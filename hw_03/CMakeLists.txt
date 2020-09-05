cmake_minimum_required(VERSION 3.11)

project(hw_03)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories("include/")

add_executable(hw_03
    include/Bits.h
    include/CLI.h
    include/IO.h
    include/Trie.h
    include/FrequencyTable.h
    include/HuffmanTree.h
    include/HuffmanArchiver.h

    src/main.cpp
    src/Bits.cpp
    src/CLI.cpp
    src/IO.cpp
    src/Trie.cpp
    src/FrequencyTable.cpp
    src/HuffmanTree.cpp
    src/HuffmanArchiver.cpp
)

set_target_properties(hw_03 PROPERTIES COMPILE_FLAGS "-O2")

add_executable(test_hw_03
    include/Bits.h
    include/CLI.h
    include/IO.h
    include/Trie.h
    include/FrequencyTable.h
    include/HuffmanTree.h
    include/HuffmanArchiver.h
    
    src/Bits.cpp
    src/CLI.cpp
    src/IO.cpp
    src/Trie.cpp
    src/FrequencyTable.cpp
    src/HuffmanTree.cpp
    src/HuffmanArchiver.cpp

    test/TestMain.cpp
    test/TestBits.cpp
    test/TestCLI.cpp
    test/TestFrequencyTable.cpp
    test/TestIO.cpp
    test/TestHuffmanTree.cpp
    test/TestTrie.cpp
    test/TestHuffmanArchiver.cpp
)