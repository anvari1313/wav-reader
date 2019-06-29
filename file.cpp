//
// Created by ahmad on 6/29/19.
//

#include <iostream>
#include <fstream>
#include <ios>
#include "file.hpp"

wav_reader::WavFile::WavFile(std::string file_name) {
    this->file_name_ = file_name;
    this->file_stream_ = std::ifstream();
}

void wav_reader::WavFile::Read() {
    this->file_stream_.open(this->file_name_, std::ios::in | std::ios::binary);
    if (! file_stream_)
    {
        std::cerr << "Could not open the file";
    }
    else
    {
        parse_header();
        extract_data_chunk();
    }
}

void wav_reader::WavFile::parse_header() {
    this->file_stream_.read((char *) &this->header_.RIFF, sizeof(this->header_.RIFF));
    this->file_stream_.read((char *) &this->header_.ChunkSize, sizeof(this->header_.ChunkSize));
    this->file_stream_.read((char *) &this->header_.WAVE, sizeof(this->header_.WAVE));
    this->file_stream_.read((char *) &this->header_.fmt, sizeof(this->header_.fmt));
    this->file_stream_.read((char *) &this->header_.Subchunk1Size, sizeof(this->header_.Subchunk1Size));
    this->file_stream_.read((char *) &this->header_.AudioFormat, sizeof(this->header_.AudioFormat));
    this->file_stream_.read((char *) &this->header_.NumOfChan, sizeof(this->header_.NumOfChan));
    this->file_stream_.read((char *) &this->header_.SamplesPerSec, sizeof(this->header_.SamplesPerSec));
    this->file_stream_.read((char *) &this->header_.bytesPerSec, sizeof(this->header_.bytesPerSec));
    this->file_stream_.read((char *) &this->header_.blockAlign, sizeof(this->header_.blockAlign));
    this->file_stream_.read((char *) &this->header_.bitsPerSample, sizeof(this->header_.bitsPerSample));
    this->file_stream_.read((char *) &this->header_.Subchunk2ID, sizeof(this->header_.Subchunk2ID));
    this->file_stream_.read((char *) &this->header_.Subchunk2Size, sizeof(this->header_.Subchunk2Size));
}

void wav_reader::WavFile::extract_data_chunk() {
    auto current = this->file_stream_.tellg();
    this->file_stream_.seekg(0, std::ios::end);
    auto end = this->file_stream_.tellg();
    this->data_size_ = end - current;
    this->data_ = new uint8_t[this->data_size_];
    this->file_stream_.seekg(current, std::ios::beg);
    this->file_stream_.read((char *)this->data_, this->data_size_);
}

uint8_t wav_reader::WavFile::GetByte(size_t i) {
    return this->data_[i];
}

wav_reader::WavFile::~WavFile() {
    delete[](this->data_);
}
