#include "Bits.h"

namespace Bits {

unsigned char getFirstByte(const Bits& bits) noexcept {
    unsigned char byte = 0;
    for (std::size_t i = 0; i < 8 && i < bits.size(); i++) {
        byte |= (bits[i] << i);
    }
    
    return byte;
}

Bits getBitsFromByte(unsigned char byte) noexcept {
    Bits bits(8);
    for (uint8_t i = 0; i < 8; i++) {
        bits[i] = (byte & 1);
        byte >>= 1;
    }

    return bits;
}


void checkCompatibility() {
    static_assert(CHAR_BIT == 8);
}

} //namespace Bits