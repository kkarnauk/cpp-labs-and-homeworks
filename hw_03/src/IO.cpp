#include <iostream>
#include <assert.h>
#include "IO.h"
#include "Bits.h"

namespace IO {

BinaryWriter::BinaryWriter(std::ostream& output_) :
    bytesNumber{0}, output{output_}{}

BinaryWriter::~BinaryWriter() {
    assert(bits.empty());
}

void BinaryWriter::writeBits(const Bits::Bits& value) {
    bits.insert(bits.end(), value.begin(), value.end());
    write();
}

void BinaryWriter::writeByte(unsigned char value) {
    writeBits(Bits::getBitsFromByte(value));
}

void BinaryWriter::writeUInt(uint64_t value) {
    for (uint8_t i = 0; i < sizeof(uint64_t); i++) {
        unsigned char byte = value & 255;
        writeByte(byte);
        value >>= 8;
    }
}

void BinaryWriter::completeByte() {
    if (bits.empty()) {
        return;
    }
    assert(bits.size() <= 8);

    bits.resize(8, false);
    write();
}

void BinaryWriter::write() {
    while (bits.size() >= 8) {
        output.put(static_cast<char>(Bits::getFirstByte(bits)));
        for (uint64_t i = 0; i < 8; i++) {
            bits.pop_front();
        }

        bytesNumber++;
    }
}

uint64_t BinaryWriter::getWrittenBytesNumber() const noexcept {
    return bytesNumber;
}


BinaryReader::BinaryReader(std::istream& input_) :
    bytesNumber{0}, input{input_} {}

bool BinaryReader::readBit() {
    if (bits.empty()) {
        read();
    }
    bool result = bits[0];
    bits.pop_front();

    return result;
}

unsigned char BinaryReader::readByte() {
    if (bits.size() < 8) {
        read();
    }
    unsigned char result = Bits::getFirstByte(bits);
    for (uint8_t i = 0; i < 8; i++) {
        bits.pop_front();
    }
    return result;
}

int32_t BinaryReader::readUInt() {
    uint64_t result = 0;
    for (uint i = 0; i < sizeof(uint64_t); i++) {
        result |= (readByte() << (i * 8));
    }
    return result;
}

void BinaryReader::read() {
    Bits::Bits byte = Bits::getBitsFromByte(static_cast<unsigned char>(input.get()));
    bits.insert(bits.end(), byte.begin(), byte.end());

    bytesNumber++;
}

void BinaryReader::skipUntilByte() {
    bits.clear();
}

uint64_t BinaryReader::getReadBytesNumber() const noexcept {
    return bytesNumber;
}


void checkCompatibility() {
    static_assert(CHAR_BIT == 8);
}

} //namespace IO