#pragma once

#include <iosfwd>
#include <optional>
#include <vector>
#include "Bits.h"

namespace IO {

class BinaryWriter final {
public:
    explicit BinaryWriter(std::ostream& output);
    ~BinaryWriter();

    BinaryWriter(const BinaryWriter&)            = delete;
    BinaryWriter& operator=(const BinaryWriter&) = delete;

    void writeBits(const Bits::Bits& value);
    void writeByte(unsigned char value);
    void writeUInt(uint64_t value);

    void completeByte();

    uint64_t getWrittenBytesNumber() const noexcept;
private:
    uint64_t bytesNumber;
    std::ostream& output;
    Bits::Bits bits;

    void write();
};

class BinaryReader final {
public:
    explicit BinaryReader(std::istream& input);

    BinaryReader(const BinaryWriter&)            = delete;
    BinaryReader& operator=(const BinaryReader&) = delete;

    bool readBit();
    unsigned char readByte();
    int32_t readUInt();

    void skipUntilByte();

    uint64_t getReadBytesNumber() const noexcept;
    
private:
    uint64_t bytesNumber;
    std::istream& input;
    Bits::Bits bits;

    void read();
};

} //namespace IO