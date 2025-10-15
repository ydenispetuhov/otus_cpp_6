//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_MATRIX_H
#define OTUS_CPP_6_MATRIX_H

#include <cstddef>
//general interface
template<typename T>
struct Matrix {
public:

    virtual ~Matrix<T>() {};

    T& operator[](std::size_t row_) const {return static_cast<T const&>(*this)[row_];}

    std::size_t size() const {return static_cast<T const&>(*this).size();}
};

#endif //OTUS_CPP_6_MATRIX_H
