#include "astream/audio_buffer.h"

namespace astream {
  AudioBuffer::AudioBuffer(int channels, long framesReadCount):
    channels(channels),
    framesReadCount(framesReadCount)
  {}

  void AudioBuffer::push(AudioChunk& chunk) {
    if (chunk.getFrameCount() != this->getFrameReadCount() || 
        chunk.getChannelCount() != this->getChannelCount()) {
      throw std::runtime_error("Mismatch between chunk size and frames per buffer. " + 
                                std::to_string(chunk.getSize()) + " vs " + 
                                std::to_string(this->framesReadCount * this->channels)
      );
    }
    this->buffer.push(chunk);
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
