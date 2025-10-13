//
// Created by PetukhovDG on 10.10.2025.
//

#include "CustomInputIterator.h"
#include "SQRMatrix.h"
#include <tuple>

template<typename T>
struct SparseSQRMatrixIterator{};

template<typename T>
struct SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>> {
    using matrix_pointer = typename std::map<std::size_t, LinearMatrix<Cell<T>>>::iterator;
    using row_pointer = typename std::map<std::size_t, Cell<T>>::iterator;
private:
    SQRMatrix<LinearMatrix<Cell<T>>>& matrix;
    matrix_pointer matrix_begin;
    matrix_pointer matrix_end;
    row_pointer row_begin;
    row_pointer row_end;
    matrix_pointer matrix_ptr;//cur_position
    row_pointer row_ptr;//cur_position
public:
    using iterator = class SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>;
    SparseSQRMatrixIterator(SQRMatrix<LinearMatrix<Cell<T>>>& data_) :matrix{data_}{
        matrix_begin = matrix.begin();
        row_begin = matrix.begin()->second.begin();
        matrix_ptr = matrix_begin;
        row_ptr = row_begin;
        matrix_end = matrix.end();
        row_end = matrix.end()->second.end();
    }
    SparseSQRMatrixIterator(SQRMatrix<LinearMatrix<Cell<T>>>&& data_) :matrix{data_}{
        matrix_begin = matrix.begin();
        row_begin = matrix.begin()->second.begin();
        matrix_ptr = matrix_begin;
        row_ptr = row_begin;
        matrix_end = matrix.end();
        row_end = matrix.end()->second.end();
    }

    std::tuple<std::size_t, std::size_t, T> operator*() {
        auto row_ =  matrix_ptr->first;
        auto col_ =  row_ptr->first;
        auto value_ = row_ptr->second.get_value();
        return std::make_tuple(row_, col_, value_);
    }

    iterator begin() {
        matrix_begin = matrix.begin();
        row_begin = matrix_begin->second.begin();
        return *this;
    }

    iterator end() {
        matrix_end = matrix.end();
        row_end = matrix_end->second.end();
        return *this;
    }

    auto &operator++() {
        if(row_ptr != row_end){
            if(matrix_ptr != matrix_end){
                ++row_ptr;
            }
        } else {
            ++matrix_ptr;
            row_ptr = matrix_ptr->second.begin();
        }
        return *this;
    }

    // Операторы сравнения
    friend bool operator==(const iterator &a, const iterator &b) {
        return a.matrix_ptr->first == b.matrix_ptr->first && a.row_ptr->first == b.row_ptr->first;
    }

    friend bool operator!=(const iterator &a, const iterator &b) {
        return !(a == b);
    }
};