cmake_minimum_required(VERSION 3.14)
project(wav_reader)

set(CMAKE_CXX_STANDARD 17)

add_executable(wav_reader main.cpp file.cpp file.hpp)