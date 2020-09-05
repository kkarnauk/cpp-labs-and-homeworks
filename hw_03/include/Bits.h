#pragma once

#include <deque>
#include <limits.h>
#include <stdint.h>

namespace Bits {

using Bits = std::deque<bool>;

unsigned char getFirstByte(const Bits& bits) noexcept;
Bits getBitsFromByte(unsigned char byte) noexcept;

} //namespace Bits