#pragma once

#include <stddef.h>

class Test {
public:
    explicit Test() = default;
    ~Test() = default;
    Test(const Test &) = delete;
    Test &operator=(const Test &) = delete;

    static bool show_final_results();
    virtual void run_all_tests() = 0;
protected:
    static size_t failed_num;
    static size_t total_num;

    static void check(bool expr, const char *func, const char *filename, size_t line_num);
};

#define DO_CHECK(EXPR) Test::check(EXPR, __PRETTY_FUNCTION__, __FILE__, __LINE__);