// File: RandWriter.hpp
// Project: ps5
// Associated Files: RandWriter.hpp, TextWriter.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/14/2022

#include "RandWriter.hpp"

#include <chrono>
#include <random>
#include <iostream>
#include <stdexcept>
#include <deque>
#include <algorithm>

RandWriter::RandWriter(std::string text, int k1): k(k1) {
    if (k1 < 0) throw std::invalid_argument("k-gram length must be >= 0");
    // instantiate a dequeue to act as a buffer for chars
    std::deque<char> buffer;
    // add the last k + 1 chars to the buffer
    std::size_t i;
    if (text.length() == k) {
        buffer.push_back(text.back());
        i = 0;
    } else {
        i = text.length() - (k + 1);
    }
    for (; i < text.length(); i++) {
        buffer.push_back(text[i]);
    }
    // add every k-gram,
    // treating the text as circular to prevent dead ends
    for (char c : text) {
        buffer.pop_front();
        buffer.push_back(c);
        std::string kgram;
        for (char ch : buffer)
            kgram += ch;
        kgram.pop_back();
        auto kg = &kgrams[kgram];
        kg->total++;
        bool hasChar = false;
        for (auto &i : kg->chars) {
            if (i.character == c) {
                hasChar = true;
                i.freq++;
                break;
            }
        }
        if (!hasChar) {
            kg->chars.push_back(CharFreqPair(c));
            kg->chars.back().freq++;
        }
        if (alpha.find(c) == std::string::npos) alpha.push_back(c);
    }
}

int RandWriter::freq(std::string kgram) const {
    if (kgram.length() != k) {
        throw std::runtime_error("k-gram incorrect length");
    }
    try {
        return kgrams.at(kgram).total;
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

int RandWriter::freq(std::string kgram, char c) const {
    if (kgram.length() != k)
        throw std::runtime_error("k-gram incorrect length");
    try {
        for (auto i : kgrams.at(kgram).chars)
            if (i.character == c) return i.freq;
        return 0;
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

char RandWriter::kRand(std::string kgram) {
    int max = freq(kgram);
    if (max == 0)
        throw std::runtime_error("k-gram \"" + kgram + "\" not found");
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    std::uniform_int_distribution<int> dist(0, max - 1);
    int r = dist(g);
    char c;
    for (auto const& iter : kgrams[kgram].chars) {
        r -= iter.freq;
        if (r < 0) {
            c = iter.character;
            break;
        }
    }
    return c;
}

std::string RandWriter::generate(std::string kgram, int L) {
    std::string full = kgram;
    while (L > 0) {
        char c = kRand(kgram);
        kgram.push_back(c);
        kgram.erase(0, 1);
        full.push_back(c);
        L--;
    }
    return full;
}

std::ostream& operator<<(std::ostream& out, const RandWriter& rw) {
    out << "Order: " << rw.orderK() << std::endl
        << "Alphabet: " << rw.alphabet() << std::endl
        << "K-Grams:" << std::endl;
    for (auto n : rw.kgrams) {
        out << n.first << " (" << n.second.total << ")" << std::endl;
        for (auto m : n.second.chars)
            out << " -" << m.character << " (" << m.freq << ")" << std::endl;
    }
    return out;
}
