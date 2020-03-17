#pragma once

#include <memory>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <limits>
#include "my_vector.h"

namespace my_vector {

size_t ceil_power_of_two(size_t n);

template <typename T>
void destruct_and_delete(T* array, size_t size) noexcept {
    for (size_t i = 0; i < size; i++) {
        array[i].~T();
    }
    delete[] reinterpret_cast<char*>(array);
}

template <typename T>
my_vector<T>::my_vector() noexcept :
    size_{0}, capacity_{0}, array_(nullptr) {}

template <typename T>
my_vector<T>::my_vector(size_t count) :
    my_vector<T>{} {
    
    my_vector<T> result = allocate_vector(0, count);
    for (size_t i = 0; i < count; i++) {
        result.push_back(T());
    }
    *this = std::move(result);
}

template <typename T>
my_vector<T>::my_vector(const my_vector<T>& other) :
    my_vector<T>{} {
    
    my_vector<T> result = allocate_vector(0, other.capacity_);
    for (size_t i = 0; i < other.size_; i++) {
        result.push_back(other[i]);
    }
    *this = std::move(result);
}

template <typename T>
my_vector<T>::my_vector(my_vector<T>&& other) noexcept :
    size_{other.size_}, capacity_{other.capacity_}, array_{other.array_} {

    other.make_empty();
}

template <typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector<T>& other) {
    my_vector<T> other_cpy(other);
    return (*this = std::move(other_cpy));
}

template <typename T>
my_vector<T>& my_vector<T>::operator=(my_vector<T>&& other) noexcept {
    if (this == &other) {
        return  *this;
    }
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);

    return *this;
} 

template <typename T>
my_vector<T>::~my_vector() {
     destruct_and_delete(array_, size_);
}

template <typename T>
size_t my_vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t my_vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
bool my_vector<T>::empty() const noexcept {
    return (size_ == 0);
}

template <typename T>
void my_vector<T>::reserve(size_t count) {
    if (count <= capacity_) {
        return;
    }
    count = ceil_power_of_two(count);
    my_vector<T> result = allocate_vector(0, count);
    for (size_t i = 0; i < size_; i++) {
        result.push_back(std::move(array_[i]));
    }
    *this = std::move(result);
} 

template <typename T>
void my_vector<T>::resize(size_t count, const T& value) {
    if (count <= size_) {
        for (size_t i = count; i < size_; i++) {
            array_[i].~T();
        }
        size_ = count;
        return;
    }
    my_vector<T> result = allocate_vector(size_, count);
    try {
        for (size_t i = size_; i < count; i++) {
            result.push_back(value);
        }
    } catch (...) {
        for (size_t i = size_; i < result.size_; i++) {
            result[i].~T();
        }
        result.size_ = 0;
        throw;
    }
    for (size_t i = 0; i < size_; i++) {
        new (&result[i]) T(std::move(array_[i]));
    }
    *this = std::move(result);
}

template <typename T>
void my_vector<T>::resize(size_t count) {
    resize(count, T());
}

template <typename T>
void my_vector<T>::push_back(const T& elem) {
    push_back(T{elem});
}

template <typename T>
void my_vector<T>::push_back(T&& elem) {
    if (size_ == capacity_) {
        reserve(capacity_ + 1);
    }
    size_++;
    new (&array_[size_ - 1]) T(std::move(elem));
}

template <typename T>
void my_vector<T>::pop_back() {
    if (size_ == 0) {
        throw std::logic_error("Unable to pop from an empty vector.");
    }
    array_[size_ - 1].~T();
    size_--;
}

template <typename T>
void my_vector<T>::clear() noexcept {
    destruct_and_delete(array_, size_);
    make_empty();
}

template <typename T>
T& my_vector<T>::operator[](size_t pos) {
    if (pos >= size_) {
        throw std::range_error("Out of range.");
    }
    return array_[pos];
}

template <typename T>
const T& my_vector<T>::operator[](size_t pos) const {
    if (pos >= size_) {
        throw std::range_error("Out of range.");
    }
    return array_[pos];
} 

template <typename T>
std::ostream& operator<<(std::ostream& out, const my_vector<T>& vector) {
    for (size_t i = 0; i < vector.size(); i++) {
        out << vector[i] << " ";
    }
    return out;
}

template <typename T>
my_vector<T> my_vector<T>::allocate_vector(size_t new_size, size_t new_capacity) {
    new_capacity = ceil_power_of_two(new_capacity);
    char* data = new char[sizeof(T) * new_capacity];
    my_vector<T> result;
    result.array_ = reinterpret_cast<T*>(data);
    result.capacity_ = new_capacity;
    result.size_ = new_size;
    return result;
}

template <typename T>
void my_vector<T>::make_empty() noexcept {
    size_ = 0;
    capacity_ = 0;
    array_ = nullptr;
}

} //namespace my_vector