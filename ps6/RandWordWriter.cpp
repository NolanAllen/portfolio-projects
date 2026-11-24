// File: RandWordWriter.hpp
// Project: ps5
// Associated Files: RandWordWriter.hpp, TextWriter.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/14/2022

#include "RandWordWriter.hpp"

#include <chrono>
#include <random>
#include <iostream>
#include <stdexcept>
#include <deque>
#include <algorithm>

RandWordWriter::RandWordWriter(std::string text, int k1):
        k(k1), whitespace(" ,.?!()[]/\n\r") {
    if (k1 < 0) throw std::invalid_argument("k-gram length must be >= 0");
    // instantiate a dequeue to act as a buffer for words
    std::deque<std::string> buffer;
    // find the initial index of the last k + 1 words
    std::size_t i = text.length() - 1;
    for (std::size_t j = 0; j < k; j++) {  // find k + 1 words
        // find non-whitespace
        while (whitespace.find(text[i]) != std::string::npos) {
            i--;
        }
        // find whitespace
        while (whitespace.find(text[i]) == std::string::npos) {
            i--;
        }
    }
    // add the last k + 1 words to the buffer
    while (i < text.length()) {
        std::string word;
        while (whitespace.find(text[i]) == std::string::npos) {
            word.push_back(text[i]);
            i++;
            if (i == text.length()) break;
        }
        while (whitespace.find(text[i]) != std::string::npos) {
            word.push_back(text[i]);
            i++;
            if (i == text.length()) break;
        }
        buffer.push_back(word);
    }
    // store every k-word string,
    // treating the text as circular to prevent dead ends
    i = 0;
    while (i < text.length()) {
        buffer.pop_front();
        std::string word;
        while (whitespace.find(text[i]) == std::string::npos) {
            word.push_back(text[i]);
            i++;
            if (i == text.length()) break;
        }
        while (whitespace.find(text[i]) != std::string::npos) {
            word.push_back(text[i]);
            i++;
            if (i == text.length()) break;
        }
        buffer.push_back(word);
        std::string kword;
        for (std::size_t i = 0; i < buffer.size() - 1; i++)
            kword += buffer[i];
        auto kw = &kgrams[kword];
        kw->total++;
        bool hasWord = false;
        for (auto &i : kw->words) {
            if (i.word == word) {
                hasWord = true;
                i.freq++;
                break;
            }
        }
        if (!hasWord) {
            kw->words.push_back(StrFreqPair(word));
            kw->words.back().freq++;
        }
        if (std::find_if(alpha.begin(), alpha.end(),
                [&word](std::string w) { return w == word; })
                == alpha.end())
            alpha.push_back(word);
    }
    // get a valid seed to be used as a parameter
    // to the generate() function
    i = 0;
    for (std::size_t j = 0; j < k; j++) {
        std::string word;
        while (whitespace.find(text[i]) == std::string::npos) {
            word.push_back(text[i]);
            i++;
            if (i == text.length()) break;
        }
        while (whitespace.find(text[i]) != std::string::npos) {
            word.push_back(text[i]);
            i++;
            if (i == text.length()) break;
        }
        validSeed += word;
    }
}

int RandWordWriter::freq(std::string kgram) const {
    try {
        return kgrams.at(kgram).total;
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

int RandWordWriter::freq(std::string kgram, std::string w) const {
    try {
        for (auto i : kgrams.at(kgram).words)
            if (i.word == w) return i.freq;
        return 0;
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

std::string RandWordWriter::kRand(std::string kgram) {
    int max = freq(kgram);
    if (max == 0)
        throw std::runtime_error("k-gram \"" + kgram + "\" not found");
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    std::uniform_int_distribution<int> dist(0, max - 1);
    int r = dist(g);
    std::string word;
    for (auto const& iter : kgrams[kgram].words) {
        r -= iter.freq;
        if (r < 0) {
            word = iter.word;
            break;
        }
    }
    return word;
}

std::string RandWordWriter::generate(std::string kgram, int L) {
    std::string full = kgram;
    while (L > 0) {
        std::string word = kRand(kgram);
        kgram += word;
        int i = 0;
        while (whitespace.find(kgram[i]) == std::string::npos) i++;
        while (whitespace.find(kgram[i]) != std::string::npos) i++;
        kgram.erase(0, i);
        full += word;
        L--;
    }
    return full;
}

std::string RandWordWriter::alphabet() const {
    std::string str;
    for (auto word : alpha)
        str += word + "\n";
    return str;
}

std::ostream& operator<<(std::ostream& out, const RandWordWriter& rw) {
    out << "Order: " << rw.orderK() << std::endl
        << "Words:" << std::endl
        << rw.alphabet()
        << "K-Grams:" << std::endl;
    for (auto n : rw.kgrams) {
        out << n.first << " (" << n.second.total << ")" << std::endl;
        for (auto m : n.second.words)
            out << " -" << m.word << " (" << m.freq << ")" << std::endl;
    }
    return out;
}
