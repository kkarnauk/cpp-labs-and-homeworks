#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <exception>
#include <assert.h>
#include <string.h>

namespace lab_13 {

template <typename T, std::size_t N>
constexpr const T& my_array<T, N>::at(std::size_t index) const {
    if (index >= N) {
        throw std::out_of_range("Out of range: " + std::to_string(index) +
                                " is larger than " + std::to_string(N));
    }
    return data[index];
}

template <typename T, std::size_t N>
constexpr T& my_array<T, N>::at(std::size_t index) {
    if (index >= N) {
        throw std::out_of_range("Out of range: " + std::to_string(index) +
                                " is larger than " + std::to_string(N));
    }
    return data[index];
}

template <typename T, std::size_t N>
constexpr const T& my_array<T, N>::operator[](std::size_t index) const noexcept {
    assert(index < N);
    return data[index];
}

template <typename T, std::size_t N>
constexpr T& my_array<T, N>::operator[](std::size_t index) noexcept{
    assert(index < N);
    return data[index];
}

template <typename T, std::size_t N>
constexpr bool my_array<T, N>::empty() const noexcept {
    return (N == 0);
}

template <typename T, std::size_t N>
constexpr std::size_t my_array<T, N>::size() const noexcept {
    return N;
}

template <typename T, std::size_t N>
constexpr void my_array<T, N>::fill(const T& value) {
    for (size_t i = 0; i < N; i++) {
        data[i] = value;
    }
}


//bool specialization

template <std::size_t N>
constexpr my_array<bool, N>::proxy::proxy(uint8_t& value_, std::size_t index_) :
    value{value_}, index{index_} {}

template <std::size_t N>
constexpr my_array<bool, N>::proxy::proxy(const proxy& other) noexcept {
    *this = other;
}

template <std::size_t N>
constexpr my_array<bool, N>::proxy::proxy(proxy&& other) noexcept {
    *this = other;
}

template <std::size_t N>
constexpr auto my_array<bool, N>::proxy::operator=(const proxy& other) noexcept -> proxy& {
    *this = bool(other.operator bool());  
    return *this;
}

template <std::size_t N>
constexpr auto my_array<bool, N>::proxy::operator=(proxy&& other) noexcept -> proxy& {
    return operator=(other);
}

template <std::size_t N>
constexpr auto my_array<bool, N>::proxy::operator=(bool new_value) noexcept -> proxy& {
    value &= ~(1 << index);
    value |= (static_cast<std::size_t>(new_value) << index);
    return *this;  
}

template <std::size_t N>
constexpr my_array<bool, N>::proxy::operator bool() const noexcept {
    return ((value >> index) & 1u);
}

template <std::size_t N>
constexpr my_array<bool, N>::my_array() noexcept {
    fill(false);
}

template <std::size_t N>
constexpr my_array<bool, N>::my_array(const my_array<bool, N>& other) noexcept {
    for (size_t i = 0; i < SIZE; i++) {
        data[i] = other.data[i];
    }
}

template <std::size_t N>
constexpr my_array<bool, N>::my_array(my_array<bool, N>&& other) noexcept {
    *this = std::move(other);
}

template <std::size_t N>
constexpr my_array<bool, N>& my_array<bool, N>::operator=(const my_array<bool, N>& other) noexcept {
    if (this == &other) {
        return *this;
    }
    *this = std::move(my_array<bool, N>(other));
    return  *this;
}

template <std::size_t N>
constexpr my_array<bool, N>& my_array<bool, N>::operator=(my_array<bool, N>&& other) noexcept {
    if (this == &other || N == 0) {
        return *this;
    }
    std::swap(data, other.data);
    return *this;
}

template <std::size_t N>
constexpr bool my_array<bool, N>::at(std::size_t index) const {
    if (index >= N) {
        throw std::out_of_range("Out of range: " + std::to_string(index) +
                                " is larger than " + std::to_string(N));
    }
    return static_cast<bool>(data[index / COMPRESSION] & (1u << (index % COMPRESSION)));
}

template <std::size_t N>
constexpr auto my_array<bool, N>::at(std::size_t index) -> proxy {
    if (index >= N) {
        throw std::out_of_range("Out of range: " + std::to_string(index) +
                                " is larger than " + std::to_string(N));
    }
    return proxy{data[index / COMPRESSION], index % COMPRESSION};
}

template <std::size_t N>
constexpr bool my_array<bool, N>::operator[](std::size_t index) const noexcept {
    assert(index < N);
    return static_cast<bool>(data[index / COMPRESSION] & (1u << (index % COMPRESSION)));
}

template <std::size_t N>
constexpr auto my_array<bool, N>::operator[](std::size_t index) noexcept -> proxy {
    assert(index < N);
    return proxy{data[index / COMPRESSION], index % COMPRESSION};
}

template <std::size_t N>
constexpr bool my_array<bool, N>::empty() const noexcept {
    return (N == 0);
}

template <std::size_t N>
constexpr std::size_t my_array<bool, N>::size() const noexcept {
    return N;
}

template <std::size_t N>
constexpr void my_array<bool, N>::fill(bool value) noexcept {
    uint8_t bunch_value = (value ? (1u << COMPRESSION) - 1 : 0);
    memset(static_cast<void*>(data), bunch_value, SIZE);
}

} //namespace lab_13