//#include "AudioChunk.h"
#include "astream/audio_chunk.h"

namespace astream {

  AudioChunk::AudioChunk() {}

  AudioChunk::AudioChunk(long size) : size(size) {
    this->buffer = std::vector<float>(size);
  }

  long AudioChunk::getSize() {
    return this->size;
  }

  std::vector<float>* AudioChunk::data() {
    return &buffer;
  }
}
