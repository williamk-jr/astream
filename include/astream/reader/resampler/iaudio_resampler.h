#pragma once
#include "astream/audio_file_descriptor.h"
#include "astream/error.h"

namespace astream {
  class AudioReader;

  class IAudioResampler {
  friend class AudioReader;
  
  public:
    virtual ~IAudioResampler() = default;

    virtual ErrorCode open(AudioFileDescriptor& fileDescriptor, int readSize, float* readBuffer) = 0;

    virtual ErrorCode resample(void* buffer) = 0;

    virtual double getSampleRateConversionRatio() = 0;

    virtual ErrorCode close() = 0;
  };
}
