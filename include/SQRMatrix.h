//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_SQRMATRIX_H
#define OTUS_CPP_6_SQRMATRIX_H


#include "Matrix.h"
#include "LinearMatrix.h"
#include "Cell.h"

template<typename T>
struct SQRMatrix : Matrix<T> {

private:
    std::size_t rows_size{};
    std::size_t cols_size{};
    std::vector<T> rows;
public:
    SQRMatrix<T>();

    ~SQRMatrix();

    T operator[](std::size_t row_);
};


template<typename T>
struct SQRMatrix<LinearMatrix<T>> : public Matrix<SQRMatrix<LinearMatrix<T>>> {

private:
    std::size_t rows_size{};
    std::size_t cols_size{};
    std::vector<LinearMatrix<T>> rows;
    using iterator = typename std::vector<T>::iterator;
public:

    SQRMatrix<LinearMatrix<T>>() : rows{}, rows_size{1}, cols_size{rows.size()} {}
    ~SQRMatrix() override {  };
    LinearMatrix<T> operator[](std::size_t row_) {
        return rows.at(row_);
    }


    iterator begin()   { return rows.begin(); }
    iterator end()     { return rows.end(); }
    std::size_t size() override { return rows.size(); }
};

#endif //OTUS_CPP_6_SQRMATRIX_H
