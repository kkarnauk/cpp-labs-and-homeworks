#include <iostream>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "employees.h"
#include "bin_manip.h"

const int32_t MAX_NAME_LEN = 110;

Employee::Employee() {
    _name = new char[MAX_NAME_LEN];
}

Employee::~Employee() {
    delete[] _name;
}

std::ostream &operator<<(std::ostream &out, const Employee &empl) {
    empl.write_textually(out);
    return out;
}

std::istream &operator>>(std::istream &in, Employee &empl) {
    empl.read_textually(in);
    return in;
}

std::ofstream &operator<<(std::ofstream &out, const Employee &empl) {
    empl.write_binary(out);
    return out;
}

std::ifstream &operator>>(std::ifstream &in, Employee &empl) {
    empl.read_binary(in);
    return in;
}


int32_t Developer::salary() const {
    int32_t salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

Employee* Developer::clone() const {
    Developer *empl = new Developer();
    strcpy(empl->_name, _name);
    empl->_base_salary = _base_salary;
    empl->_has_bonus = _has_bonus;
    return static_cast<Employee *>(empl);
}

void Developer::check_on_data_correctness() const {
    if (_base_salary < 0) { 
        throw std::logic_error("Salary has to be non-negative, but " + 
                                std::to_string(_base_salary) + " found.");
    }
}

void Developer::write_textually(std::ostream &out) const {
    out << "Developer\nName: " << _name << "\n"
        << "Base Salary: " << _base_salary << "\n"
        << "Has bonus: " << (_has_bonus ? "+" : "-") << "\n";
}

void Developer::read_textually(std::istream &in) {
    in >> _name >> _base_salary >> _has_bonus;
    check_on_data_correctness();
}

void Developer::write_binary(std::ofstream &out) const {
    out << write_le_int32(1) << write_c_str(_name)
        << write_le_int32(_base_salary) << write_bool(_has_bonus);
}

void Developer::read_binary(std::ifstream &in) {
    in >> read_c_str(_name, MAX_NAME_LEN) 
       >> read_le_int32(_base_salary) >> read_bool(_has_bonus); 
    check_on_data_correctness();
}


int32_t SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01; 
}

Employee* SalesManager::clone() const {
    SalesManager *empl = new SalesManager();
    strcpy(empl->_name, _name);
    empl->_base_salary = _base_salary;
    empl->_sold_nm = _sold_nm;
    empl->_price = _price;
    return static_cast<Employee *>(empl);
}

void SalesManager::check_on_data_correctness() const {
    if (_base_salary < 0) { 
        throw std::logic_error("Salary has to be non-negative, but " + 
                                std::to_string(_base_salary) + " found."); 
    }
    if (_sold_nm < 0) { 
        throw std::logic_error("Number of sold items has to be non-negative, but " + 
                                std::to_string(_sold_nm) + " found."); 
    }
    if (_price < 0) { 
        throw std::logic_error("Price has to be non-negative, but " + 
                                std::to_string(_price) + " found."); 
    }
}

void SalesManager::write_textually(std::ostream &out) const {
    out << "Sales Manager\nName: " << _name << "\n"
        << "Base Salary: " << _base_salary << "\n" 
        << "Sold items: " << _sold_nm << "\n"
        << "Item price: " << _price << "\n"; 
}

void SalesManager::read_textually(std::istream &in) {
    in >> _name >> _base_salary >> _sold_nm >> _price;
    check_on_data_correctness();
}

void SalesManager::write_binary(std::ofstream &out) const {
    out << write_le_int32(2) << write_c_str(_name) << write_le_int32(_base_salary)
        << write_le_int32(_sold_nm) << write_le_int32(_price);
}

void SalesManager::read_binary(std::ifstream &in) {
    in >> read_c_str(_name, MAX_NAME_LEN) >> read_le_int32(_base_salary)
       >> read_le_int32(_sold_nm) >> read_le_int32(_price);
    check_on_data_correctness();
}

EmployeeArray::~EmployeeArray() {
    for (size_t i = 0; i < _employees.size(); i++) {
        delete _employees[i];
    }
}

void EmployeeArray::add(Employee *empl) {
    _employees.push_back(empl);
}

int32_t EmployeeArray::total_salary() const {
    int32_t total_salary = 0;
    for (size_t i = 0; i < _employees.size(); i++) {
        total_salary += _employees[i]->salary();
    }
    return total_salary;
}

std::ostream &operator<<(std::ostream &out, const EmployeeArray &arr) {
    for (size_t i = 0; i < arr._employees.size(); i++) {
        out << i + 1 << ". " << *arr._employees[i];
    }
    out << "== Total salary: " << arr.total_salary() << "\n";
    return out;
}

std::ofstream &operator<<(std::ofstream &out, const EmployeeArray &arr) {
    out << write_le_int32(static_cast<int32_t>(arr._employees.size()));
    for (size_t i = 0; i < arr._employees.size(); i++) {
        out << *arr._employees[i];
    }
    return out;
}

std::ifstream &operator>>(std::ifstream &in, EmployeeArray &arr) {
    int32_t empl_number;
    in >> read_le_int32(empl_number);
    for (size_t i = 0; i < static_cast<size_t>(empl_number); i++) {
        int32_t type;
        in >> read_le_int32(type);
        Employee *empl = nullptr;
        if (type == 1) {
            empl = new Developer();
        } else if (type == 2) {
            empl = new SalesManager();
        } else {
            throw std::logic_error("Type has to be 1 or 2, but " + 
                                    std::to_string(type) + " found.");
        }
        in >> *empl;
        arr.add(empl);
    }
    return in;
}