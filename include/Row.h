//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_ROW_H
#define OTUS_CPP_6_ROW_H

#include <vector>
#include "Matrix.h"
#include "Cell.h"

template<typename T>
struct Row : Matrix<T> {
private:
    std::vector<T> rowCols;
public:
    Row() : rowCols{} {}

    ~Row() override {}

    T &operator[](int col_) {
        return rowCols.at(col_);
    }

    void add(T&& element){
        rowCols.push_back(element);
    };
};

#endif //OTUS_CPP_6_ROW_H
