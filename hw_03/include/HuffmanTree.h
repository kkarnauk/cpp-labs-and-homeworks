#pragma once

#include <memory>
#include <numeric>
#include <optional>
#include <vector>
#include "Bits.h"
#include "FrequencyTable.h"

namespace Huffman::Tree {

class Tree final {
public:
    ~Tree();

    explicit Tree(const FrequencyTable::FrequencyTable& ftable);

    std::vector<Bits::Bits> getAllCodes();
    
private:
    struct Node;
    using NodePointer = std::unique_ptr<Node>;

    NodePointer root;

    void getAllCodes(std::vector<Bits::Bits>& codes, Node* curNode, Bits::Bits& currentCode);

    class NodeHeap;
};

} //namespace Huffman::Tree