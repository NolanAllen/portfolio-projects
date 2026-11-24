// File: StringSound.cpp
// Project: ps3b
// Associated Files: CircularBuffer.hpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/17/2022

#include "StringSound.hpp"
#include <chrono>
#include <random>
#include <iostream>

StringSound::StringSound(double frequency):
        buffer(new CircularBuffer<sf::Int16>(ceil(44100.0 / frequency))),
        tickFunc(guitarTickFunc),
        tickCount(0) {
    if (ceil(44100.0 / frequency) < 2)
        throw std::invalid_argument(
            "StringSound initial number of samples must not be < 2.");
    while (!buffer->isFull()) buffer->enqueue(0);
}

StringSound::StringSound(std::vector<sf::Int16> init):
        buffer(new CircularBuffer<sf::Int16>(init.size())),
        tickFunc(guitarTickFunc),
        tickCount(0) {
    if (init.size() < 2)
        throw std::invalid_argument(
            "StringSound initial number of samples must not be < 2.");
    for (auto i : init) buffer->enqueue(i);
}

void StringSound::pluck() {
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 g1(seed);
    buffer->forEach([&g1](sf::Int16 &x) { x = g1(); });
}

void StringSound::tick() {
    auto i = tickFunc(buffer);
    if (buffer->isFull()) buffer->dequeue();
    buffer->enqueue(i);
    tickCount++;
}

void StringSound::setTickFunc(
    sf::Int16 (*tickFunc)(std::shared_ptr<CircularBuffer<sf::Int16>>)
) {
    this->tickFunc = tickFunc;
}

sf::Int16 guitarTickFunc(std::shared_ptr<CircularBuffer<sf::Int16>> buffer) {
    return 0.996 * 0.5 * (buffer->dequeue() + buffer->peek());
}

sf::Int16 StringSound::sample() const {
    return buffer->peek();
}

size_t StringSound::time() const {
    return tickCount;
}
