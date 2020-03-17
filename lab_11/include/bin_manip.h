#pragma once

#include <stdint.h>
#include <iostream>

class write_le_int32 {
public:
    explicit write_le_int32(int32_t);
    ~write_le_int32() = default;

    std::ostream &operator()(std::ostream &);
private:
    int32_t value;
};

std::ostream &operator<<(std::ostream &out, write_le_int32 given_value);

class read_le_int32 {
public:
    explicit read_le_int32(int32_t &);
    ~read_le_int32() = default;

    std::istream &operator()(std::istream &);
private:
    int32_t &value;
};

std::istream &operator>>(std::istream &in, read_le_int32 given_value);


class write_bool {
public:
    explicit write_bool(bool);
    ~write_bool() = default;

    std::ostream &operator()(std::ostream &);
private:
    bool value;
};

std::ostream &operator<<(std::ostream &out, write_bool given_value);


class read_bool {
public:
    explicit read_bool(bool &);
    ~read_bool() = default;

    std::istream &operator()(std::istream &);
private:
    bool &value;
};

std::istream &operator>>(std::istream &in, read_bool given_value);


class write_c_str {
public:
    explicit write_c_str(char *);
    ~write_c_str() = default;

    std::ostream &operator()(std::ostream &);
private:
    char *value;
};

std::ostream &operator<<(std::ostream &out, write_c_str given_value);


class read_c_str {
public:
    explicit read_c_str(char *, size_t);
    ~read_c_str() = default;

    std::istream &operator()(std::istream &);
private:
    char *value;
    size_t length;
};

std::istream &operator>>(std::istream &in, read_c_str given_value);