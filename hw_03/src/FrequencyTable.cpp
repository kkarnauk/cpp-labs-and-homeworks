#include <iostream>
#include "FrequencyTable.h"

namespace FrequencyTable {

FrequencyTable::FrequencyTable() :
    frequencies{std::vector<uint64_t>(UCHAR_MAX + 1)} {}

uint64_t FrequencyTable::operator[](uint64_t index) const noexcept {
    return frequencies[index];
}

void FrequencyTable::readAndRecount(std::istream& in) {
    frequencies.assign(256, 0);
    while (in.peek() != EOF) {
        frequencies[static_cast<unsigned char>(in.get())]++;
    }
}

uint64_t FrequencyTable::totalFrequency() const noexcept {
    uint64_t total = 0;
    for (uint64_t value : frequencies) {
        total += value;
    }

    return total;
}

} //namespace FrequencyTable