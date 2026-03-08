#pragma once
#include <filesystem>
#include <memory>
#include <vector>

#include "astream/reader/resampler/iaudio_resampler.h"
#include "astream/reader/decoder/iaudio_decoder.h"
#include "astream/audio_buffer.h"
#include "astream/error.h"

namespace astream {
    class AudioReader {
    public:

        AudioReader(std::unique_ptr<IAudioDecoder> decoder, std::unique_ptr<IAudioResampler> resampler);
        /*
        @brief Opens the audio file.
        */
        ErrorCode open(std::filesystem::path filePath);

        /*
        @brief Reads audio into the provided buffer.
        @return The number of frames read. This can be less than the requested frame count if the end of the file is reached.
        */
        Result<size_t> read(AudioBuffer& buffer);

        /*
        @brief Seeks a specified number of frames from a specified position. The position is determined by the whence parameter, which can be SEEK_SET, SEEK_CUR, or SEEK_END.
        */
        ErrorCode seek(size_t frames, int whence);

        /*
        
        */
        void* getReadBuffer();

        /*
        @brief Gets a descriptor containing information on how to handle the audio file.
        */
        AudioFileDescriptor& getAudioFileDescriptor();

        /*
        @brief Gets the maximum number of frames that can be read in a single read operation.
        */
        int getFrameReadCount();

        /*
        @brief Closes the audio file reader.
        */
        ErrorCode close();

        /*
        
        */
        double getSampleRateConversionRatio();
    private:
        std::unique_ptr<IAudioDecoder> decoder;
        std::unique_ptr<IAudioResampler> resampler;

        std::vector<float> readBuffer;
        
    };
}
