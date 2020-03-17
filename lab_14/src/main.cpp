#include <string>
#include <iostream>
#include <matrix.h>

static const size_t REG_NUM = 10;

size_t read_reg(std::istream &in) {
    char sym;
    int32_t reg;
    in >> sym >> reg;
    return static_cast<size_t>(reg);
}

int main() {
    std::vector<Matrix> mxs(REG_NUM);
    try {
        std::string command;
        while (std::cin >> command) {
            try {
                if (command == "load") {
                    size_t reg = read_reg(std::cin);
                    std::string fname;
                    std::cin >> fname;
                    mxs[reg].load_from_file(fname);
                } else if (command == "print") {
                    size_t reg = read_reg(std::cin);
                    std::cout << mxs[reg];
                } else if (command == "add") {
                    size_t reg_fir = read_reg(std::cin);
                    size_t reg_sec = read_reg(std::cin);
                    mxs[reg_fir] += mxs[reg_sec];
                } else if (command == "mul") {
                    size_t reg_fir = read_reg(std::cin);
                    size_t reg_sec = read_reg(std::cin);
                    mxs[reg_fir] *= mxs[reg_sec];
                } else if (command == "elem") {
                    size_t reg = read_reg(std::cin);
                    int32_t row;
                    int32_t col;
                    std::cin >> row >> col;
                    std::cout << mxs[reg].get_elem(row, col) << std::endl;
                } else if (command == "exit") {
                    break;
                }
            } catch (const MatrixException &me) {
                std::cout << me.what() << std::endl;
            } catch (const std::bad_alloc &e) {
                std::cout << "Unable to allocate memory." << std::endl;
            }
        }
    } catch (...) {
        std::cout << "Unknown error occured." << std::endl;
        return -1;
    }
    return 0;
}