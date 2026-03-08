#pragma once

namespace astream {

  enum class ErrorCode {
    SUCCESS = 0,
    
    BACKEND_INITIALIZATION_FAILURE,
    BACKEND_TERMINATION_FAILURE,

    DEVICE_NOT_FOUND,

    DECODER_FILE_OPEN_FAILURE,
    DECODER_FILE_CLOSE_FAILURE,

    RESAMPLER_OPEN_FAILURE,
    RESAMPLER_CLOSE_FAILURE,
    RESAMPLER_RESAMPLE_FAILURE,

    STREAM_OPEN_FAILURE,
    STREAM_CLOSE_FAILURE,
    STREAM_START_FAILURE,
    STREAM_STOP_FAILURE,
    STREAM_ALREADY_OPEN,
    STREAM_ALREADY_CLOSED,
    STREAM_ALREADY_STOPPED,
    STREAM_ALREADY_ACTIVE,
    STREAM_NOT_ACTIVE,

    BUFFER_CHUNK_SIZE_MISMATCH,
  };
  
  template<typename T>
  class Result {
    public:
      static Result success(T value) {
        return Result(value);
      }

      static Result error(T value, ErrorCode errorCode) {
        return Result(value, errorCode);
      }

      T get() const {
        return this->value;
      }

      ErrorCode error() {
        return this->errorCode;
      }

      bool successful() {
        return this->errorCode == ErrorCode::SUCCESS;
      }

    private:
      Result(T value) {
        this->value = value;
      }

      Result(T value, ErrorCode errorCode) {
        this->value = value;
        this->errorCode = errorCode;
      }

      T value;
      ErrorCode errorCode = ErrorCode::SUCCESS;
  };
}
