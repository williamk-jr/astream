#include "astream/audio_chunk.h"
#include "astream/error.h"
#include <catch2/catch_test_macros.hpp>
#include <astream/audio_buffer.h>

TEST_CASE("Test Audio Chunk", "[chunk]") {
  int channels = 2;
  int frameCount = 1024;

  astream::AudioChunk chunk(channels, frameCount);

  REQUIRE(chunk.getSize() == channels*frameCount);
}

TEST_CASE("Test Audio Buffer", "[buffer]") {
  int channels = 2;
  int frameCount = 1024;

  astream::AudioBuffer buffer(channels, frameCount);
  REQUIRE(buffer.getFrameReadCount() == frameCount);

  astream::AudioChunk goodChunk(channels, frameCount);
  astream::AudioChunk badChunk(channels+1, frameCount);

  REQUIRE(buffer.push(goodChunk) == astream::ErrorCode::SUCCESS);
  REQUIRE(buffer.push(badChunk) == astream::ErrorCode::BUFFER_CHUNK_SIZE_MISMATCH);

  REQUIRE(buffer.size() == 1);
  buffer.pop();
  REQUIRE(buffer.size() == 0);
}
