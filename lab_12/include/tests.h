#pragma once

#include <sstream>
#include "my_vector.h"

namespace my_vector {

namespace test {

static size_t checks_number = 0;
static size_t failed_checks_number = 0;

void check(bool expr) {
    checks_number++;
    if (!expr) {
        failed_checks_number++;
    }
}

template <typename T>
void test_copy_constructor_and_assignment(const T& first, const T& second) {
    const size_t STEPS = 10;
    my_vector<T> vector_first;
    for (size_t i = 0; i < STEPS; i++) {
        vector_first.push_back(first);
        vector_first.push_back(second);
    }
    my_vector<T> vector_second(vector_first);
    my_vector<T> vector_third;
    vector_third = vector_second;
    check(vector_first.size() == vector_second.size());
    check(vector_first.size() == vector_third.size());
    for (size_t i = 0; i < vector_first.size(); i++) {
        check(vector_first[i] == vector_second[i]);
        check(vector_first[i] == vector_third[i]);
    }
    vector_first[0] = second;
    check(vector_second[0] == first);
    check(vector_third[0] == first);

    vector_first.clear();
    check(!vector_second.empty());
    check(!vector_third.empty());
}

template <typename T>
void test_move_constructor_and_assignment(const T& first, const T& second) {
    const size_t STEPS = 10;
    my_vector<T> vector_first;
    for (size_t i = 0; i < STEPS; i++) {
        vector_first.push_back(first);
        vector_first.push_back(second);
    }
    my_vector<T> vector_second(std::move(vector_first));
    check(vector_second.size() == 2 * STEPS);
    for (size_t i = 0; i < STEPS; i++) {
        check(vector_second[i * 2] == first);
        check(vector_second[i * 2 + 1] == second);
    }
    vector_first = std::move(vector_second);
    check(vector_first.size() == 2 * STEPS);
    for (size_t i = 0; i < STEPS; i++) {
        check(vector_first[i * 2] == first);
        check(vector_first[i * 2 + 1] == second);
    }
}

template <typename T>
void test_size_and_capacity(const T& elem) {
    const size_t STEPS = 20;
    my_vector<T> vector;
    check(vector.size() == 0);
    check(vector.capacity() >= 0);
    for (size_t i = 0; i < STEPS; i++) {
        vector.push_back(elem);
        check(vector.size() == i + 1);
        check(vector.capacity() >= vector.size());
        check(vector.size() * 2 >= vector.capacity());
    }
}

template <typename T>
void test_empty(const T& elem) {
    my_vector<T> vector;
    check(vector.empty());
    vector.push_back(elem);
    check(!vector.empty());

    vector.pop_back();
    check(vector.empty());

    vector.push_back(elem);
    vector.clear();
    check(vector.empty());
}

template <typename T>
void test_first_push_then_pop(const T& first, const T& second) {
    const size_t STEPS = 10;
    my_vector<T> vector;
    for (size_t i = 0; i < STEPS; i++) {
        vector.push_back(first);
    }
    for (size_t i = 0; i < STEPS; i++) {
        vector.push_back(second);
    }
    for (size_t i = 0; i < STEPS; i++) {
        check(vector[vector.size() - 1] == second);
        vector.pop_back();
    }
    for (size_t i = 0; i < STEPS; i++) {
        check(vector[vector.size() - 1] == first);
        vector.pop_back();
    }
    check(vector.empty());
}

template <typename T>
void test_push_and_pop(const T& elem) {
    const size_t STEPS = 20;
    my_vector<T> vector;
    for (size_t i = 0; i < STEPS; i++) {
        vector.push_back(elem);
        check(vector[0] == elem);
        check(vector.size() == 1);
        vector.pop_back();
    }
    check(vector.empty());
    try {
        vector.pop_back();
    } catch (const std::logic_error&) {
        check(true);
    }
}

template <typename T>
void test_reserve(const T& elem) {
    my_vector<T> vector;
    vector.reserve(100);
    check(vector.empty());
    check(vector.capacity() == 128);

    vector.reserve(60);
    check(vector.empty());
    check(vector.capacity() == 128);

    vector.reserve(129);
    check(vector.empty());
    check(vector.capacity() == 256);

    vector.push_back(elem);
    check(vector.capacity() == 256);
}

template <typename T>
void test_clear(const T& elem) {
    my_vector<T> vector;
    vector.clear();
    check(vector.empty());
    vector.push_back(elem);
    vector.clear();
    check(vector.empty());
}

template <typename T>
void test_operator_get_set(const T& first, const T& second) {
    my_vector<T> vector;
    try {
        vector[0] = first;
    } catch (const std::range_error&) {
        check(true);
    }
    vector.push_back(first);
    vector[0] = second;
    check(vector[0] == second);
    vector.push_back(first);
    check(vector[1] == first);
}

template <typename T>
void test_out_operator(const T& first, const T& second) {
    const size_t STEPS = 10;
    my_vector<T> vector;
    std::stringstream out_correct;
    for (size_t i = 0; i < STEPS; i++) {
        vector.push_back(first);
        vector.push_back(second);
        out_correct << first << " " << second << " ";
    }
    std::stringstream out_current;
    out_current << vector;

    check(out_current.str() == out_correct.str());
}

template <typename T>
void test(const T& first, const T& second) {
    std::cout << "Tests of \"test_my_vector\":" << std::endl;

    checks_number = 0;
    failed_checks_number = 0;
    try {
        test_size_and_capacity(first);
        test_empty(first);
        test_reserve(second);
        test_clear(first);
        test_operator_get_set(first, second);
        test_first_push_then_pop(first, second);
        test_push_and_pop(second);
        test_copy_constructor_and_assignment(first, second);
        test_move_constructor_and_assignment(first, second);
        test_out_operator(first, second);
    } catch (const std::exception &e) {
        std::cout << "Testing failed because of the next error:" << std::endl
                  << e.what() << std::endl
                  << "Not all tests were started, but the results:" << std::endl;
    } catch (...) {
        std::cout << "Testing failed because of an unknown error." << std::endl
                  << "Not all tests were started, but the results:" << std::endl;
    }
    std::cout << "Successful checks: " << checks_number - failed_checks_number << "/" << checks_number << std::endl;
} 

} //namespace test

namespace test_default_consructible {

static size_t checks_number = 0;
static size_t failed_checks_number = 0;

void check(bool expr) {
    checks_number++;
    if (!expr) {
        failed_checks_number++;
    }
}

template <typename T>
void test_default_constructor() {
    const size_t SIZE = 10;
    my_vector<T> vector(SIZE);
    const T& elem = T();
    for (size_t i = 0; i < SIZE; i++) {
        check(vector[i] == elem);
    }
}

template <typename T>
void test_resize(const T& elem) {
    const size_t SIZE = 10;
    my_vector<T> vector;
    vector.resize(SIZE);
    check(vector.size() == SIZE);
    for (size_t i = 0; i < SIZE; i++) {
        check(vector[i] == T());
    }
    vector.resize(SIZE * 2, elem);
    for (size_t i = 0; i < SIZE; i++) {
        check(vector[i] == T());
    }
    for (size_t i = SIZE; i < SIZE * 2; i++) {
        check(vector[i] == elem);
    }
    vector.resize(SIZE / 2);
    check(vector.size() == SIZE / 2);
} 

template <typename T>
void test(const T& elem) {
    std::cout << "Tests of \"test_my_vector_default_constructible\":" << std::endl;

    checks_number = 0;
    failed_checks_number = 0;
    try {
        test_default_constructor<T>();
        test_resize(elem);
    } catch (const std::exception &e) {
        std::cout << "Testing failed because of the next error:" << std::endl
                  << e.what() << std::endl
                  << "Not all tests were started, but the results:" << std::endl;
    } catch (...) {
        std::cout << "Testing failed because of an unknown error." << std::endl
                  << "Not all tests were started, but the results:" << std::endl;
    }
    std::cout << "Successful checks: " << checks_number - failed_checks_number << "/" << checks_number << std::endl;
}

} //namespace test_default_constructible

} //namespace my_vector

#include "my_vector_impl.h"