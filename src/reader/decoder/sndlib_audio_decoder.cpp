#include "astream/reader/decoder/sndlib_audio_decoder.h"

namespace astream {
  SndlibAudioDecoder::SndlibAudioDecoder() {}

  SndlibAudioDecoder::SndlibAudioDecoder(int frameReadCount): 
    frameReadCount(frameReadCount) {}

  bool SndlibAudioDecoder::open(std::filesystem::path filePath) {
    SF_INFO info;

    // Format file path
    std::string pathStr = filePath.string();
    const char* pathCStr = pathStr.c_str();

    // Open file
    this->file = sf_open(pathCStr, SFM_READ, &info);
    if (this->file == nullptr) {
      return false;
    }

    this->audioFileDescriptor.frames = info.frames;
    this->audioFileDescriptor.channels = info.channels;
    this->audioFileDescriptor.sampleRate = info.samplerate;
    return true;
  }

  size_t SndlibAudioDecoder::read(float* buffer) {
    return sf_readf_float(this->file, buffer, this->frameReadCount);
  }

  bool SndlibAudioDecoder::seek(size_t frames, int whence) {
    sf_seek(this->file, frames, whence);
    return true; // TODO: Proper error handling.
  }

  AudioFileDescriptor& SndlibAudioDecoder::getAudioFileDescriptor() {
    return this->audioFileDescriptor;
  }

  int SndlibAudioDecoder::getFrameReadCount() {
    return this->frameReadCount;
  }

  void SndlibAudioDecoder::close() {
    sf_close(file);
  }
}
