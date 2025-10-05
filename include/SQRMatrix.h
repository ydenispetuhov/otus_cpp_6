//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_SQRMATRIX_H
#define OTUS_CPP_6_SQRMATRIX_H


#include "Matrix.h"
#include "Row.h"
#include "Cell.h"

template<typename T>
struct SQRMatrix : Matrix<T> {
//    SQRMatrix(SQRMatrix<Row<Cell<int, def_value>>> *pMatrix) {
//
//    }

private:
    std::size_t rows_size{};
    std::size_t cols_size{};
public:
    ~SQRMatrix() override {}

private:
    std::vector<T> rows;
public:
//    SQRMatrix(std::size_t rows, std::size_t rowCols) : rows_size{rows}, cols_size{rowCols} {}

    SQRMatrix<T>() : rows{}, rows_size{1}, cols_size{rows.size()} {}


//    SQRMatrix(Matrix<T> &matrix, int idx, const std::vector<Row<T>> &rows) : Matrix(matrix, idx), rows(rows) {}

    T& operator[](int row_) override {
        return rows.at(row_);;//(Row<Cell<int>> &) nullptr;//static_cast<T>(static_cast<Row<Cell<int>>>(Row<Cell<T>>()));//todo check
    }
};


#endif //OTUS_CPP_6_SQRMATRIX_H
