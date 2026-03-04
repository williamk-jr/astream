add_executable(test_audio 
  test_main.cpp
  test_audio_buffer.cpp
  reader/test_audio_reader.cpp
  backends/test_port_audio_backend.cpp
)

target_link_libraries(test_audio PRIVATE Catch2::Catch2WithMain astream)
target_include_directories(test_audio PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(CTest)
include(Catch)

catch_discover_tests(test_audio)
