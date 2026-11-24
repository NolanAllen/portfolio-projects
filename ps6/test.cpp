// File: test.cpp
// Project: ps3a
// Associated Files: RandWriter.cpp RandWriter.hpp TextWriter.cpp
//  RandWordWriter.hpp, RandWordWriter.cpp WordWriter.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/12/2022

#include <stdexcept>
#include <string>
#include "RandWriter.hpp"
#include "RandWordWriter.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include <boost/regex.hpp>

BOOST_AUTO_TEST_CASE(testConstructor) {
  BOOST_REQUIRE_THROW(RandWriter("abcac", -2), std::invalid_argument);
  BOOST_REQUIRE_THROW(RandWriter("abcac", -1), std::invalid_argument);
  BOOST_REQUIRE_NO_THROW(RandWriter("abcac", 0));
  BOOST_REQUIRE_NO_THROW(RandWriter("abcac", 1));
  BOOST_REQUIRE_NO_THROW(RandWriter("abcac", 2));
  RandWriter rw0("gagggagaggcgagaaa", 0);
  BOOST_REQUIRE_EQUAL(rw0.orderK(), 0);
  RandWriter rw1("gagggagaggcgagaaa", 1);
  BOOST_REQUIRE_EQUAL(rw1.orderK(), 1);
  RandWriter rw2("gagggagaggcgagaaa", 2);
  BOOST_REQUIRE_EQUAL(rw2.orderK(), 2);

  std::string str("Hello! How are you? I am well.");
  BOOST_REQUIRE_THROW(RandWordWriter(str, -2), std::invalid_argument);
  BOOST_REQUIRE_THROW(RandWordWriter(str, -1), std::invalid_argument);
  BOOST_REQUIRE_NO_THROW(RandWordWriter(str, 0));
  BOOST_REQUIRE_NO_THROW(RandWordWriter(str, 1));
  BOOST_REQUIRE_NO_THROW(RandWordWriter(str, 2));
}

BOOST_AUTO_TEST_CASE(testFreq) {
  RandWriter rw1("gagggagaggcgagaaa", 2);
  BOOST_REQUIRE_EQUAL(rw1.freq("ga"), 5);
  BOOST_REQUIRE_EQUAL(rw1.freq("ag"), 5);
  BOOST_REQUIRE_EQUAL(rw1.freq("gg"), 3);
  BOOST_REQUIRE_EQUAL(rw1.freq("gc"), 1);
  BOOST_REQUIRE_EQUAL(rw1.freq("cg"), 1);
  BOOST_REQUIRE_EQUAL(rw1.freq("aa"), 2);
  BOOST_REQUIRE_EQUAL(rw1.freq("ac"), 0);
  BOOST_REQUIRE_THROW(rw1.freq("g"), std::runtime_error);
  BOOST_REQUIRE_THROW(rw1.freq("gaa"), std::runtime_error);
  BOOST_REQUIRE_EQUAL(rw1.freq("ga", 'g'), 4);
  BOOST_REQUIRE_EQUAL(rw1.freq("ga", 'a'), 1);
  BOOST_REQUIRE_EQUAL(rw1.freq("ga", 'c'), 0);
  BOOST_REQUIRE_THROW(rw1.freq("g", 'a'), std::runtime_error);
  BOOST_REQUIRE_THROW(rw1.freq("gaaa", 'g'), std::runtime_error);
  RandWriter rw2("gagggagaggcgagaaa", 0);
  BOOST_REQUIRE_EQUAL(rw2.freq(""), 17);
  BOOST_REQUIRE_THROW(rw2.freq("a"), std::runtime_error);
  BOOST_REQUIRE_EQUAL(rw2.freq("", 'g'), 9);
  BOOST_REQUIRE_EQUAL(rw2.freq("", 'a'), 7);
  BOOST_REQUIRE_EQUAL(rw2.freq("", 'c'), 1);
  BOOST_REQUIRE_THROW(rw2.freq("gc", 'g'), std::runtime_error);

  RandWordWriter rww1("You, you, you ought to know", 1);
  BOOST_REQUIRE_EQUAL(rww1.freq("You, "), 1);
  BOOST_REQUIRE_EQUAL(rww1.freq("you, "), 1);
  BOOST_REQUIRE_EQUAL(rww1.freq("you "), 1);
  BOOST_REQUIRE_EQUAL(rww1.freq("you ", "ought"), 0);
  BOOST_REQUIRE_EQUAL(rww1.freq("you ", "ought "), 1);
  RandWordWriter rww2("Hello! How are you? How are you doing?", 2);
  BOOST_REQUIRE_EQUAL(rww2.freq("How are "), 2);
  BOOST_REQUIRE_EQUAL(rww2.freq("are you? "), 1);
  BOOST_REQUIRE_EQUAL(rww2.freq("How are ", "you? "), 1);
  BOOST_REQUIRE_EQUAL(rww2.freq("How are ", "you "), 1);
}

BOOST_AUTO_TEST_CASE(testAlphabet) {
  RandWriter rw1("abcac", 0),
             rw2("gagggagaggcgagaaa", 5);
  BOOST_REQUIRE_EQUAL(rw1.alphabet(), "abc");
  BOOST_REQUIRE_EQUAL(rw2.alphabet(), "gac");

  RandWordWriter rww("Hello! How are you? I am well.", 3);
  BOOST_REQUIRE_EQUAL(rww.alphabet(),
  "Hello! \n"
  "How \n"
  "are \n"
  "you? \n"
  "I \n"
  "am \n"
  "well.\n");
  BOOST_REQUIRE_EQUAL(rww.getValidSeed(), "Hello! How are ");
}

BOOST_AUTO_TEST_CASE(testGeneration) {
  RandWriter rw1("gagggagaggcgagaaa", 2);
  BOOST_REGEX_MATCH_HPP(rw1.kRand("ag"), "[ag]");
  BOOST_REGEX_MATCH_HPP(rw1.kRand("gc"), "g");
  BOOST_REQUIRE_THROW(rw1.kRand("g"), std::runtime_error);
  BOOST_REQUIRE_THROW(rw1.kRand("ggc"), std::runtime_error);
  BOOST_REGEX_MATCH_HPP(rw1.generate("ga", 2), "ga[(g[gac])(a[ag])]");
  BOOST_REQUIRE_THROW(rw1.generate("g", 2), std::runtime_error);
  BOOST_REQUIRE_THROW(rw1.generate("ggc", 2), std::runtime_error);
  RandWriter rw2("abcacbca", 3);
  BOOST_REGEX_MATCH_HPP(rw2.generate("abc", 3), "abca[ca]b");

  RandWordWriter rww1("I am here. How are you? How am I?", 1);
  BOOST_REGEX_MATCH_HPP(rww1.kRand("am "), "[(here.)(I?)]");
  RandWordWriter rww2("Here are those. Here are you. Here are we.", 2);
  BOOST_REGEX_MATCH_HPP(rww2.generate("Here are ", 3),
      "Here are [(those. )(you. )(we.)]Here ");
}
