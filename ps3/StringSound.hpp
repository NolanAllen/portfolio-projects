// File: StringSound.hpp
// Project: ps3b
// Associated Files: CircularBuffer.hpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/17/2022

#ifndef STRINGSOUND_HPP_
#define STRINGSOUND_HPP_

#include <stdlib.h>
#include <vector>
#include <functional>
#include <memory>
#include <SFML/System.hpp>
#include "CircularBuffer.hpp"

sf::Int16 guitarTickFunc(std::shared_ptr<CircularBuffer<sf::Int16>> buffer);

class StringSound {
 public:
    // Create a guitar string sound of the given frequency using a sampling rate
    // of 44,100
    explicit StringSound(double frequency);
    // Create a guitar string with size and initial values given by the vector
    explicit StringSound(std::vector<sf::Int16> init);
    StringSound(const StringSound& obj) = delete;  // No copy constructor
    // Pluck the guitar string by replacing the buffer with random values,
    // representing the white noise
    void pluck();
    void tick();  // Advance the simulation one time step
    // Set the function used in the tick function
    void setTickFunc(
      sf::Int16 (*tickFunc)(std::shared_ptr<CircularBuffer<sf::Int16>>));
    sf::Int16 sample() const;  // Return the current sample
    size_t time() const;  // Return the number of times tick was called so far
 private:
    std::shared_ptr<CircularBuffer<sf::Int16>> buffer;
    sf::Int16 (*tickFunc)(std::shared_ptr<CircularBuffer<sf::Int16>>);
    size_t tickCount;
};

#endif  // STRINGSOUND_HPP_
