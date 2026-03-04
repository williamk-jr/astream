#include "astream/reader/resampler/sr_audio_resampler.h"

namespace astream {
  SRAudioResampler::SRAudioResampler(double deviceSampleRate) : deviceSampleRate(deviceSampleRate) {}

  bool SRAudioResampler::open(AudioFileDescriptor& fileDescriptor, int readSize, float* readBuffer) {
    this->sampleRateConversionRatio = deviceSampleRate / fileDescriptor.sampleRate;

    this->srcState = src_new(SRC_SINC_FASTEST, fileDescriptor.channels, &this->error);
    this->srcData.data_in = readBuffer;
    this->srcData.input_frames = readSize;
    this->srcData.output_frames = readSize * this->sampleRateConversionRatio;
    this->srcData.src_ratio = this->sampleRateConversionRatio;
    this->srcData.end_of_input = 0;

    return true;
  }

  void SRAudioResampler::resample(void* buffer) {
    this->srcData.data_out = (float*)buffer;
    src_process(this->srcState, &this->srcData);
  }

  void SRAudioResampler::close() {
    src_delete(this->srcState);
  }

  double SRAudioResampler::getSampleRateConversionRatio() {
    return this->sampleRateConversionRatio;
  }
}
