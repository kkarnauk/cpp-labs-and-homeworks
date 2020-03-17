#include <string>
#include "tests.h"

int main() {
    lab_13::tests::test_all<int, 75>(3, 10);
    lab_13::tests::test_all<std::string, 60>("hello", "my friend\n");
    lab_13::tests::test_all<double, 1000>(1.0, 17.2);
    lab_13::tests::test_all<bool, 23>(false, true);
    lab_13::tests::test_all<bool, 16>(true, false);
    lab_13::tests::test_all<bool, 100>(false, false);
    lab_13::tests::test_all<bool, 70>(true, true);
    lab_13::tests::test_all<const char*, 1>("hey", "how are you?");
}