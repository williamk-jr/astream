cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(astream)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # Required by clangd

add_library(astream STATIC
	"src/audio_stream.cpp"
	"src/audio_chunk.cpp"
  "src/audio_buffer.cpp"
  "src/audio_stream_factory.cpp"

	"src/stream/port_audio_stream.cpp" 
	"src/backends/port_audio_backend.cpp" 
  
	"src/reader/resampler/sr_audio_resampler.cpp" 
	"src/reader/decoder/sndlib_audio_decoder.cpp"
  "src/reader/audio_reader.cpp"
)

find_package(PortAudio)
find_package(LibSndFile)
find_package(LibSamplerate)

target_include_directories(astream
  PUBLIC ${CMAKE_SOURCE_DIR}/include

  PUBLIC ${PORTAUDIO_INCLUDE_DIR}
  PUBLIC ${LIBSAMPLERATE_INCLUDE_DIR}
  PUBLIC ${LIBSNDFILE_INCLUDE_DIR}
)

target_link_directories(astream 
  PRIVATE ${PORTAUDIO_LIBRARIES}
  PRIVATE ${LIBSAMPLERATE_LIBRARIES}
  PRIVATE ${LIBSNDFILE_LIBRARIES}
)

target_link_libraries(astream 
  PUBLIC portaudio
  PUBLIC sndfile 
  PUBLIC samplerate
)

if(DEFINED LIBAUDIO_DEBUG_PROGRAM)
  add_executable(test_audio main.cpp)
  target_link_libraries(test_audio astream)
  target_include_directories(test_audio PRIVATE ${PROJECT_SOURCE_DIR}/include)
endif()


