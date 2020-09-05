#include <algorithm>
#include <assert.h>
#include <iostream>
#include "Bits.h"
#include "IO.h"
#include "Trie.h"
#include "HuffmanTree.h"
#include "HuffmanArchiver.h"

namespace Huffman::Archiver {

Archiver::Archiver(std::istream& input_, std::ostream& output_) :
    input{input_}, output{output_} {}

Statistics Archiver::compress() {
    Statistics stats;

    FrequencyTable::FrequencyTable ftable;
    ftable.readAndRecount(input);

    stats.initialDataSize = ftable.totalFrequency();

    Tree::Tree tree(ftable);
    std::vector<Bits::Bits> codes = tree.getAllCodes();

    IO::BinaryWriter writer(output);
    writer.writeUInt(static_cast<uint64_t>(std::count_if(codes.begin(), codes.end(), 
                                           [](const auto& elem) { return !elem.empty(); } )));

    for (std::size_t i = 0; i < codes.size(); i++) {
        if (codes[i].empty()) {
            continue;
        }
        writer.writeByte(i);
        writer.writeByte(codes[i].size());
        writer.writeBits(codes[i]);
    }
    writer.completeByte();
    writer.writeUInt(stats.initialDataSize);

    stats.extraDataSize = writer.getWrittenBytesNumber();

    input.seekg(0, input.beg);
    input.clear();

    while (input.peek() != EOF) {
        writer.writeBits(codes[static_cast<unsigned char>(input.get())]);
    }
    writer.completeByte();

    stats.finalDataSize = writer.getWrittenBytesNumber() - stats.extraDataSize;

    return stats;
}

Statistics Archiver::extract() {
    Statistics stats;

    IO::BinaryReader reader(input);
    uint64_t numberOfCodes = reader.readUInt();

    std::vector<Bits::Bits> codes(256);
    for (uint64_t i = 0; i < numberOfCodes; i++) {
        unsigned char byte = reader.readByte();
        uint64_t size = reader.readByte();
        for (uint64_t j = 0; j < size; j++) {
            codes[byte].push_back(reader.readBit());
        }
    }    
    reader.skipUntilByte();

    Trie::Trie trie;
    for (std::size_t i = 0; i < codes.size(); i++) {
        if (codes[i].empty()) {
            continue;
        }
        trie.addCode(codes[i], i);
    }

    uint64_t length = reader.readUInt();

    stats.finalDataSize = length;
    stats.extraDataSize = reader.getReadBytesNumber();

    for (uint64_t i = 0; i < length; i++) {
        Trie::Iterator trieIterator = trie.begin();
        while (!trieIterator.hasValue()) {
            trieIterator.go(reader.readBit());
        }
        output.put(static_cast<char>(trieIterator.getValue()));
    }
    stats.initialDataSize = reader.getReadBytesNumber() - stats.extraDataSize;
    stats.finalDataSize = length;

    return stats;
}

std::ostream& operator<<(std::ostream& out, const Statistics& stats) {
    out << stats.initialDataSize << "\n"
        << stats.finalDataSize << "\n"
        << stats.extraDataSize << "\n";
    
    return out;
}

} //namespace Huffman::Archiver