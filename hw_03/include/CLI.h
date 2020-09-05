#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

namespace Huffman::CLI {

class Settings final {
public:
    enum class Action : int {
        Archive,
        Unarchive,
        Nothing
    };

    explicit Settings(int argc, const char** argv);

    const std::string& getInputFile() const noexcept;
    const std::string& getOutputFile() const noexcept;
    Action getAction() const noexcept;

private:
    std::string inputFile;
    std::string outputFile;
    Action action;

    void setInputFile(std::string_view newInputFile);
    void setOutputFile(std::string_view newOutputFile);
    void setAction(Action newAction);

    bool isComplete() const noexcept;
};

class ParsingArgsException final : public std::logic_error {
    using std::logic_error::logic_error;
};

} //namespace Huffman::CLI