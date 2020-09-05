#include <sstream>
#include <vector>
#include "doctest.h"
#include "FrequencyTable.h"
#include "HuffmanTree.h"

using namespace Huffman::Tree;

TEST_CASE("testing Huffman Tree") {
    FrequencyTable::FrequencyTable ftable;
    std::stringstream stream;
    stream << "aaaabcccd";
    ftable.readAndRecount(stream);
    Tree tree(ftable);
    
    std::vector<Bits::Bits> codes = tree.getAllCodes();
    std::vector<Bits::Bits> againCodes = tree.getAllCodes();
    CHECK(codes == againCodes);

    CHECK(codes['a'] == Bits::Bits({0}));
    CHECK(codes['c'] == Bits::Bits({1, 1}));
    CHECK(codes['b'] == Bits::Bits({1, 0, 0}));
    CHECK(codes['d'] == Bits::Bits({1, 0, 1}));
}