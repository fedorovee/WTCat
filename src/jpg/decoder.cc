// Copyright (c) 2023 Emil Fedorov

#include "decoder.h"
#include <iostream>

namespace jpegUtils
{

namespace Markers
{
    const unsigned char JPEG_FORMAT[3] = {0xFF, 0xD8, 0x00};
} // namespace Markers

bool hexstrcmp(const char* left, const char* right) {
    for (int i = 0; ; i++) {
        if (left[i] != right[i]) 
            return 0;
        else if (left[i] == '\0' && right[i] == '\0')
            return 1;
    }

    return 1;
}

int JPEG::ReadFromFile() {
    int segment_number = 0;
    int len_of_segment = 2;
    int len_of_new_seg = 0;
    bool len_reading = false;

    vector <string> seg;
    // bool begin_of_segment = true;
    
    int i = 0;
    while (!file->eof()) {
        std::cout << "Deb#3\n";
        seg[segment_number] += file->get();

        if (i >= 2) {
            
            if (len_of_segment == 0) {
                if (!len_of_new_seg) {
                    segment_number++;
                    len_of_segment = 4;
                    len_reading = true;
                }
                else {
                    len_of_segment = len_of_new_seg;
                    len_reading = false;
                }
                len_of_new_seg = 0;

            } else if (len_of_segment <= 2 && len_reading) {
                len_of_new_seg += seg[segment_number][i];
            }

        } else if (i == 1 && !(seg[0][i - 1] == 0xFF && seg[0][i] == 0xD8)) {
            return 2;
        }

        i++;
        len_of_segment--;
    }

    return 0;
}

JPEG::JPEG(const char* path) :
    file(new std::ifstream(path, std::ios::binary | std::ios::in)) {
    if (file->is_open()) {
        std::cout << "Deb#1\n";
        init_error = ReadFromFile();
    } else {
        std::cout << "Deb#2\n";
        init_error = 1;
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
