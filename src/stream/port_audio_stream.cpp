#include "astream/stream/port_audio_stream.h"
#include "astream/error.h"
#include <portaudio.h>

namespace astream {

  PortAudioStream::PortAudioStream(AudioReader& reader) : IBasicAudioStream(reader) {}

  ErrorCode PortAudioStream::openStream() {
    // PaDeviceIndex devicesCount = Pa_GetDeviceCount();
    // for (PaDeviceIndex device = 0; device < devicesCount; device++) {
    //  const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);

    // }

    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);
    
    PaStreamParameters outputParameters;
    outputParameters.device = device;
    outputParameters.channelCount = this->audioStreamData->data.channels;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = deviceInfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    PaError error = Pa_OpenStream(
      &this->stream,
      NULL,
      &outputParameters,
      deviceInfo->defaultSampleRate,
      this->audioBuffer->getFrameReadCount(), // paFramesPerBufferUnspecified
      paNoFlag,
      paCallback,
      &this->audioStreamData
    );

    if (error != paNoError) {
      return ErrorCode::STREAM_OPEN_FAILURE;
    }

    Pa_SetStreamFinishedCallback(this->stream, paStreamFinishedCallback);
    return ErrorCode::SUCCESS;
  }

  ErrorCode PortAudioStream::closeStream() {
    PaError error = Pa_CloseStream(this->stream);
    if (error != paNoError) {
      return ErrorCode::STREAM_CLOSE_FAILURE;
    }
    return ErrorCode::SUCCESS;
  }

  ErrorCode PortAudioStream::startStream() {
    this->audioStreamData->streamFinished = false;
    PaError error = Pa_StartStream(this->stream);
    if (error != paNoError) {
      return ErrorCode::STREAM_START_FAILURE;
    }
    return ErrorCode::SUCCESS;
  }

  void PortAudioStream::seekStream(int frames) {
    this->audioStreamData->seekOffset = frames;
    this->audioStreamData->seeking = true;
  }

  ErrorCode PortAudioStream::stopStream() {
    PaError error = Pa_StopStream(this->stream);
    if (error != paNoError) {
      return ErrorCode::STREAM_STOP_FAILURE;
    }
    return ErrorCode::SUCCESS;
  }

  bool PortAudioStream::isStreamFinished() {
    return this->audioStreamData->streamFinished;
  }

  bool PortAudioStream::isStreamStopped() {
    return Pa_IsStreamStopped(this->stream);
  }

  bool PortAudioStream::isStreamActive() {
    return Pa_IsStreamActive(this->stream);
  }

  long PortAudioStream::streamPosition() {
    return this->audioStreamData->start / this->getChannelCount();
  }

  long PortAudioStream::streamDuration() {
    return this->audioStreamData->data.frames;
  }

  int PortAudioStream::getChannelCount() {
    return this->audioStreamData->data.channels;
  }

  AudioBuffer& PortAudioStream::getAudioBuffer() {
    return *this->audioBuffer;
  }

  std::string PortAudioStream::getError() {
    return std::string(Pa_GetErrorText(this->error));
  }

  bool PortAudioStream::hasError() {
    return this->error != paNoError;
  }

  int PortAudioStream::getDeviceIndex() {
    PaDeviceIndex device = Pa_GetDefaultOutputDevice();
    if (device == paNoDevice) {
      throw std::runtime_error("No default output device found.");
    }
    return device;
  }

  const PaDeviceInfo* PortAudioStream::getDeviceInfo() {
    return Pa_GetDeviceInfo(getDeviceIndex());
  }
}
