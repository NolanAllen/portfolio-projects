// File: WordWriter.cpp
// Project: ps5
// Associated Files: RandWordWriter.hpp, RandWordWriter.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/14/2022

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "RandWordWriter.hpp"


int main(int argc, char **argv) {
    char *garbage;
    int L = std::strtol(argv[1], &garbage, 0),
        k = std::strtol(argv[2], &garbage, 0);

    std::stringstream buffer;
    buffer << std::cin.rdbuf();
    RandWordWriter writer(buffer.str(), k);
    /**/
    std::cout << writer.generate(writer.getValidSeed(), L) << std::endl;

    return 0;
}
