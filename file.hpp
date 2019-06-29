//
// Created by ahmad on 6/29/19.
//

#ifndef WAV_READER_FILE_HPP
#define WAV_READER_FILE_HPP

#include <string>
#include <fstream>

namespace wav_reader
{

    typedef struct WAV_HEADER {
        /* RIFF Chunk Descriptor */
        uint8_t RIFF[4];        // RIFF Header Magic header
        uint32_t ChunkSize;      // RIFF Chunk Size
        uint8_t WAVE[4];        // WAVE Header
        /* "fmt" sub-chunk */
        uint8_t fmt[4];         // FMT header
        uint32_t Subchunk1Size;  // Size of the fmt chunk
        uint16_t AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
        uint16_t NumOfChan;      // Number of channels 1=Mono 2=Sterio
        uint32_t SamplesPerSec;  // Sampling Frequency in Hz
        uint32_t bytesPerSec;    // bytes per second
        uint16_t blockAlign;     // 2=16-bit mono, 4=16-bit stereo
        uint16_t bitsPerSample;  // Number of bits per sample
        /* "data" sub-chunk */
        uint8_t Subchunk2ID[4]; // "data"  string
        uint32_t Subchunk2Size;  // Sampled data length
    } wav_hdr;

    class WavFile
    {
    private:
        wav_hdr header_;

        std::string file_name_;
        std::ifstream file_stream_;

        size_t data_size_;
        uint8_t *data_;

        void parse_header();
        void extract_data_chunk();
    public:
        explicit WavFile(std::string);

        void Read();
        uint8_t GetByte(size_t i);

        ~WavFile();
    };
}


#endif //WAV_READER_FILE_HPP
