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

#include <iostream>
#include "cli.h"

int main(int argc, const char** argv) {
    if (argc < 2) {
        cli::showHelp();
        return 1;
    }

    std::map<char, std::string> options;

    if (cli::getOpt(argc, argv, options)) {
        for (const auto& [key, value] : options) {
            std::cout << key << ' ' << value << '\n'; // Test
        }
    }

    return 0;
}