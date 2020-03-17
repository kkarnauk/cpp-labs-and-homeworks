#pragma once

#include <cstddef>
#include <iostream>
#include <exception>
#include "my_array.h"

namespace lab_13 {

namespace tests {

size_t checks_number = 0;
size_t failed_checks_number = 0;

void check(bool expression) {
    if (!expression) {
        failed_checks_number++;
    }
    checks_number++;
}

template <typename T, std::size_t N>
void test_constructors(const T& first, const T& second) {
    my_array<T, N> first_array;
    for (std::size_t i = 0; i < N; i++) {
        first_array[i] = first;
    }
    my_array<T, N> second_array(first_array);
    for (std::size_t i = 0; i < N; i++) {
        check(second_array[i] == first);
        second_array[i] = second;
    }
    my_array<T, N> third_array(std::move(second_array));
    for (std::size_t i = 0; i < N; i++) {
        check(third_array[i] == second);
        check(first_array[i] == first);
    }
}

template <typename T, std::size_t N>
void test_assignments(const T& first, const T& second) {
    my_array<T, N> first_array;
    for (std::size_t i = 0; i < N; i++) {
        first_array[i] = first;
    }
    my_array<T, N> second_array;
    second_array = first_array;
    for (std::size_t i = 0; i < N; i++) {
        check(second_array[i] == first);
        second_array[i] = second;
    }
    my_array<T, N> third_array;
    third_array = std::move(second_array);
     for (std::size_t i = 0; i < N; i++) {
        check(third_array[i] == second);
        check(first_array[i] == first);
    }
}

template <typename T, std::size_t N>
void test_at(const T& first, const T& second) {
    if (N < 2) {
        return;
    }
    my_array<T, N> array;
    array.at(0) = first;
    array.at(1) = second;
    check(array.at(0) == first);
    check(array.at(1) == second);
    try {
        checks_number++;
        array.at(N) = first;
        failed_checks_number++;
    } catch (const std::out_of_range &) {
    } catch (...) {
        throw;
    }
}

template <typename T, std::size_t N>
void test_subscript_operator(const T& first, const T& second) {
    my_array<T, N> array;
    for (size_t i = 0; i < N; i++) {
        array[i] = (i % 2 == 0 ? first : second);
    }
    for (size_t i = 0; i < N; i++) {
        check(array[i] == (i % 2 == 0 ? first : second));
    }

}

template <typename T, std::size_t N>
void test_empty() {
    my_array<T, N> array;
    check(!array.empty());
}

template <typename T, std::size_t N>
void test_size() {
    my_array<T, N> array;
    check(array.size() == N);
} 

template <typename T, std::size_t N>
void test_fill(const T& first, const T& second) {
    my_array<T, N> array;
    array.fill(first);
    for (size_t i = 0; i < N; i++) {
        check(array[i] == first);
    }
    array.fill(second);
    for (size_t i = 0; i < N; i++) {
        check(array[i] == second);
    }
}

template <typename T, std::size_t N>
void test_all(const T& first, const T& second) {
    checks_number = 0;
    failed_checks_number = 0;
    try {
        test_constructors<T, N>(first, second);
        test_assignments<T, N>(first, second);
        test_at<T, N>(first, second);
        test_subscript_operator<T, N>(first, second);
        test_empty<T, N>();
        test_size<T, N>();
        test_fill<T, N>(first, second);
        if (failed_checks_number == 0) {
            std::cout << "All tests were passed (number: " << checks_number << ")" << std::endl;
        } else {
        std::cout << "Failed tests: " << failed_checks_number << "/" << checks_number << std::endl;
        }
    } catch (...) {
        std::cout << "Unknown error occured." << std::endl;
    }
}

} //namespace tests

} //namespace lab_13