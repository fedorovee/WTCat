// Copyright (c) 2023 Emil Fedorov

#include "cli.h"
#include "about.h"

#define OPTCMP(i, s, shs)       !std::strcmp(argv[i], s) || !std::strcmp(argv[i], shs)
#define ITERFAIL                iExit = false, options_got = false

namespace cli
{

void showHelp() {
    const char* helpMessage = 
        "\n Usage: wtcat [options]\n\n "
        "-h, --help \t\t\t\tShow help.\n "
        "-v, --version \t\t\t\tShow version and about.\n "
        "-f, --format <picture format> \t\tSpecify format of output pictures.\n "
        "-d, --directory <path> \t\tSet folder for concatenating contain pictures.\n";

    std::cerr << helpMessage;
}

void showAbout() {
    const char* aboutMessage = 
        "\n wtcat version " WTCAT_VERSION_STR "\n "
        "author: Emil Fedorov (fedorovee)\n "
        "repo: https://github.com/fedorovee/WTCat\n";

    std::cout << aboutMessage;
}

bool getOpt(const int& argc, const char** argv, std::map<char, std::string>& opt) {
    
    char option;
    bool next_is_value = false;
    bool iExit = false;
    bool options_got = true;

    for (int i = 1; i < argc && !iExit; i++) {
        if(OPTCMP(i, "--version", "-v")) {
            showAbout();
            ITERFAIL;
        } else if (OPTCMP(i, "--help", "-h")) {
            showHelp();
            ITERFAIL;
        } else if (OPTCMP(i, "--directory", "-d")) {
            if (i == argc - 1) {
                showHelp();
                ITERFAIL;
            } else {
                option = 'd';
                next_is_value = true;
            }
        } else if (OPTCMP(i, "--format", "-f")) {
            if (i == argc - 1) {
                showHelp();
                ITERFAIL;
            } else {
                option = 'f';
                next_is_value = true;
            }
        } else if (next_is_value) {
            opt[option] = argv[i];
            next_is_value = false;
        } else {
            showHelp();
            ITERFAIL;
        }
    }

    return options_got;
}

} // namespace cli
