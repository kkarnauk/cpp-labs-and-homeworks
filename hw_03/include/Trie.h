#pragma once

#include <memory>
#include <optional>
#include <vector>
#include "Bits.h"

namespace Trie {

class Trie final {
private:
    struct Node;
    using NodePointer = std::unique_ptr<Node>;

    NodePointer root;

    struct Node final {
        NodePointer left;
        NodePointer right;

        std::optional<unsigned char> value;
    };
    
public:
    class Iterator;

    explicit Trie();

    bool addCode(const Bits::Bits& code, unsigned char value);

    Iterator begin() const noexcept;

    class Iterator final {
    public:
        void go(bool bit) noexcept;

        bool hasValue() const noexcept;
        unsigned char getValue() const noexcept;

    private:
        Node* curNode;
        explicit Iterator(Node* root) noexcept;

        friend Trie;
    };
};

using Iterator = Trie::Iterator;

} //namespace Trie