#include <stdint.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include "bin_manip.h"

write_le_int32::write_le_int32(int32_t _value) : 
    value{_value} {}

std::ostream &write_le_int32::operator()(std::ostream &out) {
    for (size_t i = 0; i < 4; i++) {
        out.put(static_cast<char>(value % 256));
        value /= 256;
    }
    return out;
} 

std::ostream &operator<<(std::ostream &out, write_le_int32 given_value) {
    return given_value(out);
}


read_le_int32::read_le_int32(int32_t &_value) :
    value{_value} {}

std::istream &read_le_int32::operator()(std::istream &in) {
    value = 0;
    for (size_t i = 0; i < 4; i++) {
        char byte;
        in.get(byte);
        value += (static_cast<unsigned char>(byte) << (i * 8)); 
    }
    return in;
} 

std::istream &operator>>(std::istream &in, read_le_int32 given_value) {
    return given_value(in);
}


write_bool::write_bool(bool _value) :
    value{_value} {}

std::ostream &write_bool::operator()(std::ostream &out) {
    out.put(static_cast<char>(value));
    return out;
}

std::ostream &operator<<(std::ostream &out, write_bool given_value) {
    return given_value(out);
}


read_bool::read_bool(bool &_value) :
    value{_value} {}

std::istream &read_bool::operator()(std::istream &in) {
    char char_value;
    in.get(char_value);
    value = static_cast<bool>(char_value);
    return in;
}

std::istream &operator>>(std::istream &in, read_bool given_value) {
    return given_value(in);
}


write_c_str::write_c_str(char *_value) :
    value{_value} {}

std::ostream &write_c_str::operator()(std::ostream &out) {
    out.write(value, strlen(value) + 1);
    return out;
}

std::ostream &operator<<(std::ostream &out, write_c_str given_value) {
    return given_value(out);
}


read_c_str::read_c_str(char *_value, size_t _length) :
    value{_value}, length{_length} {}

std::istream &read_c_str::operator()(std::istream &in) {
    in.getline(value, length, '\0');
    return in;
}

std::istream &operator>>(std::istream &in, read_c_str given_value) {
    return given_value(in);
}