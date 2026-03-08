#include <cmath>
#include <astream/audio_buffer.h>

namespace astream {
  struct Wave {
    double amplitude = 1.0;
    double frequency = 1.0;
    double phase = 1.0;
  };

  AudioBuffer sinusoidal(Wave wave, long frames, int channels);

}
