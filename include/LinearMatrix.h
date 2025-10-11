//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_LINEARMATRIX_H
#define OTUS_CPP_6_LINEARMATRIX_H

#include <vector>
#include <map>
#include "Matrix.h"
#include "Cell.h"

template<typename T>
struct LinearMatrix : public Matrix<T> {
private:
    std::map<std::size_t, Cell<T>> rowCols;
    using iterator = typename std::map<std::size_t, T>::iterator;
public:
    LinearMatrix<T>() : rowCols{} {}

    ~LinearMatrix() = default;

    T &operator[](std::size_t col_);

    auto find(std::size_t col_);

    auto erase(iterator col_);

    std::size_t size();
};

template<typename T>
struct LinearMatrix<Cell<T>> : public Matrix<LinearMatrix<Cell<T>>> {
private:
    std::map<std::size_t, Cell<T>> rowCols;
    using iterator = typename std::map<std::size_t, Cell<T>>::iterator;
public:
    LinearMatrix<Cell<T>>() : rowCols{} {}

    ~LinearMatrix() = default;

    Cell<T>& operator[](std::size_t col_) {
        return rowCols[col_];
    }

    iterator find(std::size_t col_){
        return rowCols.find(col_);
    }

    auto erase(iterator col_){
        return rowCols.erase(col_);
    }

    iterator begin() { return rowCols.begin(); }

    iterator end() { return rowCols.end(); }

    std::size_t size() { return rowCols.size(); }
};

#endif //OTUS_CPP_6_LINEARMATRIX_H
