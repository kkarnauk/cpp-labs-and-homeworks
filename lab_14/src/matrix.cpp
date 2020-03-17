#include <iostream>
#include <fstream>
#include "matrix.h"

Matrix::Matrix() noexcept :
    row_size(0), col_size(0) {}

Matrix::Matrix(const std::vector<std::vector<int32_t>> &_data) {
    if (_data.empty() || _data.front().empty()) {
        return;
    }
    row_size = _data.size();
    col_size = _data.front().size();
    data = _data;
}

int32_t Matrix::get_elem(int32_t row, int32_t col) const {
    if (row >= static_cast<int32_t>(row_size) || col >= static_cast<int32_t>(col_size) ||
        row < 0 || col < 0) {
        
        throw MatrixException("ACCESS: bad index.");
    }
    return data[row][col];
}

size_t Matrix::get_row_size() const noexcept {
    return row_size;
}

size_t Matrix::get_col_size() const noexcept {
    return col_size;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    if (row_size != other.get_row_size() ||
        col_size != other.get_col_size()) {

        throw MatrixException("ADD: dimensions do not match.");
    } 
    for (size_t i = 0; i < row_size; i++) {
        for (size_t j = 0; j < col_size; j++) {
            data[i][j] += other.get_elem(i, j);
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    if (col_size != other.get_row_size()) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    size_t cur_row_size = row_size;
    size_t cur_col_size = other.get_col_size();
    std::vector<std::vector<int32_t>> result(cur_row_size, std::vector<int32_t>(cur_col_size));
    for (size_t i = 0; i < cur_row_size; i++) {
        for (size_t j = 0; j < cur_col_size; j++) {
            for (size_t k = 0; k < col_size; k++) {
                result[i][j] += data[i][k] * other.get_elem(k, j);
            }
        }
    }
    return (*this = Matrix(result));
}

int32_t read_int_safely(std::istream &in) {
    int32_t data;
    if (!(in >> data)) {
        throw MatrixException("LOAD: invalid file format.");
    }
    return data;
}

void Matrix::load_from_file(const std::string &fname) {
    std::ifstream fin(fname);
    if (!fin.is_open()) {
        throw MatrixException("LOAD: unable to open file.");
    }
    size_t cur_row_size = static_cast<size_t>(read_int_safely(fin));
    size_t cur_col_size = static_cast<size_t>(read_int_safely(fin));
    std::vector<std::vector<int32_t>> data(cur_row_size, std::vector<int32_t>(cur_col_size));
    for (size_t i = 0; i < cur_row_size; i++) {
        for (size_t j = 0; j < cur_col_size; j++) {
            data[i][j] = read_int_safely(fin);
        }
    }
    *this = Matrix(data);
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
    for (size_t i = 0; i < matrix.row_size; i++) {
        for (size_t j = 0; j < matrix.col_size; j++) {
            out << matrix.data[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

MatrixException::MatrixException(const char *_msg) :
    std::logic_error{_msg} {}