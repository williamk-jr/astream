#pragma once

#include <vector>

namespace astream {
  struct AudioFileDescriptor {
    size_t frames;
    int sampleRate;
    int channels;
  };
}
