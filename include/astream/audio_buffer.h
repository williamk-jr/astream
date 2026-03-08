#pragma once
#include <queue>
#include <sndfile.h>

#include "astream/audio_chunk.h"
#include "astream/error.h"

namespace astream {
  class AudioBuffer {
  public:
    AudioBuffer(int channels, long framesReadCount);

    ErrorCode push(AudioChunk& chunk);

    AudioChunk& front();

    void pop();

    size_t size();

    bool isEmpty();

    const long getFrameReadCount();

    int getChannelCount();

  private:
    std::queue<AudioChunk> buffer;
    
    int channels;
    long framesReadCount;
  };
}
