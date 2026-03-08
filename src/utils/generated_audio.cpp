#include <astream/utils/generated_audio.h>

namespace astream {
  AudioBuffer sinusoidal(Wave wave, long frames, int channels) {
    double buffer[frames*channels];
    double step = 0.01;
    

    for (int frame = 0; frame < frames; frame++) {
      for (int channel = 0; channel < channels; channel++) {
        buffer[frame+channel] = wave.amplitude*std::sin(
          wave.frequency * (step*frame)
        );
      }
    }
    

  }
}
