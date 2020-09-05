#include <sstream>
#include "doctest.h"
#include "FrequencyTable.h"

TEST_CASE("testing Frequency Table") {
    std::stringstream stream;
    stream << "hello!?!!!";
    FrequencyTable::FrequencyTable ftable;
    ftable.readAndRecount(stream);
    CHECK(ftable['e'] == 1);
    CHECK(ftable['h'] == 1);
    CHECK(ftable['l'] == 2);
    CHECK(ftable['o'] == 1);
    CHECK(ftable['!'] == 4);
    CHECK(ftable['?'] == 1);
    CHECK(ftable.totalFrequency() == 10);
}