// File: CircularBuffer.hpp
// Project: ps3a
// Associated Files: test.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/12/2022

#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

#include <stdlib.h>
#include <stdexcept>
#include <deque>
#include <functional>
#include <iostream>

template<typename T>
class CircularBuffer {
 public:
    // Create an empty ring buffer with given max capacity
    explicit CircularBuffer(size_t capacity);
    size_t size() const;  // The number of items currently in the buffer
    bool isEmpty() const;  // Is the buffer is empty?
    bool isFull() const;  // Is the buffer full?
    void enqueue(T item);  // Add item to the end
    T dequeue();  // Delete and return item from the front
    T peek() const;  // Return (but do not delete) item from the front
    // Apply a given function to each item
    void forEach(std::function<void(T&)> func);
 private:
    size_t capacity;
    std::deque<T> buffer;
};

template<typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity) {
    if (capacity < 1)
        throw std::invalid_argument("CircularBuffer capacity must not be < 1.");
    this->capacity = capacity;
}

template<typename T>
size_t CircularBuffer<T>::size() const {
    return buffer.size();
}

template<typename T>
bool CircularBuffer<T>::isEmpty() const {
    return buffer.empty();
}

template<typename T>
bool CircularBuffer<T>::isFull() const {
    return buffer.size() == capacity;
}

template<typename T>
void CircularBuffer<T>::enqueue(T item) {
    if (isFull())
        throw std::runtime_error("CircularBuffer is full; can't enqueue.");
    buffer.push_back(item);
}

template<typename T>
T CircularBuffer<T>::dequeue() {
    if (isEmpty())
        throw std::runtime_error("CircularBuffer is empty; can't dequeue.");
    T hold = peek();
    buffer.pop_front();
    return hold;
}

template<typename T>
T CircularBuffer<T>::peek() const {
    if (isEmpty())
        throw std::runtime_error("CircularBuffer is empty; can't peek.");
    return buffer.front();
}

template<typename T>
void CircularBuffer<T>::forEach(std::function<void(T&)> func) {
    for (size_t i = 0; i < size(); i++)
        func(buffer[i]);
}

#endif  // CIRCULARBUFFER_HPP_
