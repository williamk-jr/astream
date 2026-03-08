#pragma once
#include <samplerate.h>

#include "iaudio_resampler.h"

namespace astream {
  class SRAudioResampler: public IAudioResampler {
  public:
    SRAudioResampler(double deviceSampleRate);
  
  protected:
    ErrorCode open(AudioFileDescriptor& fileDescriptor, int readSize, float* readBuffer) override;
    ErrorCode resample(void* writeBuffer) override;
    double getSampleRateConversionRatio() override;
    ErrorCode close() override;

  private:
    SRC_STATE* srcState; // Samplerate Converter state
    SRC_DATA srcData; // Samplerate Converter data

    double sampleRateConversionRatio;
    double deviceSampleRate;
  };
}
