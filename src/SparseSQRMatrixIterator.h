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
    using matrix_iterator = typename std::map<std::size_t, LinearMatrix<Cell<T>>>::iterator;
    using row_iterator = typename std::map<std::size_t, Cell<T>>::iterator;
private:
    SQRMatrix<LinearMatrix<Cell<T>>>& matrix;
    matrix_iterator& matrix_ptr;//cur_position
    row_iterator& row_ptr;//cur_position
public:
    using iterator = class SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>;
    SparseSQRMatrixIterator(SQRMatrix<LinearMatrix<Cell<T>>>& data_, matrix_iterator&& matrix_ptr_, row_iterator&& row_ptr_) :matrix{data_}, matrix_ptr{matrix_ptr_}, row_ptr{row_ptr_}{}

    std::tuple<std::size_t, std::size_t, T> operator*() {
        auto row_ =  matrix_ptr->first;
        auto col_ =  row_ptr->first;
        auto value_ = row_ptr->second.get_value();
        return std::make_tuple(row_, col_, value_);
    }

    auto &operator++() {
        if(row_ptr != matrix.end()->second.end()){
            if(matrix_ptr !=  matrix.end()){
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
        return a.matrix_ptr == b.matrix_ptr && a.row_ptr == b.row_ptr;
    }

    friend bool operator!=(const iterator &a, const iterator &b) {
        return !(a == b);
    }
};