#pragma once
#include "../../audio_file_descriptor.h"

namespace astream {
  class AudioReader;

  class IAudioResampler {
  friend class AudioReader;
  
  public:
    virtual ~IAudioResampler() = default;

    virtual bool open(AudioFileDescriptor& fileDescriptor, int readSize, float* readBuffer) = 0;

    virtual void resample(void* buffer) = 0;

    virtual double getSampleRateConversionRatio() = 0;

    virtual void close() = 0;
  };
}
