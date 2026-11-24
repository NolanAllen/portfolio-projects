// File: TextWriter.cpp
// Project: ps5
// Associated Files: RandWriter.hpp, RandWriter.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/14/2022

#include <fstream>
#include <sstream>
#include <iostream>
#include "RandWriter.hpp"


int main(int argc, char **argv) {
    char *garbage;
    int L = std::strtol(argv[1], &garbage, 0),
        k = std::strtol(argv[2], &garbage, 0);

    std::stringstream buffer;
    buffer << std::cin.rdbuf();
    RandWriter writer(buffer.str(), k);
    std::cout << writer.generate(buffer.str().substr(0, k), L) << std::endl;

    return 0;
}
