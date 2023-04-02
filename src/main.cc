/* Copyright (c) 2023 Emil Fedorov
 *
 * Webtoon Concatenator or simply WTCat.
 * 
 * WTCat is an open-source and, I hope, cross-platfrom application
 * for concatenating sliced images of Webtoon pages.
 * 
 * Perhaps in the future I'll develop full toolkit for downloading
 * and preparing webtoons for scanlating.
 * 
 */

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#elif
    #include <unistd.h>
#endif

#include <iostream>
#include <filesystem>
#include "cli.h"
#include "jpg/decoder.h"

int main(int argc, const char** argv) {
    if (argc < 2) {
        //cli::showHelp();
        //return 1;
    }

    char cur_dir[256];
    getcwd(cur_dir, 256);

    for (int i = 1; i < argc; i++) {
        jpegUtils::JPEG Image(argv[i]);
        std::cout << argv[i] << '\n';
        Image.PrintHexTable();
    }

    std::map<char, std::string> options;

    // if (cli::getOpt(argc, argv, options)) {
    //     for (const auto& [key, value] : options) {
    //         std::cout << key << ' ' << value << '\n'; // Test
    //     }
    // }
    return 0;
}