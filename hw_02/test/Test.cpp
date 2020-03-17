#include <iostream>
#include "BoardTest.h"

size_t Test::failed_num = 0;
size_t Test::total_num = 0;

bool Test::show_final_results() {
    std::cout << "Failed tests    : " << failed_num << "/" << total_num << std::endl;
    std::cout << "Successful tests: " << total_num - failed_num << "/" << total_num << std::endl;
    return (failed_num == 0);
}

void Test::check(bool expr, const char *func, const char *filename, size_t line_num) {
    total_num++;
    if (!expr) {
        failed_num++;
        printf("Test failed => Function: %s, filename: %s, line: %lu\n", func, filename, line_num); 
    }
}
