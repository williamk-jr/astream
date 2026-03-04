#include "astream/reader/decoder/iaudio_decoder.h"
#include "astream/reader/decoder/sndlib_audio_decoder.h"
#include "astream/reader/resampler/iaudio_resampler.h"
#include "astream/reader/resampler/sr_audio_resampler.h"
#include <catch2/catch_test_macros.hpp>
#include <astream/reader/audio_reader.h>
#include <memory>

std::unique_ptr<astream::IAudioDecoder> decoders[] = {
  std::make_unique<astream::SndlibAudioDecoder>()
};

std::unique_ptr<astream::IAudioResampler> resamplers[] = {
  std::make_unique<astream::SRAudioResampler>(41000)
};

TEST_CASE("Test Audio Reader.", "[reader]") {
  for (std::unique_ptr<astream::IAudioDecoder>& decoder : decoders) {
    for (std::unique_ptr<astream::IAudioResampler>& resampler : resamplers) {

      SECTION("Test Decoders & Resamplers") {
        astream::AudioReader reader(std::move(decoder), std::move(resampler));

        REQUIRE(reader.open("test_files/test.mp3"));
        //reader.getAudioFileDescriptor()

        reader.close();
      }
    }
  }
}

