// Copyright (c) 2023 Emil Fedorov

#ifndef WTCAT_JPEG_DECODER_H_
#define WTCAT_JPEG_DECODER_H_

#include <fstream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ifstream;

namespace jpegUtils
{
    
class JPEG {
public:
    JPEG(const char*);
    void PrintHexTable();
    ~JPEG();
private:
    void ReadFromFile();
    ifstream* file;
    vector<string> segments;
    int init_error;
};

} // namespace jpegUtils

#endif