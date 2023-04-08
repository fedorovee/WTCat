/*
 * Copyrigth (c) 2023 feerus23
 *
 * Webtoon concatenator / shortly WTCat.
 * 
 * Wtcat is an opensource project for vertical concatenating images (sliced pages) of webtoons
 * or manhwa.
 * 
 */

#include "w_jpeg.h"
#include <iostream>
#include <fstream>
#include <ios>

int main(int argc, const char** argv) {
    if (argc < 2) {
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    w_jpeg::JPEG JFIF_FILE(file);

    if (JFIF_FILE.GetInitCode() == 0) {
        std::cout << "Deb#1\n";
        JFIF_FILE.PrintHEX();
    } else {
        std::cerr << "Init error: " << JFIF_FILE.GetInitCode();
    }

    return 0;
}