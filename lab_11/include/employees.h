#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <bin_manip.h>

class Employee {
public:
    Employee();
    virtual ~Employee();

    virtual int32_t salary() const = 0; 
    virtual Employee* clone() const = 0;
    virtual void check_on_data_correctness() const = 0;

    friend std::ostream &operator<<(std::ostream &, const Employee &);
    friend std::istream &operator>>(std::istream &, Employee &);
    friend std::ofstream &operator<<(std::ofstream &, const Employee &);
    friend std::ifstream &operator>>(std::ifstream &, Employee &);
protected:
    char *_name;
    int32_t _base_salary = 0;

    virtual void write_textually(std::ostream &) const = 0;
    virtual void read_textually(std::istream &) = 0;
    virtual void write_binary(std::ofstream &) const = 0;
    virtual void read_binary(std::ifstream &) = 0;
};

class Developer final : public Employee {
public:
    Developer() = default;
    ~Developer() = default;

    Developer(const Developer &) = delete;
    Developer &operator=(Developer) = delete;
    void check_on_data_correctness() const override;

    int32_t salary() const override;
    Employee* clone() const override;
private:
    bool _has_bonus = false;

    void write_textually(std::ostream &) const override;
    void read_textually(std::istream &) override;
    void write_binary(std::ofstream &) const override;
    void read_binary(std::ifstream &) override;
};


class SalesManager final : public Employee {
public:
    SalesManager() = default;
    ~SalesManager() = default;

    SalesManager(const SalesManager &) = delete;
    SalesManager &operator=(SalesManager) = delete;
    void check_on_data_correctness() const override;

    int32_t salary() const override;
    Employee* clone() const override;
private:
    int32_t _sold_nm = 0;
    int32_t _price = 0;

    void write_textually(std::ostream &) const override;
    void read_textually(std::istream &) override;
    void write_binary(std::ofstream &) const override;
    void read_binary(std::ifstream &) override;
};


class EmployeeArray final {
public:
    EmployeeArray() = default;
    ~EmployeeArray();

    int32_t total_salary() const;
    void add(Employee *);

    friend std::ostream &operator<<(std::ostream &, const EmployeeArray &);
    friend std::ofstream &operator<<(std::ofstream &, const EmployeeArray &);
    friend std::ifstream &operator>>(std::ifstream &, EmployeeArray &);
private:
    std::vector<Employee *> _employees;
};