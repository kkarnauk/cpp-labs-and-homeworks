#include <iostream>
#include <sstream>
#include "doctest.h"
#include "IO.h"

using namespace IO;

TEST_CASE("testing Binary IO") {
    SUBCASE("--> testing end-to-end Byte IO") {
        unsigned char byte = 211;
        std::stringstream stream;
        BinaryWriter writer(stream);
        writer.writeByte(byte);

        BinaryReader reader(stream);
        CHECK(reader.readByte() == byte);
    }
    SUBCASE("--> testing end-to-end UInt IO") {
        uint64_t value = 538932;
        std::stringstream stream;
        BinaryWriter writer(stream);
        writer.writeUInt(value);

        BinaryReader reader(stream);
        CHECK(reader.readUInt() == value);
    }
    SUBCASE("--> testing end-to-end Binary") {
        std::stringstream stream;
        BinaryWriter writer(stream);
        writer.writeBits(Bits::Bits({0, 1, 1, 0, 0, 1}));
        writer.writeBits(Bits::Bits({1, 1, 1, 0, 1, 1, 1, 0}));
        writer.writeBits(Bits::Bits({0, 0, 0, 0, 1}));
        writer.completeByte();

        unsigned char byte = 251;
        uint64_t intValue = 11275;
        writer.writeByte(byte);
        writer.writeUInt(intValue);

        CHECK(writer.getWrittenBytesNumber() == 12);

        BinaryReader reader(stream);
        CHECK(reader.readBit() == false);
        CHECK(reader.readBit() == true);

        CHECK(reader.readByte() == Bits::getFirstByte(Bits::Bits({1, 0, 0, 1, 1, 1, 1, 0})));
        CHECK(reader.readByte() == Bits::getFirstByte(Bits::Bits({1, 1, 1, 0, 0, 0, 0, 0})));
        
        CHECK(reader.readBit() == true);

        reader.skipUntilByte();

        CHECK(reader.readByte() == byte);
        CHECK(reader.readUInt() == intValue);

        CHECK(reader.getReadBytesNumber() == 12);
    }
}