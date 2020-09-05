#pragma once

#include <limits.h>
#include <iosfwd>
#include <stdint.h>
#include <vector>

namespace FrequencyTable {

class FrequencyTable final {
public:
    explicit FrequencyTable();

    uint64_t operator[](uint64_t index) const noexcept;
    void readAndRecount(std::istream& in);

    uint64_t totalFrequency() const noexcept;
    
private:
    std::vector<uint64_t> frequencies;
};

} //namespace FrequencyTable