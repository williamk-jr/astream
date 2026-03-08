#include "astream/audio_stream.h"

namespace astream {
  int AudioStream::MAX_LOADED_CHUNKS = 20;

  AudioStream::AudioStream() {};

  AudioStream::AudioStream(std::unique_ptr<AudioReader> reader, std::unique_ptr<IBasicAudioStream> stream) :
    reader(std::move(reader)),
    basicAudioStream(std::move(stream))
  {};
  
  ErrorCode AudioStream::setup() {
    if (this->streamState == StreamState::OPEN) {
      return ErrorCode::STREAM_ALREADY_OPEN;
    }

    AudioFileDescriptor& audioData = this->reader->getAudioFileDescriptor();
    this->audioReaderThread = std::thread([this](){ audioReaderThreadCallback(); }); // Start reader thread.

    ErrorCode error = this->basicAudioStream->openStream();
    if (error != ErrorCode::SUCCESS) {
      return error;
    }

    this->streamState = StreamState::OPEN;
    return ErrorCode::SUCCESS;
  }

  ErrorCode AudioStream::start() {
    if (this->basicAudioStream->isStreamStopped()) {
      return ErrorCode::STREAM_ALREADY_STOPPED;
    }

    ErrorCode error = this->basicAudioStream->startStream();
    if (error != ErrorCode::SUCCESS) {
      return error;
    }

    this->playingState = PlayingState::PLAYING;
    return ErrorCode::SUCCESS;
  }

  void AudioStream::seek(float seconds) {
    this->playingState = PlayingState::SEEKING;

    while (this->basicAudioStream->getAudioBuffer().size() > 0) { // Clear chunk buffer
      this->basicAudioStream->getAudioBuffer().pop();
    }

    long frames = seconds * this->reader->getAudioFileDescriptor().sampleRate;
    this->reader->seek(frames, SEEK_CUR);
    this->basicAudioStream->seekStream(frames);

    this->playingState = PlayingState::PLAYING;
  }

  ErrorCode AudioStream::stop() {
    if (!this->basicAudioStream->isStreamActive()) {
      return ErrorCode::STREAM_NOT_ACTIVE;
    }

    ErrorCode error = this->basicAudioStream->stopStream();
    if (error != ErrorCode::SUCCESS) {
      return error;
    }

    this->playingState = PlayingState::STOPPED;
    return ErrorCode::SUCCESS;
  }

  ErrorCode AudioStream::end() {
    if (this->streamState == StreamState::CLOSED) {
      return ErrorCode::STREAM_ALREADY_CLOSED;
    }

    if (this->audioReaderThread.joinable()) {
      this->audioReaderThread.join();
    }

    ErrorCode error = this->basicAudioStream->closeStream();
    if (error != ErrorCode::SUCCESS) {
      return error;
    }

    this->streamState = StreamState::CLOSED;
    return ErrorCode::SUCCESS;
  }

  long AudioStream::position() {
    if (this->isStopped()) {
      return -1;
    }
    return this->basicAudioStream->streamPosition() / this->reader->getAudioFileDescriptor().sampleRate;
  }

  double AudioStream::durationInSeconds() {
    return (double)this->basicAudioStream->streamDuration() / this->reader->getAudioFileDescriptor().sampleRate;
  }

  double AudioStream::durationInMilliseconds() {
    return this->durationInSeconds() * 1000;
  }

  bool AudioStream::isFinished() {
    return this->basicAudioStream->isStreamFinished();
  }

  bool AudioStream::isActive() {
    return this->basicAudioStream->isStreamActive();
  }

  bool AudioStream::isStopped() {
    return this->basicAudioStream->isStreamStopped();
  }

  // Private
  void AudioStream::audioReaderThreadCallback() {
    while (this->streamState != StreamState::CLOSED) {

      if (this->basicAudioStream->getAudioBuffer().size() >= this->MAX_LOADED_CHUNKS || this->playingState == PlayingState::SEEKING) {
        continue;
      }

      Result<size_t> readSize = this->reader->read(this->basicAudioStream->getAudioBuffer());
    }
    this->reader->close();
  }
}
