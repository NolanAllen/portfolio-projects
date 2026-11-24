// File: RandWriter.hpp
// Project: ps5
// Associated Files: RandWriter.hpp, TextWriter.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/14/2022

#ifndef RANDWRITER_HPP_
#define RANDWRITER_HPP_

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>

class RandWriter {
 public:
    // Create a Markov model of order k from given text
    // Assume that text has length at least k.
    RandWriter(std::string text, int k);

    int orderK() const { return k; }  // Order k of Markov model

    // Number of occurences of kgram in text
    // Throw an exception if kgram is not length k
    int freq(std::string kgram) const;
    // Number of times that character c follows kgram
    // if order=0, return num of times that char c appears
    // (throw an exception if kgram is not of length k)
    int freq(std::string kgram, char c) const;

    // Random character following given kgram
    // (throw an exception if kgram is not of length k)
    // (throw an exception if no such kgram)
    char kRand(std::string kgram);

    // Generate a string of length L characters by simulating a trajectory
    // through the corresponding Markov chain.  The first k characters of
    // the newly generated string should be the argument kgram.
    // Throw an excpetion if kgram is not of length k.
    // Assume that L is at least k
    std::string generate(std::string kgram, int L);

    std::string alphabet() const { return alpha; }

 private:
    const std::size_t k;
    std::string alpha;
    struct CharFreqPair {
     public:
        explicit CharFreqPair(char c): character(c), freq(0) {}
        char character;
        std::size_t freq;
    };
    struct ItemsTotalPair {
     public:
        ItemsTotalPair(): total(0) {}
        std::vector<CharFreqPair> chars;
        std::size_t total;
    };
    std::unordered_map<std::string, ItemsTotalPair> kgrams;
    friend std::ostream & operator<<(std::ostream &os, const RandWriter& rw);
};
// Overload the stream insertion operator << and display the internal state
// of the Markov model.  Print out the order, alphabet, and the frequencies
// of the k-grams and k+1-grams
std::ostream& operator<<(std::ostream&, const RandWriter& rw);

#endif  // RANDWRITER_HPP_
