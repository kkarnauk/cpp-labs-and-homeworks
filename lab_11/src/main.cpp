#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include "bin_manip.h"
#include "employees.h"

void load(const std::string &file_name, EmployeeArray &arr) {
    std::ifstream in(file_name, std::ios::binary | std::ios::in);
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    in >> arr;
}

void save(const std::string &file_name, EmployeeArray &arr) {
    std::ofstream out(file_name, std::ios::binary | std::ios::out);
    out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    out << arr;
}

void read_and_add(EmployeeArray &arr) {
    int32_t type;
    std::cin >> type;
    Employee *empl = nullptr;
    if (type == 1) {
        empl = new Developer();
    } else if (type == 2) {
        empl = new SalesManager();
    } else {
        throw std::logic_error("Type has to be 1 or 2, but " + 
                                std::to_string(type) + " found.");
    }
    std::cin >> *empl;
    arr.add(empl);
}

void list(EmployeeArray &arr) {
    std::cout << arr << std::endl;
}

int main() {
    try {
        std::cin.exceptions(std::istream::failbit | std::istream::badbit);
        std::cout.exceptions(std::ostream::failbit | std::ostream::badbit);

        EmployeeArray arr;
        while (true) {
            std::string command;
            std::cin >> command;
            if (command == "exit") {
                break;
            } else if (command == "load") {
                std::string file_name;
                std::cin >> file_name;
                load(file_name, arr);
            } else if (command == "save") {
                std::string file_name;
                std::cin >> file_name;
                save(file_name, arr);
            } else if (command == "add") {
                read_and_add(arr);
            } else if (command == "list") {
                list(arr);
            } else {
                std::cout << "Unknown command." << std::endl;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 2;
    }

    return 0;
}