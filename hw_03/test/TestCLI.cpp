#include <string>
#include "doctest.h"
#include "CLI.h"

using namespace Huffman::CLI;

void checkSettings(const Settings& setting, const std::string& input, 
                   const std::string& output, Settings::Action action) {

    CHECK(setting.getAction() == action);
    CHECK(setting.getInputFile() == input);
    CHECK(setting.getOutputFile() == output);
}

TEST_CASE("testing CLI") {
    SUBCASE("-> testing correct inputs") {
        SUBCASE("--> full arguments names") {
            const char* args[] = {"name", "--output", "a.txt", "--file", "b.txt", "-c"}; 
            Settings setting(std::size(args), args);
            checkSettings(setting, "b.txt", "a.txt", Settings::Action::Archive);
        }
        SUBCASE("--> short arguments names") {
            const char* args[] = {"name", "-o", "hello.txt", "-u", "-f", "ready.txt"}; 
            Settings setting(std::size(args), args);
            checkSettings(setting, "ready.txt", "hello.txt", Settings::Action::Unarchive);
        }
        SUBCASE("--> and short, and full arguments names") {
            const char* args1[] = {"name", "--output", "world.bin", "-c", "-f", "cat.txt"};
            Settings setting1(std::size(args1), args1);
            checkSettings(setting1, "cat.txt", "world.bin", Settings::Action::Archive);

            const char* args2[] = {"name", "-u", "--file", "The Big Bang.bin", "-o", "Theory.txt"};
            Settings setting2(std::size(args2), args2);
            checkSettings(setting2, "The Big Bang.bin", "Theory.txt", Settings::Action::Unarchive);
        }
    }

    SUBCASE("-> testing incorrect inputs") {
        SUBCASE("--> wrong arguments") {
            const char* args1[] = {"name", "--output", "world.bin", "-c", "-f", "cat.txt", "--help"};
            CHECK_THROWS_AS(Settings(std::size(args1), args1), ParsingArgsException);

            const char* args2[] = {"name", "--out", "world.bin", "-c", "-f", "cat.txt"};
            CHECK_THROWS_AS(Settings(std::size(args2), args2), ParsingArgsException);
        }
        SUBCASE("--> double arguments") {
            const char* args1[] = {"name", "--output", "world.bin", "--output", "hello", "-c", "-f", "a.txt"};
            CHECK_THROWS_AS(Settings(std::size(args1), args1), ParsingArgsException);

            const char* args2[] = {"name", "--output", "world.bin", "-c", "-f", "cat.txt", "--file", "cat"};
            CHECK_THROWS_AS(Settings(std::size(args2), args2), ParsingArgsException);
        }
        SUBCASE("--> and archive, and unarchive arguments") {
            const char* args1[] = {"name", "--output", "a.txt", "--file", "-u", "b.txt", "-c"}; 
            CHECK_THROWS_AS(Settings(std::size(args1), args1), ParsingArgsException);

            const char* args2[] = {"name", "-c", "--output", "a.txt", "--file", "-u", "b.txt"}; 
            CHECK_THROWS_AS(Settings(std::size(args2), args2), ParsingArgsException);
        }
    }
}   