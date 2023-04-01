// Copyright (c) 2023 Emil Fedorov


#include <iostream>
#include "cli.h"

namespace cli
{

void showUsage(const char* name) {
    std::cerr << "usage: " << name << " [-v | --version] [-h | --help]"
              << "[-d | --directory]";
}

void parseArgs(const int &argc, const char** argv, const char** envp) {
    if (argc < 2) {
        showUsage(argv[0]);
    }
}

    
} // namespace cli
