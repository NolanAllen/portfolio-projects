// File: FibLFSR.hpp
// Project: ps1a
// Associated Files: FibLFSR.cpp test.cpp main.cpp
// Written by: Nolan Allen
// Last Update: 9/19/2022

#include <iostream>

class FibLFSR {
 public:
    // Constructor to create LFSR with the given initial seed
    FibLFSR(std::string seed);
    // Destructor to release held memory
    ~FibLFSR() { delete ptr; }
    // Simulate one step and return the new bit as 0 or 1
    int step();
    // Simulate k steps and return a k-bit integer
    int generate(int k);
    // Return the value of the bit at index i in the register
    int bit(int i) const { return ptr[getIndex(i)]; }
    // Return the number of bits in the register
    int bitCount() const { return length; }
 private:
    // Any fields that you need
    int index, length, *ptr;
    // Return the array index of register index i
    int getIndex(int i) const { return (index + length - 1 - i) % length; }
    // Set bit i in the register to the given value
    void setBit(int i, int value) { ptr[getIndex(i)] = value; }
    // Shift the register one position to the left
    void shift() { index = index == length - 1 ? 0 : index + 1; }
};
// Overload the << operator
std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);
