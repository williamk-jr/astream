#pragma once
#include <sndfile.h>
#include <filesystem>

#include "astream/reader/decoder/iaudio_decoder.h"


namespace astream {
  class SndlibAudioDecoder: public IAudioDecoder {
  public:
    SndlibAudioDecoder();
    SndlibAudioDecoder(int readSize);

  protected:
    ErrorCode open(std::filesystem::path filePath) override;
    Result<size_t> read(float* buffer) override;
    ErrorCode seek(size_t frames, int whence) override;

    AudioFileDescriptor& getAudioFileDescriptor() override;
    int getFrameReadCount() override;

    ErrorCode close() override;
  private:
    std::filesystem::path path;
    SNDFILE* file;

    AudioFileDescriptor audioFileDescriptor;

    int frameReadCount = 0;
    int readSize = 0;
  };
}
