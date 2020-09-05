#include <assert.h>
#include "Trie.h"
#include "Bits.h"

namespace Trie {

Trie::Trie() :
    root{std::make_unique<Node>()} {}

bool Trie::addCode(const Bits::Bits& code, unsigned char value) {
    Node* cur = root.get();
    for (bool bit : code) {
        if (bit == false) {
            if (cur->left == nullptr) {
                cur->left = std::make_unique<Node>();
            }
            cur = cur->left.get();
        } else {
            if (cur->right == nullptr) {
                cur->right = std::make_unique<Node>();
            }
            cur = cur->right.get();
        }
        
        assert(cur->value == std::nullopt);
    }
    cur->value = value;

    return true;
}

Iterator Trie::begin() const noexcept {
    return Iterator{root.get()};
}

Iterator::Iterator(Trie::Node* root) noexcept :
    curNode{root} {}

void Iterator::go(bool bit) noexcept {
    if (bit == false) {
        assert(curNode->left != nullptr);
        curNode = curNode->left.get();
    } else {
        assert(curNode->right != nullptr);
        curNode = curNode->right.get();
    }
}

bool Iterator::hasValue() const noexcept {
    return curNode->value.has_value();
}

unsigned char Iterator::getValue() const noexcept {
    assert(hasValue());
    return curNode->value.value();
}

} //namespace Trie