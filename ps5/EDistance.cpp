// File: EDistance.cpp
// Project: ps5
// Associated Files: EDistance.hpp, main.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/7/2022

#include "EDistance.hpp"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <stdexcept>

EDistance::EDistance(std::string s1, std::string s2):
    s1(s1), s2(s2), matrix(new int[(s1.size() + 1) * (s2.size() + 1)]) {}

int EDistance::optDistance() {
    // initialize bottom right corner
    int i = (s1.size() + 1) * (s2.size() + 1) - 1;
    matrix[i] = 0;
    // initialize bottom row
    for (std::size_t j = 1; j < s2.size() + 1; j++) {
        i--;
        matrix[i] = matrix[i + 1] + 2;
    }
    // fill in remaining elements
    for (std::size_t j = s1.size(); j > 0; j--) {
        i--;
        matrix[i] = matrix[i + s2.size() + 1] + 2;
        for (std::size_t k = s2.size(); k > 0; k--) {
            i--;
            matrix[i] = min(matrix[i + s2.size() + 2]
                            + penalty(s1[j-1], s2[k-1]),
                            matrix[i + 1] + 2,
                            matrix[i + s2.size() + 1] + 2);
        }
    }
    // return top left corner
    return matrix[0];
}

std::string EDistance::alignment() {
    std::string result;
    auto rowNum = [&, this](int i) { return i / (s2.size() + 1); };
    auto colNum = [&, this](int i) { return i % (s2.size() + 1); };
    const int lastIndex = (s1.size() + 1) * (s2.size() + 1) - 1;
    int i = 0;
    while (i < lastIndex) {
        int cost = penalty(s1[rowNum(i)], s2[colNum(i)]);
        bool isLastRow = rowNum(i) == s1.size() + 1,
             isLastCol = colNum(i) == s2.size() + 1;
        if (!isLastCol && !isLastRow
                && matrix[i] == matrix[i + s2.size() + 2] + cost) {
            result += s1[i / (s2.size() + 1)];
            result += ' ';
            result += s2[i % (s2.size() + 1)];
            result += ' ';
            result += '0' + cost;
            i += s2.size() + 2;
        } else if (!isLastRow && matrix[i] == matrix[i + s2.size() + 1] + 2) {
            result += s1[i / (s2.size() + 1)];
            result += " - 2";
            i += s2.size() + 1;
        } else if (!isLastCol && matrix[i] == matrix[i + 1] + 2) {
            result += "- ";
            result += s2[i % (s2.size() + 1)];
            result += " 2";
            i++;
        } else {
            throw std::runtime_error("matrix data corrupted");
        }
        result += '\n';
    }
    if (i != lastIndex)
        throw std::runtime_error("alignment index out of bounds, "
                "data unreliable");
    return result;
}

void EDistance::printMatrix() const {
    std::cout << "   ";
    for (std::size_t i = 0; i < (s2.size()); i++)
        std::cout << s2[i] << "  ";
    std::cout << "-";
    for (std::size_t i = 0; i < (s1.size() + 1) * (s2.size() + 1); i++) {
        if (i == (s1.size()) * (s2.size() + 1))
            std::cout << std::endl << '-';
        else if (i % (s2.size() + 1) == 0)
            std::cout << std::endl << s1[i / (s2.size() + 1)];
        std::cout << std::setw(3) << matrix[i];
    }
    std::cout << std::endl;
    return;
}
