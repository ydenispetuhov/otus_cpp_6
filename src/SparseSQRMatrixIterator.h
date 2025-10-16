//
// Created by PetukhovDG on 10.10.2025.
//

#include "CustomInputIterator.h"
#include "SQRMatrix.h"
#include <tuple>

template<typename T>
struct SparseSQRMatrixIterator {
};

template<typename T>
struct SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>> {
    using matrix_iterator = typename std::map<std::size_t, LinearMatrix<Cell<T>>>::iterator;
    using row_iterator = typename std::map<std::size_t, Cell<T>>::iterator;
private:
    SQRMatrix<LinearMatrix<Cell<T>>> &matrix;
    matrix_iterator matrix_ptr;//cur_position row
    row_iterator row_ptr;//cur_position col
public:
    using iterator = class SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>;

    SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>(const iterator &other) = default;

    SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>(iterator &&other) :
            matrix{other.getMatrix()}, matrix_ptr{other.getMatrixIter()}, row_ptr{other.getRowIter()} {}

    SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>(SQRMatrix<LinearMatrix<Cell<T>>> &&data_,
                                                                     matrix_iterator &&matrix_ptr_,
                                                                     row_iterator &&row_ptr_) :
            matrix{&data_}, matrix_ptr{&matrix_ptr_}, row_ptr{&row_ptr_} {}

    SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>(SQRMatrix<LinearMatrix<Cell<T>>> &data_,
                                                                     matrix_iterator &matrix_ptr_,
                                                                     row_iterator &row_ptr_) :
            matrix{&data_}, matrix_ptr{&matrix_ptr_}, row_ptr{&row_ptr_} {}

    SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>(SQRMatrix<LinearMatrix<Cell<T>>> &data_,
                                                                     matrix_iterator &&matrix_ptr_,
                                                                     row_iterator &&row_ptr_) :
            matrix{data_}, matrix_ptr{matrix_ptr_}, row_ptr{row_ptr_} {}

    SQRMatrix<LinearMatrix<Cell<T>>> &getMatrix() {
        return matrix;
    }

    matrix_iterator &getMatrixIter() {
        return matrix_ptr;
    }

    row_iterator &getRowIter() {
        return row_ptr;
    }

    std::tuple<std::size_t, std::size_t, T> operator*() {
        auto row_ = matrix_ptr->first;
        auto col_ = row_ptr->first;
        auto value_ = row_ptr->second.get_value();
        return std::make_tuple(row_, col_, value_);
    }

    auto &operator++() {
        if (matrix_ptr != matrix.end() && row_ptr != matrix.end()->second.end()) {
            if (row_ptr != matrix_ptr->second.end()) {
                ++row_ptr;
                if (row_ptr == matrix_ptr->second.end()) {// jump to next row
                    ++matrix_ptr;
                    if (matrix_ptr != matrix.end()) {
                        row_ptr = matrix_ptr->second.begin();
                    } else {
                        row_ptr = matrix_ptr->second.end();
                    }
                }
            } else {
                ++matrix_ptr;
                if (matrix_ptr != matrix.end()) {
                    row_ptr = matrix_ptr->second.begin();
                } else {
                    row_ptr = matrix_ptr->second.end();
                }
            }
        }
        return *this;
    }

    // Операторы сравнения
    friend bool operator==(const iterator &a, const iterator &b) {
        return a.matrix_ptr == b.matrix_ptr && a.row_ptr == b.row_ptr;
    }

    friend bool operator!=(const iterator &a, const iterator &b) {
        return !(a == b);
    }
};