#pragma once

#include "astream/audio_stream.h"
#include "astream/audio_stream_settings.h"
#include "astream/reader/audio_reader.h"
#include "astream/reader/decoder/sndlib_audio_decoder.h"
#include "astream/reader/resampler/sr_audio_resampler.h"
#include "astream/stream/port_audio_stream.h"
#include "astream/backends/iaudio_backend.h"

namespace astream {
  

  class AudioStreamFactory {
    public:
      static AudioStream fromFile(const IAudioBackend& backend, const std::string& filePath);
      static AudioStream fromFile(const IAudioBackend& backend, const std::string& filePath, AudioStreamSettings settings);

    private:
      static std::unique_ptr<IAudioDecoder> createDecoder(AudioStreamSettings settings);
      static std::unique_ptr<IAudioResampler> createResampler(AudioStreamSettings settings, const IAudioBackend& backend);
      static std::unique_ptr<IBasicAudioStream> createAudioStream(AudioStreamSettings settings, AudioReader& reader);
  };
}
