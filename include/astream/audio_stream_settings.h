#pragma once

namespace astream {
  enum class DecoderType {
    SNDLIB
  };

  enum class ResamplerType {
    SR
  };

  enum class StreamType {
    PORTAUDIO
  };


  struct DecoderSettings {
    DecoderType readerType;
    int bufferSize = 1024;
  };

  struct ResamplerSettings {
    ResamplerType resamplerType;
  };

  struct StreamSettings {
    StreamType streamType;
  };
  

  struct AudioStreamSettings {
    DecoderSettings readerSettings;
    ResamplerSettings resamplerSettings;
    StreamSettings streamSettings;
  };
}
