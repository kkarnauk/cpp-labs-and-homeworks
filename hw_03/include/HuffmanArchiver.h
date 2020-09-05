#pragma once

#include <iosfwd>

namespace Huffman::Archiver {

struct Statistics;

class Archiver final {
public:
    explicit Archiver(std::istream& input_, std::ostream& output_);

    Statistics compress();
    Statistics extract();

private:
    std::istream& input;
    std::ostream& output;
};

struct Statistics final {
    uint64_t initialDataSize = 0;
    uint64_t finalDataSize = 0;
    uint64_t extraDataSize = 0;
};

std::ostream& operator<<(std::ostream& out, const Statistics& stats);

} //namespace Huffman::Archiver