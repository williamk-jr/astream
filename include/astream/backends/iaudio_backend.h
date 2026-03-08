#pragma once
#include <memory>

#include "astream/error.h"
#include "astream/audio_device.h"
#include "astream/stream/ibasic_audio_stream.h"

namespace astream {
  typedef std::unique_ptr<IBasicAudioStream> AudioStreamPtr;

  class IAudioBackend {
  public:
    /*
    @brief Intializes audio backend. This should be called before the usage of this library.
    */
    virtual ErrorCode initialize() = 0;

    /*
    @brief Terminates audio backend.
    */
    virtual ErrorCode terminate() = 0;

    /*
    @brief Gets the default audio device.
    */
    virtual const Result<AudioDevice> getDefaultAudioDevice() const = 0;

    /*
    @brief Gets the audio device via the index. Index representation can vary between backends.
    */
    virtual const Result<AudioDevice> getAudioDevice(int id) const = 0;
  };
}
