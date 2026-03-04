#include <catch2/catch_test_macros.hpp>
#include <astream/backends/port_audio_backend.h>

TEST_CASE("Test Portaudio Backend.", "[portaudio][backend]") {
  astream::PortAudioBackend backend;

  REQUIRE_NOTHROW(backend.initialize());
  
  backend.terminate();
}
