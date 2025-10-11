//
// Created by PetukhovDG on 10.10.2025.
//

#include "CustomInputIterator.h"
#include "SQRMatrix.h"
#include <tuple>

template<typename T>
struct SparseSQRMatrixIterator : public CustomInputIterator<std::tuple<std::size_t, std::size_t, T>> {};



template<typename T>
struct SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>> : public CustomInputIterator<std::tuple<std::size_t, std::size_t, T>> {
    using pointer = typename std::map<std::size_t, LinearMatrix<Cell<T>>>*;
//    using pointer = T *;
private:
    SQRMatrix<LinearMatrix<Cell<T>>> matrix;
    pointer m_ptr;
public:
//    using iterator = class SparseSQRMatrixIterator<T>;
    using iterator = class SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>;
//     SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>(SQRMatrix<LinearMatrix<Cell<T>>>& data_): matrix{data_}, m_ptr{data_.bein()}{}
//     SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>(SQRMatrix<LinearMatrix<Cell<T>>>&& data_): matrix{data_}{ delete data_;}
    SparseSQRMatrixIterator<T>() = delete;
    SparseSQRMatrixIterator(SQRMatrix<LinearMatrix<Cell<T>>> &data_) : matrix{data_}, m_ptr{data_.begin()} {}

    SparseSQRMatrixIterator(SQRMatrix<LinearMatrix<Cell<T>>> &&data_) : matrix{data_} { delete data_; }

    std::tuple<std::size_t, std::size_t, T> operator*() {
        auto origin_row_iterator = m_ptr;
        auto row_data = *origin_row_iterator;
        auto row_ = row_data.first();
        auto col_data = row_data.second().begin();
        auto col_ = col_data.first();
        auto value_ = col_data.second().get_value();
        return std::make_tuple(row_, col_, value_);
    }

    iterator begin() {
        return *this;
//        auto origin_row_iterator = matrix.begin();
//        auto row_data_begin = *origin_row_iterator;
//        auto row_ = row_data_begin.first();
//        auto col_data_begin = row_data_begin.second().begin();
//        auto col_ = col_data_begin.first();
//        auto value_ = col_data_begin.second().get_value();
//        return std::make_tuple(row_, col_, value_);
    }

    iterator end() {
        return *this;
//        auto origin_row_iterator = matrix.end();
//        auto row_data_end = *origin_row_iterator;
//        auto row_ = row_data_end.first();
//        auto col_data_end = row_data_end.second().begin();
//        auto col_ = col_data_end.first();
//        auto value_ = col_data_end.second().get_value();
//        return std::make_tuple(row_, col_, value_);
    }
//
//        auto& operator*() {
//            auto origin_row_iterator = m_ptr;
//            auto row_data = *origin_row_iterator;
//            auto row_ = row_data.first();
//            auto col_data = row_data.second().begin();
//            auto col_ = col_data.first();
//            auto value_ = col_data.second().get_value();
//            return std::make_tuple(row_, col_, value_);
//        }

    auto &operator++() {
        m_ptr++;
        return *this;
    }
};