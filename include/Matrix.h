//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_MATRIX_H
#define OTUS_CPP_6_MATRIX_H

//general interface
template<typename T>
struct Matrix {
public:

    virtual ~Matrix() ;
//    Matrix(Matrix<T> &matrix_) = 0;

    virtual T& operator[](int row_) = 0;
};

#endif //OTUS_CPP_6_MATRIX_H
