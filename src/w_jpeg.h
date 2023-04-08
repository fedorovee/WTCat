// Copyright (c) 2023 feerus23

#ifndef W_JPEG_H_
#define W_JPEG_H_

#include <map>
#include <vector>
#include <fstream>

namespace w_jpeg
{

struct Chunk {
    unsigned char marker[2];
    unsigned length;
    std::vector<unsigned char> content;
};

class JPEG {
public:
    JPEG(std::ifstream&, const std::vector<Chunk>* = nullptr);
    int GetInitCode();
    void PrintHEX();
    ~JPEG();
private:
    void Decode();
    void Encode();
    int init_error = 0;
    std::ifstream* file;
    std::vector<Chunk> chunks;
};

} // namespace w_jpeg


#endif // W_JPEG_H_