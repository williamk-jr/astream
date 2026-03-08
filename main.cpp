#include <iostream>
#include <chrono>
#include <thread>
#include <astream/audio_stream.h>
#include <astream/audio_stream_factory.h>
#include <astream/backends/port_audio_backend.h>

int main() {
  std::cout << "hello world" << "\n";
  astream::PortAudioBackend backend;
  backend.initialize();

  astream::AudioStream audioStream = 
      astream::AudioStreamFactory::fromFile(backend, "test_files/test.mp3");

  std::cout << "Duration (Seconds): " << audioStream.durationInSeconds() << "\n";
  std::cout << "Duration (Milliseconds): " << audioStream.durationInMilliseconds() << "\n";


  audioStream.setup();
  audioStream.start();

  while (!audioStream.isFinished()) {
    //Pa_Sleep(1000);
    //std::cout << audioStream.position() << " s/ " << audioStream.duration() << " s" << std::endl;
  }

  audioStream.stop();
  audioStream.end();
  backend.terminate();
  return 0;
}
