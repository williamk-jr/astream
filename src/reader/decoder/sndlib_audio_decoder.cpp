#include "astream/reader/decoder/sndlib_audio_decoder.h"
#include "astream/error.h"

namespace astream {
  SndlibAudioDecoder::SndlibAudioDecoder() {}

  SndlibAudioDecoder::SndlibAudioDecoder(int frameReadCount): 
    frameReadCount(frameReadCount) {}

  ErrorCode SndlibAudioDecoder::open(std::filesystem::path filePath) {
    SF_INFO info;

    // Format file path
    std::string pathStr = filePath.string();
    const char* pathCStr = pathStr.c_str();

    // Open file
    this->file = sf_open(pathCStr, SFM_READ, &info);
    if (this->file == nullptr) {
      return ErrorCode::DECODER_FILE_OPEN_FAILURE;
    }

    this->audioFileDescriptor.frames = info.frames;
    this->audioFileDescriptor.channels = info.channels;
    this->audioFileDescriptor.sampleRate = info.samplerate;
    return ErrorCode::SUCCESS;
  }

  Result<size_t> SndlibAudioDecoder::read(float* buffer) {
    size_t readCount = sf_readf_float(this->file, buffer, this->frameReadCount);
    return Result<size_t>::success(readCount);
  }

  ErrorCode SndlibAudioDecoder::seek(size_t frames, int whence) {
    sf_seek(this->file, frames, whence);
    return ErrorCode::SUCCESS; // TODO: Proper error handling.
  }

  AudioFileDescriptor& SndlibAudioDecoder::getAudioFileDescriptor() {
    return this->audioFileDescriptor;
  }

  int SndlibAudioDecoder::getFrameReadCount() {
    return this->frameReadCount;
  }

  ErrorCode SndlibAudioDecoder::close() {
    if (sf_close(file) != SF_ERR_NO_ERROR) {
      return ErrorCode::DECODER_FILE_CLOSE_FAILURE;
    }
    return ErrorCode::SUCCESS;
  }
}
