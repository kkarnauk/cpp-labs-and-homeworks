#include <unordered_map>
#include "doctest.h"
#include "Trie.h"


TEST_CASE("testing Huffman Trie") {
    std::unordered_map<unsigned char, Bits::Bits> codes;
    codes['a'] = Bits::Bits({1, 1, 0, 1, 1, 0});
    codes['b'] = Bits::Bits({1, 1, 0, 0, 1});
    codes['c'] = Bits::Bits({0, 0, 1, 0});
    codes['d'] = Bits::Bits({0, 0, 0, 0, 0});
    codes['e'] = Bits::Bits({1, 1, 1, 0});

    Trie::Trie trie;
    for (unsigned char cur = 'a'; cur <= 'e'; cur++) {
        trie.addCode(codes[cur], cur);
    }
    for (auto& [value, code] : codes) {
        Trie::Iterator iterator = trie.begin();
        for (bool bit : code) {
            CHECK(iterator.hasValue() == false);
            iterator.go(bit);
        }
        
        CHECK(iterator.getValue() == value); 
    }
}