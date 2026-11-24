// File: EDistance.hpp
// Project: ps5
// Associated Files: EDistance.hpp, main.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/7/2022

#ifndef EDISTANCE_HPP_
#define EDISTANCE_HPP_

#include <algorithm>
#include <string>

class EDistance {
 public:
    EDistance(std::string s1, std::string s2);
    ~EDistance() { delete [] matrix; }
    int optDistance();
    std::string alignment();
    void printMatrix() const;
 private:
    int penalty(char a, char b) const { return a != b; }
    // 3-input min function using two std::mins tends to be slower than two ifs
//  int min(int a, int b, int c) const { return std::min(a, std::min(b, c)); }
    int min(int a, int b, int c) const {
        if (a <= b && a <= c)
            return a;
        if (b <= a && b <= c)
            return b;
        return c;
    }
    std::string s1, s2;
    int * matrix;
};

#endif  // EDISTANCE_HPP_
