//#include "AudioChunk.h"
#include "astream/audio_chunk.h"

namespace astream {

  AudioChunk::AudioChunk() {}

  AudioChunk::AudioChunk(int channels, long frameCount) 
    : channels(channels), frameCount(frameCount) {
    this->buffer = std::vector<float>(frameCount * channels);
  }

  size_t AudioChunk::getSize() {
    return this->buffer.capacity();
  }

  int AudioChunk::getChannelCount() {
    return this->channels;
  }
  
  long AudioChunk::getFrameCount() {
    return this->frameCount;
  }

  std::vector<float>* AudioChunk::data() {
    return &buffer;
  }
}
