// File: FibLFSR.cpp
// Project: ps1a
// Associated Files: FibLFSR.hpp test.cpp main.cpp
// Written by: Nolan Allen
// Last Update: 9/19/2022

#include <iostream>
#include "FibLFSR.hpp"

// read a string into an int array, offset from ascii so that '0' becomes 0
FibLFSR::FibLFSR(std::string seed): index(0), length(seed.length()), ptr(new int[length]) {
	ptr = new int[length];
	for (int i = 0; i < length; i++) { // read the data into the array
		ptr[i] = seed[i] - '0'; // convert from ascii symbolic meaning to int data and store
	}
}

// execute a step to shift the register and assign a new value to the LSB
int FibLFSR::step() {
	int newBit = bit(15) ^ bit(13) ^ bit(12) ^ bit(10); // calculate the value of the bit to be added
	shift(); // shift the register
	setBit(0, newBit); // add the new bit
	return newBit;
}

// execute step k times and return the combined binary value of the results
int FibLFSR::generate(int k) {
	int i = 0;
	for (; k > 0; k--) {
		i = i * 2 + step(); // interpret step() output as digits in a binary number
	}
	return i;
}

// overloaded << operator to send register contents to a stream
std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr) {
	for (int i = lfsr.bitCount() - 1; i >= 0; i--) { // read each bit in the register
			out << lfsr.bit(i);
		}
	return out;
}
