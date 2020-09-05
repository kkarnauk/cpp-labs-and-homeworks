#include "CLI.h"

namespace Huffman::CLI {

Settings::Settings(int argc, const char** argv) :
    action{Action::Nothing} {

    std::size_t flagsNumber = static_cast<uint64_t>(argc);

    for (std::size_t i = 1; i < flagsNumber; i++) {
        std::string command(argv[i]);
        
        if (command == "-c") {
            setAction(Action::Archive);
        } else if (command == "-u") {
            setAction(Action::Unarchive);
        } else if (command == "-f" || command == "--file") {
            if (i + 1 == flagsNumber) {
                throw ParsingArgsException("No value provided for " + command + ".");
            }
            setInputFile(argv[++i]);
        } else if (command == "-o" || command == "--output") {
            if (i + 1 == flagsNumber) {
                throw ParsingArgsException("No value provided for " + command + ".");
            }
            setOutputFile(argv[++i]);
        } else {
            throw ParsingArgsException("Unknown argument specified: " + command + ".");
        }
    }

    if (!isComplete()) {
        throw ParsingArgsException("Not enough arguments specified.");
    }
}

const std::string& Settings::getInputFile() const noexcept {
    return inputFile;
}

const std::string& Settings::getOutputFile() const noexcept {
    return outputFile;
}

Settings::Action Settings::getAction() const noexcept {
    return action;
}

void Settings::setInputFile(std::string_view newInputFile) {
    if (!inputFile.empty()) {
        throw ParsingArgsException("Input file is already specified.");
    }
    inputFile = newInputFile;
}

void Settings::setOutputFile(std::string_view newOutputFile) {
    if (!outputFile.empty()) {
        throw ParsingArgsException("Output file is already specified.");
    }
    outputFile = newOutputFile;
}

void Settings::setAction(Action newAction) {
    if (action != Action::Nothing) {
        throw ParsingArgsException("Action is already specified.");
    }
    action = newAction;
}

bool Settings::isComplete() const noexcept {
    return !inputFile.empty() && !outputFile.empty() && action != Action::Nothing;
}

} //namespace Huffman::CLI