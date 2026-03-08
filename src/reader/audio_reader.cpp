#include "astream/reader/audio_reader.h"
#include "astream/error.h"

namespace astream {

    AudioReader::AudioReader(std::unique_ptr<IAudioDecoder> decoder, std::unique_ptr<IAudioResampler> resampler) {
      
      this->decoder = std::move(decoder);
      this->resampler = std::move(resampler);
    }

    ErrorCode AudioReader::open(std::filesystem::path filePath) {
        ErrorCode error = ErrorCode::SUCCESS;
        error = this->decoder->open(filePath);

        if (error != ErrorCode::SUCCESS) {
          return error;
        }

        error = this->resampler->open(
            this->decoder->getAudioFileDescriptor(), 
            this->decoder->getFrameReadCount(), 
            this->readBuffer.data()
        );

        if (error != ErrorCode::SUCCESS) {
          return error;
        }

        this->readBuffer = std::vector<float>(
            this->decoder->getFrameReadCount() * this->decoder->getAudioFileDescriptor().channels
        );

        return error;
    }

    Result<size_t> AudioReader::read(AudioBuffer& buffer) {
        double srConvertionRatio = this->resampler->getSampleRateConversionRatio();
        long frameCount = this->decoder->getFrameReadCount() * srConvertionRatio;
        int channels = this->decoder->getAudioFileDescriptor().channels;

        AudioChunk chunk(channels, frameCount);
        Result<size_t> readCount = this->decoder->read(this->readBuffer.data());
        if (!readCount.successful()) {
          return readCount;
        }
        // Transfer data from read buffer to chunk buffer.
        if (srConvertionRatio == 1.0) { // The ratio is the same, no need to convert.
            *(chunk.data()) = this->readBuffer;
        } else {
            ErrorCode error = this->resampler->resample(chunk.data()->data());
            if (error != ErrorCode::SUCCESS) {
              return Result<size_t>::error(readCount.get(), error);
            }
        }

        if (readCount.get() > 0) {
            buffer.push(chunk);
        }
        return readCount;
    }

    ErrorCode AudioReader::seek(size_t frames, int whence) {
        ErrorCode error = this->decoder->seek(frames, whence);
        if (error != ErrorCode::SUCCESS) {
          return error;
        }
        return ErrorCode::SUCCESS;
    }

    void* AudioReader::getReadBuffer() {
        return this->readBuffer.data();
    }

    AudioFileDescriptor& AudioReader::getAudioFileDescriptor() {
        return this->decoder->getAudioFileDescriptor();
    }

    int AudioReader::getFrameReadCount() {
        return this->decoder->getFrameReadCount();
    }

    double AudioReader::getSampleRateConversionRatio() {
        return this->resampler->getSampleRateConversionRatio();
    }

    ErrorCode AudioReader::close() {
        ErrorCode error = ErrorCode::SUCCESS;
        error = this->resampler->close();
        if (error != ErrorCode::SUCCESS) {
          return error;
        }

        error = this->decoder->close();
        return error;
    }
}
