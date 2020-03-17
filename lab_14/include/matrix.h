#pragma once
#include <iosfwd>
#include <stdexcept>
#include <string>
#include <vector>

class Matrix final {
public:
    explicit Matrix() noexcept;
    ~Matrix() = default;
    Matrix(const Matrix &) = default;
    Matrix &operator=(const Matrix &) = default;

    explicit Matrix(const std::vector<std::vector<int32_t>> &);
    
    int32_t get_elem(int32_t, int32_t) const;
    size_t get_row_size() const noexcept;
    size_t get_col_size() const noexcept;
    void load_from_file(const std::string &);

    Matrix &operator+=(const Matrix &);
    Matrix &operator*=(const Matrix &);
    friend std::ostream &operator<<(std::ostream &, const Matrix &);
private:
    size_t row_size;
    size_t col_size;
    std::vector<std::vector<int32_t>> data;
};

class MatrixException final : public std::logic_error {
public:
    explicit MatrixException(const char *);
};