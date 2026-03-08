#include "astream/audio_buffer.h"
#include "astream/error.h"

namespace astream {
  AudioBuffer::AudioBuffer(int channels, long framesReadCount):
    channels(channels),
    framesReadCount(framesReadCount)
  {}

  ErrorCode AudioBuffer::push(AudioChunk& chunk) {
    if (chunk.getFrameCount() != this->getFrameReadCount() || 
        chunk.getChannelCount() != this->getChannelCount()) {

      return ErrorCode::BUFFER_CHUNK_SIZE_MISMATCH; 
      //throw std::runtime_error("Mismatch between chunk size and frames per buffer. " + 
      //                          std::to_string(chunk.getSize()) + " vs " + 
      //                          std::to_string(this->framesReadCount * this->channels)
      //);
    }
    this->buffer.push(chunk);
    return ErrorCode::SUCCESS;
  }

  AudioChunk& AudioBuffer::front() {
    return this->buffer.front();
  }

  void AudioBuffer::pop() {
    this->buffer.pop();
  }

  size_t AudioBuffer::size() {
    return this->buffer.size();
  }

  bool AudioBuffer::isEmpty() {
    return this->buffer.empty();
  }

  const long AudioBuffer::getFrameReadCount() {
    return this->framesReadCount;
  }


  int AudioBuffer::getChannelCount() {
    return this->channels;
  }
}
