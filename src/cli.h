// Copyright (c) 2023 Emil Fedorov

#ifndef WTCAT_CLI_H_
#define WTCAT_CLI_H_

#include <iostream>

namespace cli
{

void showUsage(const char* name);
    
void parseArgs(int &argc, const char** argv, const char** envp);

} // namespace cli


#endif