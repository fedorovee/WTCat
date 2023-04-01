// Copyright (c) 2023 Emil Fedorov
#pragma once

#ifndef WTCAT_CLI_H_
#define WTCAT_CLI_H_

#include <iostream>
#include <map>
#include <string>

namespace cli
{
    
void showHelp();

void showAbout();

bool getOpt(const int&, const char**, std::map<char, std::string>&);

} // namespace cli


#endif