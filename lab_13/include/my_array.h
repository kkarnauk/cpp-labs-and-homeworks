#pragma once

#include <cstddef>
#include <cstdint>

namespace lab_13 {

template <typename T, std::size_t N>
class my_array final {
private:
    T data[N];

public:
    constexpr explicit my_array() = default;
    ~my_array()         = default;

    constexpr my_array(const my_array& other)                = default;
    constexpr my_array(my_array&& other) noexcept            = default;
    constexpr my_array& operator=(const my_array& other)     = default;
    constexpr my_array& operator=(my_array&& other) noexcept = default;

    constexpr const T& at(std::size_t index) const;
    constexpr T& at(std::size_t index);

    constexpr const T& operator[](std::size_t index) const noexcept;
    constexpr T& operator[](std::size_t index) noexcept;

    constexpr bool empty() const noexcept;
    constexpr std::size_t size() const noexcept;

    constexpr void fill(const T& value);
};

template <std::size_t N>
class my_array<bool, N> final {
private:
    constexpr static std::size_t COMPRESSION = 8;
    constexpr static std::size_t SIZE = (static_cast<long long>(N) + COMPRESSION - 1) / COMPRESSION;

    struct proxy {
        uint8_t& value;
        std::size_t index;

        constexpr proxy(uint8_t& value_, std::size_t index_);
        ~proxy() = default;

        constexpr proxy(const proxy& other) noexcept;
        constexpr proxy(proxy&& other) noexcept;
        constexpr proxy& operator=(const proxy& other) noexcept;
        constexpr proxy& operator=(proxy&& other) noexcept;

        constexpr proxy& operator=(bool new_value) noexcept;
        constexpr operator bool() const noexcept;
    };

    uint8_t data[SIZE];

public:
    constexpr explicit my_array() noexcept;
    ~my_array<bool, N>() = default;

    constexpr my_array(const my_array& other) noexcept;
    constexpr my_array(my_array&& other) noexcept;

    constexpr my_array& operator=(const my_array& other) noexcept;
    constexpr my_array& operator=(my_array&& other) noexcept; 

    constexpr bool at(std::size_t index) const;
    constexpr proxy at(std::size_t index);

    constexpr bool operator[](std::size_t index) const noexcept;
    constexpr proxy operator[](std::size_t index) noexcept;

    constexpr bool empty() const noexcept;
    constexpr std::size_t size() const noexcept;

    constexpr void fill(bool value) noexcept;
};

} //namespace lab_13


#include "my_array_impl.h"