#pragma once
#include <string>

namespace astream {
  struct AudioDevice {
    std::string name;
    double samplerate;
  };
}
