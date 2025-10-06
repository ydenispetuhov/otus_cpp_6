//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_LINEARMATRIX_H
#define OTUS_CPP_6_LINEARMATRIX_H

#include <vector>
#include "Matrix.h"
#include "Cell.h"

template<typename  T>
struct LinearMatrix : public Matrix<T> {
private:
    std::vector<T> rowCols;
public:
    LinearMatrix<T>(): rowCols{} {}
//    LinearMatrix<Cell<T>>(LinearMatrix<Cell<T>> const linearMatrix) : rowCols{linearMatrix.rowCols} {}
//    LinearMatrix<Cell<T>>(LinearMatrix<Cell<T>>&& linearMatrix) {
//        for(auto rowCol: linearMatrix.rowCols){
//            rowCols.push_back(std::move(rowCol));
//        }
//    }
    ~LinearMatrix() = default;

    T& operator[](std::size_t col_) {
        return rowCols.at(col_);
    }

    void add(T&& element){
        rowCols.push_back(element);
    };
};

template<typename  T>
struct LinearMatrix<Cell<T>> : public Matrix<LinearMatrix<Cell<T>>> {
private:
    std::vector<Cell<T>> rowCols;
    using iterator = typename std::vector<T>::iterator;
public:
    LinearMatrix<Cell<T>>(): rowCols{} {}
//    LinearMatrix<Cell<T>>(LinearMatrix<Cell<T>> const linearMatrix) : rowCols{linearMatrix.rowCols} {}
//    LinearMatrix<Cell<T>>(LinearMatrix<Cell<T>>&& linearMatrix) {
//        for(auto rowCol: linearMatrix.rowCols){
//            rowCols.push_back(std::move(rowCol));
//        }
//    }
    ~LinearMatrix() = default;

    Cell<T>& operator[](std::size_t col_) {
        return rowCols.at(col_)/*.get_value()*/;
    }

    void add(Cell<T>&& element){
        rowCols.push_back(element);
    };

    iterator begin()   { return rowCols.begin(); }
    iterator end()     { return rowCols.end(); }
    std::size_t size() override { return rowCols.size(); }
};

#endif //OTUS_CPP_6_LINEARMATRIX_H
