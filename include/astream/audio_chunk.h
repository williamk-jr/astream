#pragma once
#include <vector>

namespace astream {
  class AudioChunk {
  public:
    AudioChunk();
    AudioChunk(int channels, long frameCount);

    std::vector<float>* data();
    int getChannelCount();
    long getFrameCount();
    size_t getSize();

  private:
    int channels;
    long frameCount;
    std::vector<float> buffer;
  };
};
