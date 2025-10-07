//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_SQRMATRIX_H
#define OTUS_CPP_6_SQRMATRIX_H


#include "Matrix.h"
#include "LinearMatrix.h"
#include "Cell.h"
#include <numeric>
#include <tuple>

template<typename T>
struct SQRMatrix : Matrix<T> {

private:
    std::size_t rows_size{};
    std::size_t cols_size{};
    std::map<std::size_t, T> rows;
public:
    SQRMatrix<T>();

    ~SQRMatrix();

    T operator[](std::size_t row_);

    std::size_t size();
};


template<typename T>
struct SQRMatrix<LinearMatrix<Cell<T>>> : public Matrix<SQRMatrix<LinearMatrix<Cell<T>>>> {

private:
    std::size_t rows_size{};
    std::size_t cols_size{};
    std::map<std::size_t, LinearMatrix<Cell<T>>> rows;
    using iterator = typename std::map<std::size_t, LinearMatrix<Cell<T>>>::iterator;
public:

    SQRMatrix<LinearMatrix<Cell<T>>>() : rows{}, rows_size{}, cols_size{} {}

    ~SQRMatrix() override {};

    LinearMatrix<Cell<T>>& operator[](std::size_t row_) {
        return rows[row_];
    }


    iterator begin() { return rows.begin(); }

    iterator end() { return rows.end(); }

    std::size_t size() {
        return std::accumulate(begin(), end(), 0,
                               [](int total, std::pair<const std::size_t, LinearMatrix<Cell<T>>> entrySet) {
                                   return total + entrySet.second.size();
                               });
    }
};

#endif //OTUS_CPP_6_SQRMATRIX_H
