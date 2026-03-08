#include "astream/backends/port_audio_backend.h"
#include "astream/audio_device.h"
#include "astream/error.h"
#include <portaudio.h>

namespace astream {
  PortAudioBackend::PortAudioBackend() : error(paNoError) {
    // Constructor initializes the backend with no error
  }

  ErrorCode PortAudioBackend::initialize() {
    if (Pa_Initialize() != paNoError) {
      return ErrorCode::BACKEND_INITIALIZATION_FAILURE;
      //throw std::runtime_error("Failed to initialize PortAudio: " + std::string(Pa_GetErrorText(this->error)));
    }

    return ErrorCode::SUCCESS;
  }

  ErrorCode PortAudioBackend::terminate() {
    if (Pa_Terminate() != paNoError) {
      return ErrorCode::BACKEND_TERMINATION_FAILURE; 
    }
    return ErrorCode::SUCCESS;
  }

  const Result<AudioDevice> PortAudioBackend::getDefaultAudioDevice() const {
    return this->getAudioDevice(Pa_GetDefaultOutputDevice());
  }

  const Result<AudioDevice> PortAudioBackend::getAudioDevice(int device) const {
    if (device == paNoDevice) {
      return Result<AudioDevice>::error({}, ErrorCode::DEVICE_NOT_FOUND);
      //throw std::runtime_error("No default output device found.");
    }

    const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(device);
    return Result<AudioDevice>::success({ deviceInfo->name, deviceInfo->defaultSampleRate });
  }
}
