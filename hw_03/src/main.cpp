#include <iostream>
#include <fstream>
#include "HuffmanArchiver.h"
#include "CLI.h"

int main(int argc, const char** argv) {
    try {
        std::cout.exceptions(std::ostream::failbit | std::ostream::badbit);

        Huffman::CLI::Settings settings(argc, argv);

        std::ifstream input(settings.getInputFile(), std::istream::in | std::ifstream::binary);
        input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        std::ofstream output(settings.getOutputFile(), std::ostream::out | std::ofstream::binary);
        output.exceptions(std::ofstream::failbit | std::ofstream::badbit); 

        Huffman::Archiver::Archiver archiver(input, output);
        Huffman::Archiver::Statistics stats;

        if (settings.getAction() == Huffman::CLI::Settings::Action::Archive) {
            stats = archiver.compress();
        } else {
            stats = archiver.extract();
        }
        
        std::cout << stats;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;

        return -1;
    } catch (...) {
        std::cout << "Unknown error occurred." << std::endl;

        return -2;
    }

    return 0;
}   