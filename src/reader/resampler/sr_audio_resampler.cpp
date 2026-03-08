#include "astream/reader/resampler/sr_audio_resampler.h"
#include "astream/error.h"

namespace astream {
  SRAudioResampler::SRAudioResampler(double deviceSampleRate) : deviceSampleRate(deviceSampleRate) {}

  ErrorCode SRAudioResampler::open(AudioFileDescriptor& fileDescriptor, int readSize, float* readBuffer) {
    this->sampleRateConversionRatio = deviceSampleRate / fileDescriptor.sampleRate;
    
    int error = 0;
    this->srcState = src_new(SRC_SINC_FASTEST, fileDescriptor.channels, &error);
    if (error != 0) {
      return ErrorCode::RESAMPLER_OPEN_FAILURE;
    }

    this->srcData.data_in = readBuffer;
    this->srcData.input_frames = readSize;
    this->srcData.output_frames = readSize * this->sampleRateConversionRatio;
    this->srcData.src_ratio = this->sampleRateConversionRatio;
    this->srcData.end_of_input = 0;

    return ErrorCode::SUCCESS;
  }

  ErrorCode SRAudioResampler::resample(void* buffer) {
    this->srcData.data_out = (float*)buffer;
    if (src_process(this->srcState, &this->srcData) != 0) {
      return ErrorCode::RESAMPLER_RESAMPLE_FAILURE; 
    }
    return ErrorCode::SUCCESS;
  }

  ErrorCode SRAudioResampler::close() {
    if (src_delete(this->srcState) != 0) {
      return ErrorCode::RESAMPLER_CLOSE_FAILURE;
    }
    return ErrorCode::SUCCESS;
  }

  double SRAudioResampler::getSampleRateConversionRatio() {
    return this->sampleRateConversionRatio;
  }
}
