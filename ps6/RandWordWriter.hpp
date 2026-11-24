// File: RandWordWriter.hpp
// Project: ps5
// Associated Files: RandWordWriter.hpp, WordWriter.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/14/2022

#ifndef RANDWORDWRITER_HPP_
#define RANDWORDWRITER_HPP_

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>

class RandWordWriter {
 public:
    // Create a Markov model of order k from given text
    // Assume that text has length at least k.
    RandWordWriter(std::string text, int k);

    int orderK() const { return k; }  // Order k of Markov model

    // Number of occurences of kgram in text
    int freq(std::string kgram) const;
    // Number of times that character c follows kgram
    // if order=0, return num of times that char c appears
    int freq(std::string kgram, std::string w) const;

    // Random character following given kgram
    std::string kRand(std::string kgram);

    // Generate a string of length L characters by simulating a trajectory
    // through the corresponding Markov chain.  The first k characters of
    // the newly generated string should be the argument kgram.
    // Assume that L is at least k
    std::string generate(std::string kgram, int L);

    std::string alphabet() const;

    std::string getValidSeed() const { return validSeed; }

 private:
    const std::size_t k;
    std::vector<std::string> alpha;
    const std::string whitespace;
    std::string validSeed;
    struct StrFreqPair {
     public:
        explicit StrFreqPair(std::string w): word(w), freq(0) {}
        std::string word;
        std::size_t freq;
    };
    struct ItemsTotalPair {
     public:
        ItemsTotalPair(): total(0) {}
        std::vector<StrFreqPair> words;
        std::size_t total;
    };
    std::unordered_map<std::string, ItemsTotalPair> kgrams;
    friend std::ostream & operator<<(std::ostream &os,
         const RandWordWriter& rw);
};
// Overload the stream insertion operator << and display the internal state
// of the Markov model.  Print out the order, alphabet, and the frequencies
// of the k-grams and k+1-grams
std::ostream& operator<<(std::ostream&, const RandWordWriter& rw);

#endif  // RANDWORDWRITER_HPP_
