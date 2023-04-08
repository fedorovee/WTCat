// Copyright (c) 2023 feerus23

#include <valarray>
#include <iostream>
#include "w_jpeg.h"

#define markcmp(var, fi, si, marker_name) (var[fi] == Markers::marker_name[0] && var[si] == Markers::marker_name[1])

namespace w_jpeg
{

namespace Markers {
    std::vector<unsigned char> JFIF = { 0xFF, 0xD8 };
    std::vector<unsigned char> SOS = { 0xFF, 0xDA };
    std::vector<unsigned char> EOI = { 0xFF, 0xD9 };
};

int JPEG::GetInitCode() {
    return init_error;
}

JPEG::JPEG(std::ifstream& image_file, const std::vector<Chunk>* chunks_param) {
    if (!image_file.is_open()) {
        init_error = 1;
    } else if(!chunks_param) {
        file = &image_file;
        Decode();
    }
}

void JPEG::Decode() {
    std::vector<unsigned char> image;
    int len_of_chunk;
    bool transition = true;
    bool start_of_scan_readed = false;

    for (size_t i = 0; !file->eof(); i++) {
        image.push_back(file->get());

        if (!start_of_scan_readed){
            if (i == 1) {
                if (!markcmp(image, i - 1, i, JFIF)) {
                    init_error = 2;
                    break;
                }
            } else if (i > 4) {
                if (transition) {
                    if (chunks.size() > 1 && markcmp(chunks[chunks.size() - 1].marker, 0, 1, SOS)) {
                        start_of_scan_readed = true;

                        len_of_chunk = 1;

                        Chunk chunk {
                            {0x00, 0x00},
                            0,
                            {image[i]}
                        };

                        chunks.push_back(chunk);
                        continue;
                    }
                    Chunk chunk = {
                        {image[i - 3], image[i - 2]},
                        256 * ((unsigned) image[i - 1]) + (unsigned) image[i] - 2
                    };

                    len_of_chunk = chunk.length;

                    chunks.push_back(chunk);
                    transition = false;
                } else {
                    if (len_of_chunk == -3) {
                        transition = true;
                    } else if (len_of_chunk >= 0) {
                        chunks[chunks.size()-1].content.push_back(image[i]);
                    }
                }

                len_of_chunk--;
            }
        } else {
            if (len_of_chunk > 1) {
                if (!markcmp(image, i - 1, i, EOI)) {
                    chunks[chunks.size()-1].content.push_back(image[i - 1]);
                } else {
                    chunks.push_back(Chunk {
                        { 0xFF, 0xD9 },
                        0
                    });
                    break;
                }
            }

            len_of_chunk++;
        }
    }

    image.clear();
}

void JPEG::PrintHEX() {
    std::cout << chunks.size() << std::endl;
    for (Chunk ch : chunks) {
        std::cout << "Marker of chunk is " << std::hex << (int) ch.marker[0] << ' ' << (int) ch.marker[1] << '\n' << std::dec;
        std::cout << "Length of chunk is " << ch.length << '\n';

        for (unsigned char c : ch.content) {
            std::cout << std::hex << (unsigned) c << ' ';
        }

        std::cout << "\n\n";
    }
}

JPEG::~JPEG() {
    chunks.clear();
}

} // namespace w_jpeg
