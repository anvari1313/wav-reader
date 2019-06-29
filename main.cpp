#include <iostream>
#include "file.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    wav_reader::WavFile file1("t1.wav");
    wav_reader::WavFile file2("1.wav");
    file1.Read();
    file2.Read();
    cout << file1.GetByte(0) << file2.GetByte(0) << endl;
    cout << file1.GetByte(1) << file2.GetByte(1) << endl;
    cout << file1.GetByte(2) << file2.GetByte(2) << endl;
    cout << file1.GetByte(3) << file2.GetByte(3) << endl;

    return 0;
}