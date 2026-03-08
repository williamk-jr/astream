#pragma once
#include <portaudio.h>

#include "astream/backends/iaudio_backend.h"
#include "astream/audio_device.h"

namespace astream {
  class PortAudioBackend : public IAudioBackend {
  public:
    PortAudioBackend();

    ErrorCode initialize() override;
    ErrorCode terminate() override;

    const Result<AudioDevice> getDefaultAudioDevice() const override;
    const Result<AudioDevice> getAudioDevice(int id) const override;
  private:
    PaError error;
  };
}
