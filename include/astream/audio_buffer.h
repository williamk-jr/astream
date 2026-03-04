#pragma once
#include <sndfile.h>
#include <queue>
#include <filesystem>
#include <iostream>

#include "audio_chunk.h"
#include "audio_file_descriptor.h"


namespace astream {
  class AudioBuffer {
  public:
    AudioBuffer(int channels, long framesReadCount);

    void push(AudioChunk& chunk);

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
