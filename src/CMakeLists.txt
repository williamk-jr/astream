add_library(astream STATIC
	"audio_stream.cpp"
	"audio_chunk.cpp"
  "audio_buffer.cpp"
  "audio_stream_factory.cpp"

	"stream/port_audio_stream.cpp" 
	"backends/port_audio_backend.cpp" 
  
	"reader/resampler/sr_audio_resampler.cpp" 
	"reader/decoder/sndlib_audio_decoder.cpp"
  "reader/audio_reader.cpp"
)

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
