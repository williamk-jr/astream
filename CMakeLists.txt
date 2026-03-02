cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(libaudio)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # Required by clangd

add_library(libaudio STATIC
	"libaudio/audio_stream.cpp"
	"libaudio/audio_chunk.cpp"
  "libaudio/audio_buffer.cpp"
  "libaudio/audio_stream_factory.cpp"

	"libaudio/stream/port_audio_stream.cpp" 
	"libaudio/backends/port_audio_backend.cpp" 
  
	"libaudio/reader/resampler/sr_audio_resampler.cpp" 
	"libaudio/reader/decoder/sndlib_audio_decoder.cpp"
  "libaudio/reader/audio_reader.cpp"
)

find_package(PortAudio)
find_package(LibSndFile)
find_package(LibSamplerate)

target_include_directories(libaudio
  PUBLIC ${CMAKE_SOURCE_DIR}/include

  PUBLIC ${PORTAUDIO_INCLUDE_DIR}
  PUBLIC ${LIBSAMPLERATE_INCLUDE_DIR}
  PUBLIC ${LIBSNDFILE_INCLUDE_DIR}
)

target_link_directories(libaudio 
  PRIVATE ${PORTAUDIO_LIBRARIES}
  PRIVATE ${LIBSAMPLERATE_LIBRARIES}
  PRIVATE ${LIBSNDFILE_LIBRARIES}
)

target_link_libraries(libaudio 
  PUBLIC portaudio
  PUBLIC sndfile 
  PUBLIC samplerate
)

if(DEFINED LIBAUDIO_DEBUG_PROGRAM)
  add_executable(test_audio main.cpp)
  target_link_libraries(test_audio libaudio)
  target_include_directories(test_audio PRIVATE ${PROJECT_SOURCE_DIR}/libaudio)
endif()


