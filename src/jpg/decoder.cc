// Copyright (c) 2023 Emil Fedorov

#include "decoder.h"
#include <iostream>

namespace jpegUtils
{

void JPEG::ReadFromFile() {
    unsigned char byte = 0x00;
    int segment_number = 0;
    int len_of_segment = 2;
    int len_of_new_seg = 0;
    bool jpeg_signature = false;
    // bool begin_of_segment = true;
    
    int i = 0;
    while (!file->eof()) {
        byte = file->get();

        std::cout << std::hex << std::uppercase << (int) byte << ' ';

        if (i == 0 && byte == 0xFF) {
            jpeg_signature = true;
        } else if(!jpeg_signature || i == 1 && byte != 0xD8) {
            jpeg_signature = false;
            init_error = 1;
            break;
        } //else {
        //     if (len_of_segment == 0) {
        //         if (!len_of_new_seg) {
        //             len_of_segment = 4;
        //             segment_number++;
        //         }
        //         else
        //             len_of_segment = len_of_new_seg;
        //         len_of_new_seg = 0;
        //     } else if (len_of_segment <= 2) {
        //         len_of_new_seg += byte;
        //     }
        // }

        // if (segments.size() < (segment_number - 1))
        //     segments.push_back("" + byte);
        // else
        //     segments[segment_number] += byte;

        // len_of_segment--;
        // i++;
    }
}

JPEG::JPEG(const char* path) :
    file(new std::ifstream(path, std::ios::binary | std::ios::in)) {
    if (file->is_open()) {
        std::cout << "Deb#1\n";
        ReadFromFile();
    } else {
        std::cout << "Deb#2\n";
        init_error = 0;
    }
}

void JPEG::PrintHexTable() {
    std::cout << segments.size();

    for (string segment : segments) {
        //std::cout << "Deb#4\n";
        for (char symbol : segment) {
            std::cout << std::hex << std::uppercase << (int) symbol << ' ';
        }
        //std::cout << '\n\n' << segment.size() << "\n\n";
    }
}

JPEG::~JPEG() {
    delete file;
}

} // namespace jpegUtils
