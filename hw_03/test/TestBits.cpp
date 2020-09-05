#include <random>
#include "doctest.h"
#include "Bits.h"


#include <iostream>

TEST_CASE("testing Bits") {
    SUBCASE("-> testing end-to-end") {
        static constexpr uint64_t TESTS_NUMBER = 100;

        std::mt19937 rnd(120);
        std::uniform_int_distribution<unsigned char> distr(0, 255);
        for (uint64_t i = 0; i < TESTS_NUMBER; i++) {
            unsigned char byte = distr(rnd);
            CHECK(Bits::getFirstByte(Bits::getBitsFromByte(byte)) == byte);
        }
    }
    SUBCASE("-> testing order of bits") {
        CHECK(Bits::getBitsFromByte(154) == Bits::Bits({0, 1, 0, 1, 1, 0, 0, 1}));
        CHECK(Bits::getBitsFromByte(15) == Bits::Bits({1, 1, 1, 1, 0, 0, 0, 0}));

        CHECK(Bits::getFirstByte(Bits::Bits({0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0})) == 36);
    }
    SUBCASE("-> test special cases") {
        CHECK(Bits::getFirstByte({}) == 0);
        CHECK(Bits::getFirstByte(Bits::Bits({1})) == 1);
        CHECK(Bits::getFirstByte(Bits::Bits({1, 1, 1, 1, 1, 1, 1, 1})) == 255);
        
        CHECK(Bits::getBitsFromByte(0) == Bits::Bits({0, 0, 0, 0, 0, 0, 0, 0}));
    }
}