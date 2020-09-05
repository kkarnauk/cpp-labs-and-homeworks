#include <assert.h>
#include <set>
#include "HuffmanTree.h"

namespace Huffman::Tree {

struct Tree::Node final {
    NodePointer left;
    NodePointer right;

    std::optional<unsigned char> value;

    uint64_t frequency;

    explicit Node(unsigned char value_, uint64_t frequency_) noexcept;
    explicit Node(NodePointer left_, NodePointer right_) noexcept;

    friend NodeHeap;
};

class Tree::NodeHeap final {
public:
    NodePointer extractMin() {
        return std::move(nodes.extract(nodes.begin()).value().first);
    }

    void push(NodePointer node) {
        nodes.emplace(std::move(node), uniqueIndex++);
    }

    std::size_t size() const noexcept {
        return nodes.size();
    }
    
private:
    using Element = std::pair<NodePointer, uint64_t>;

    struct NodeComparator final {
        bool operator()(const Element& firstElement, const Element& secondElement) const {
            if (firstElement.first->frequency != secondElement.first->frequency) {
                return firstElement.first->frequency < secondElement.first->frequency;
            }
            return firstElement.second < secondElement.second;
        }
    };

    uint64_t uniqueIndex;
    std::set<Element, NodeComparator> nodes;
};


Tree::Tree(const FrequencyTable::FrequencyTable& ftable) {
    NodeHeap heap;
    for (int i = 0; i < 256; i++) {
        if (ftable[i] != 0) {
            heap.push(std::make_unique<Node>(i, ftable[i]));
        }
    }

    while (heap.size() > 1) {
        NodePointer left = heap.extractMin();
        NodePointer right = heap.extractMin();
        heap.push(std::make_unique<Node>(std::move(left), std::move(right)));
    }

    if (heap.size() == 0) {
        root = std::make_unique<Node>(nullptr, nullptr);
    } else {
        assert(heap.size() == 1);

        root = heap.extractMin();
        if (root->left == nullptr && root->right == nullptr) {
            root = std::make_unique<Node>(std::move(root), nullptr);
        } else {
            assert(root->left != nullptr && root->right != nullptr);
        }
    }
    
    assert(heap.size() == 0);
}

Tree::~Tree() = default; //needed for Tree::Node forward declaration

std::vector<Bits::Bits> Tree::getAllCodes() {
    std::vector<Bits::Bits> codes(UCHAR_MAX + 1);
    Bits::Bits currentCode;

    getAllCodes(codes, root.get(), currentCode);
    
    return codes;
}

void Tree::getAllCodes(std::vector<Bits::Bits>& codes, Node* curNode, Bits::Bits& currentCode) {
    if (curNode->value != std::nullopt) {
        codes[curNode->value.value()] = currentCode;

        assert(curNode->left == nullptr);
        assert(curNode->right == nullptr); 

        return;
    }

    if (curNode->left != nullptr) {
        currentCode.push_back(false);
        getAllCodes(codes, curNode->left.get(), currentCode);

        currentCode.pop_back();
    }

    if (curNode->right != nullptr) {
        currentCode.push_back(true);
        getAllCodes(codes, curNode->right.get(), currentCode);

        currentCode.pop_back();
    }
}


Tree::Node::Node(unsigned char value_, uint64_t frequency_) noexcept :
    value{value_}, frequency{frequency_} {}

Tree::Node::Node(NodePointer left_, NodePointer right_) noexcept :
    left{std::move(left_)}, right{std::move(right_)}, frequency{0} {

    if (left != nullptr) {
        frequency += left->frequency;
    }
    if (right != nullptr) {
        frequency += right->frequency;
    }
}

} //namespace Huffman::Tree