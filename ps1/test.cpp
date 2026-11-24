// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 5/12/2022
// expanded by Nolan Allen for PS1a, 9/19/2022
// expanded by Nolan Allen for PS1b, 9/26/2022

#include <iostream>
#include <string>

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testStepInstr1) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testStepInstr2) {
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l2.generate(9), 51);
}

BOOST_AUTO_TEST_CASE(testOStream) {
  FibLFSR l3("1011011000110110");
  l3.generate(10);
	std::stringstream stream;
  stream << l3;
  BOOST_REQUIRE_EQUAL(stream.str(), "1101100001100110");
}

BOOST_AUTO_TEST_CASE(testBitData) {
  FibLFSR l4("1011011000110110");
  l4.step();
  BOOST_REQUIRE_EQUAL(l4.bitCount(), 16);
  BOOST_REQUIRE_EQUAL(l4.bit(15), 0);
  BOOST_REQUIRE_EQUAL(l4.bit(14), 1);
  BOOST_REQUIRE_EQUAL(l4.bit(13), 1);
  BOOST_REQUIRE_EQUAL(l4.bit(2), 1);
  BOOST_REQUIRE_EQUAL(l4.bit(1), 0);
  BOOST_REQUIRE_EQUAL(l4.bit(0), 0);
}

BOOST_AUTO_TEST_CASE(testEncodeDecode) {
  FibLFSR l1("1011011000110110");
  const int ELEMENTS = 8;
  int original[ELEMENTS] = { 104, 59, 242, 98, 21, 42, 8, 156 },
      encoded[ELEMENTS];
  for (int i = 0; i < ELEMENTS; i++)
      encoded[i] = original[i] ^ l1.generate(8);
  
  FibLFSR l2("1011011000110110");
  int decoded[ELEMENTS];
  for (int i = 0; i < ELEMENTS; i++)
      decoded[i] = encoded[i] ^ l2.generate(8);
  
  BOOST_REQUIRE_EQUAL_COLLECTIONS(original, original + ELEMENTS, decoded, decoded + ELEMENTS);
}
