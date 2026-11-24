// File: CircularBuffer.hpp
// Project: ps3a
// Associated Files: CircularBuffer.hpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/12/2022

#include <stdexcept>
#include <string>
#include "CircularBuffer.hpp"
#include "StringSound.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testStatistics) {
  CircularBuffer<bool> cb(2);
  BOOST_REQUIRE(cb.isEmpty());
  BOOST_REQUIRE(!cb.isFull());
  BOOST_REQUIRE_EQUAL(cb.size(), 0);
  cb.enqueue(true);
  BOOST_REQUIRE(!cb.isEmpty());
  BOOST_REQUIRE(!cb.isFull());
  BOOST_REQUIRE_EQUAL(cb.size(), 1);
  cb.enqueue(false);
  BOOST_REQUIRE(!cb.isEmpty());
  BOOST_REQUIRE(cb.isFull());
  BOOST_REQUIRE_EQUAL(cb.size(), 2);
  cb.dequeue();
  BOOST_REQUIRE(!cb.isEmpty());
  BOOST_REQUIRE(!cb.isFull());
  BOOST_REQUIRE_EQUAL(cb.size(), 1);
  cb.dequeue();
  BOOST_REQUIRE(cb.isEmpty());
  BOOST_REQUIRE(!cb.isFull());
  BOOST_REQUIRE_EQUAL(cb.size(), 0);
}

BOOST_AUTO_TEST_CASE(testContent) {
  CircularBuffer<std::string> cb(3);
  cb.enqueue("Test 1");
  BOOST_REQUIRE_EQUAL(cb.peek(), "Test 1");
  cb.enqueue("Test 2");
  BOOST_REQUIRE_EQUAL(cb.peek(), "Test 1");
  cb.enqueue("Test 3");
  BOOST_REQUIRE_EQUAL(cb.peek(), "Test 1");
  BOOST_REQUIRE_EQUAL(cb.dequeue(), "Test 1");
  BOOST_REQUIRE_EQUAL(cb.peek(), "Test 2");
  BOOST_REQUIRE_EQUAL(cb.dequeue(), "Test 2");
  BOOST_REQUIRE_EQUAL(cb.peek(), "Test 3");
  BOOST_REQUIRE_EQUAL(cb.dequeue(), "Test 3");
}

BOOST_AUTO_TEST_CASE(testExceptions) {
  CircularBuffer<float> cb(3);
  BOOST_REQUIRE_THROW(CircularBuffer<int> cb2(0), std::invalid_argument);
  BOOST_REQUIRE_NO_THROW(CircularBuffer<int> cb2(1));
  BOOST_REQUIRE_NO_THROW(CircularBuffer<int> cb2(2));
  BOOST_REQUIRE_THROW(cb.peek(), std::runtime_error);
  BOOST_REQUIRE_THROW(cb.dequeue(), std::runtime_error);
  cb.enqueue(1.5);
  cb.enqueue(2.5);
  cb.enqueue(3.5);
  BOOST_REQUIRE_THROW(cb.enqueue(4.5), std::runtime_error);
  cb.dequeue();
  cb.dequeue();
  cb.dequeue();
  BOOST_REQUIRE_THROW(cb.dequeue(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(testForEach) {
  CircularBuffer<char> cb(4);
  cb.enqueue('a');
  cb.enqueue('b');
  cb.enqueue('C');
  cb.enqueue('d');
  cb.forEach([](char& x) -> void {
      if ('a' <= x && x <= 'z') x = x + 'A' - 'a';
    });
  BOOST_REQUIRE_EQUAL(cb.dequeue(), 'A');
  BOOST_REQUIRE_EQUAL(cb.dequeue(), 'B');
  BOOST_REQUIRE_EQUAL(cb.dequeue(), 'C');
  BOOST_REQUIRE_EQUAL(cb.dequeue(), 'D');
}

BOOST_AUTO_TEST_CASE(testStringSoundExceptions) {
  std::vector<sf::Int16> v1;
  BOOST_REQUIRE_THROW(StringSound s(v1), std::invalid_argument);
  std::vector<sf::Int16> v2 = { 1 };
  BOOST_REQUIRE_THROW(StringSound s(v2), std::invalid_argument);
  std::vector<sf::Int16> v3 = { 1, 2 };
  BOOST_REQUIRE_NO_THROW(StringSound s(v3));
  BOOST_REQUIRE_THROW(StringSound s(0.0), std::invalid_argument);
  BOOST_REQUIRE_NO_THROW(StringSound s(220.0));
}

BOOST_AUTO_TEST_CASE(testStringSoundContent) {
  std::vector<sf::Int16> v1 = { 1, 2, 3 },
                         v2;
  StringSound s1(v1);
  for (auto i : v1) {
    BOOST_REQUIRE_EQUAL(s1.sample(), i);
    s1.tick();
  }
  StringSound s2(220.0);
  BOOST_REQUIRE_EQUAL(s2.sample(), 0);
  s2.tick();
  BOOST_REQUIRE_EQUAL(s2.sample(), 0);
  s2.tick();
  BOOST_REQUIRE_EQUAL(s2.sample(), 0);
  BOOST_REQUIRE_EQUAL(s2.time(), 2);
}

BOOST_AUTO_TEST_CASE(testStringSoundDataProcessing) {
  StringSound s2(220.0);
  s2.pluck();
  int differenceCount = 0;
  for (int i = 0; i < 201; i++) {
    if (s2.sample() != 0) differenceCount++;
    s2.tick();
  }
  BOOST_REQUIRE_GT(differenceCount, 190);
  s2.setTickFunc(
    [](std::shared_ptr<CircularBuffer<sf::Int16>> buffer) -> sf::Int16 {
      static sf::Int16 i = 0;
      return i++;
    });
  for (int i = 0; i < 201 * 5; i++) s2.tick();
  for (int i = 0; i < 201; ++i) {
    BOOST_REQUIRE_NE(s2.sample(), i);
    s2.tick();
  }
}
