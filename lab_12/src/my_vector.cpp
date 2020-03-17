#include <limits>
#include <stdexcept>
#include <stdio.h>

namespace my_vector {
    size_t ceil_power_of_two(size_t n) {
        if (std::numeric_limits<size_t>::max() / 2 < n) {
            throw std::logic_error("Too many elements.");
        }
        size_t result = 1;
        while (result < n) {
            result <<= 1;
        }
        return result;
    }
}