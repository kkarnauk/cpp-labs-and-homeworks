#include "BoardTest.h"

int main() {
    BoardTest bt;
    bt.run_all_tests();
    return static_cast<int>(!Test::show_final_results());
}