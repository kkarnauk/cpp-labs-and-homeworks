#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include "doctest.h"
#include "HuffmanArchiver.h"

using namespace Huffman::Archiver;

TEST_CASE("testing Huffman Archiver") {
    auto checkTextEndToEnd = [](const std::string& text) {
        std::stringstream input;
        std::stringstream compressedOut;
        std::stringstream extractedOut;
        input << text;

        Archiver compressing(input, compressedOut);
        Statistics compressedStats = compressing.compress();

        CHECK(compressedStats.finalDataSize + compressedStats.extraDataSize == compressedOut.str().size());

        Archiver extracting(compressedOut, extractedOut);
        Statistics extractedStats = extracting.extract();

        CHECK(extractedOut.str() == text);
        CHECK(text.size() == extractedStats.finalDataSize);
        CHECK(compressedStats.extraDataSize == extractedStats.extraDataSize);
        CHECK(compressedStats.finalDataSize == extractedStats.initialDataSize);
        CHECK(compressedStats.initialDataSize == extractedStats.finalDataSize);
    };

    std::mt19937 rnd(127);
    std::uniform_int_distribution<unsigned char> byteDistr(0, 255);
    std::uniform_int_distribution<uint64_t> smallLengthDistr(1, 100);
    std::uniform_int_distribution<uint64_t> bigLengthDistr(1e5, 2e6);

    auto getRandomString = [&rnd, &byteDistr](uint64_t length) {
        std::string result;
        result.reserve(length);
        for (uint64_t i = 0; i < length; i++) {
            result.push_back(byteDistr(rnd));
        }
        return result;
    };

    auto getRandomFibonacciString = [&rnd, &byteDistr](uint64_t length) {
        std::string result;
        uint64_t first = 0;
        uint64_t second = 1;

        result.reserve(length);
        for (unsigned char i = byteDistr(rnd); result.size() < length; i++) {
            second += first;
            first = second;
            for (uint64_t j = 0; j < second && result.size() < length; j++) {
                result.push_back(i);
            }
        }
        std::shuffle(result.begin(), result.end(), rnd);

        return result;
    };

    SUBCASE("--> testing end-to-end") {
        checkTextEndToEnd("skjdhaewqijn34u238rjfi289rh23ij209uru31r02839hfueiwc");
    }
    SUBCASE("--> testing one-symbol-text") {
        checkTextEndToEnd("sssssssssssssssssssssssssssssssssssssssssssssssssssss");
        checkTextEndToEnd("a");
    }
    SUBCASE("--> testing empty text") {
        checkTextEndToEnd("");
    }
    SUBCASE("--> testing random texts") {
        constexpr static uint64_t SMALL_STRING_NUMBER = 500;
        constexpr static uint64_t BIG_STRING_NUMBER = 5;

        for (uint64_t i = 0; i < SMALL_STRING_NUMBER; i++) {
            checkTextEndToEnd(getRandomString(smallLengthDistr(rnd)));
        }
        for (uint64_t i = 0; i < BIG_STRING_NUMBER; i++) {
            checkTextEndToEnd(getRandomString(bigLengthDistr(rnd)));
        }
    }
    SUBCASE("--> testing Fibonacci texts") {
        constexpr static uint64_t N = 5;

        for (uint64_t i = 0; i < N; i++) {
            checkTextEndToEnd(getRandomFibonacciString(bigLengthDistr(rnd)));
        }
    }
    SUBCASE("--> testing time") {
        constexpr static uint64_t N = 3;
        constexpr static uint64_t MAX_MILLISECONDS = 10000; //it is without optimizations

        for (uint64_t i = 0; i < N; i++) {
            auto startTime = std::chrono::high_resolution_clock::now();

            checkTextEndToEnd(getRandomString(bigLengthDistr(rnd)));
            
            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
            CHECK(duration.count() <= MAX_MILLISECONDS);  
        }
    }
}