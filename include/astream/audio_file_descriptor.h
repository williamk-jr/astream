#pragma once
#include <cstddef>

namespace astream {
  struct AudioFileDescriptor {
    size_t frames;
    int sampleRate;
    int channels;
  };
}
