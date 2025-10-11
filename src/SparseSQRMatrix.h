//
// Created by PetukhovDG on 08.10.2025.
//

#include "Matrix.h"
#include "SQRMatrix.h"
#include "LinearMatrix.h"
#include "Cell.h"
#include "SparseSQRMatrixIterator.h"
#include <tuple>

template<typename T>
struct SparseSQRMatrix : Matrix<T> {

private:
    std::size_t const negative_idx = -1;
    std::size_t cur_row;
    std::size_t cur_col;
    T def_value = 0;
    T cur_value = 0;
    using iterator = class SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, T>>;
    using matrix_type = class SQRMatrix<LinearMatrix<Cell<T>>>;
    matrix_type origin;
    iterator cur_iterator;
public:

    SparseSQRMatrix<T>(const matrix_type& sqrmatrix) : cur_row{negative_idx}, cur_col{negative_idx}, origin{sqrmatrix}, cur_iterator{sqrmatrix}{
//        cur_iterator(sqrmatrix);
    }

    SparseSQRMatrix<T>(matrix_type &&sqrmatrix) : cur_row{negative_idx}, cur_col{negative_idx}, origin{sqrmatrix}, cur_iterator{sqrmatrix}{
//        origin = &sqrmatrix;
//        cur_iterator(&origin);
    }

    ~SparseSQRMatrix() override {};

    SparseSQRMatrix<T> &operator[](std::size_t idx) {
        if (cur_row == negative_idx) {
            cur_row = idx;
        } else {
            if (cur_col == negative_idx) {
                cur_col = idx;
                if (origin.find(cur_row) == origin.end()) {//not found
                    cur_value = def_value;
                } else {
                    auto foun_row = origin[cur_row];
                    if (foun_row.find(cur_col) == foun_row.end()) {//not found
                        cur_value = def_value;
                    } else {
                        cur_value = foun_row[cur_col].get_value();
                    }
                }
            } else {
                cur_row = idx;
                cur_col = negative_idx;
                cur_value = def_value;
            }
        }
        return *this;
    }

    auto operator=(const T &val) {
        if (cur_row == negative_idx || cur_col == negative_idx) return nullptr;
        if (val == def_value) {
            if (cur_row != negative_idx && cur_col != negative_idx) {
                auto foun_row_iter = origin.find(cur_row);
                if (foun_row_iter == origin.end()) {//not found
                    cur_value = def_value;
                } else {
                    auto foun_row = origin[cur_row];
                    auto foun_col_iter = foun_row.find(cur_col);
                    if (foun_col_iter == foun_row.end()) {//not found
                        cur_value = def_value;
                    } else {
                        auto foun_col = foun_row[cur_col];
                        cur_row = negative_idx;
                        cur_col = negative_idx;
                        cur_value = def_value;
                        foun_row.erase(foun_col_iter);
                        origin.erase(foun_row_iter);
                    }
                }
            }
        } else {
            if (cur_row != negative_idx && cur_col != negative_idx) {
                origin[cur_row][cur_col] = val;
                cur_row = negative_idx;
                cur_col = negative_idx;
                cur_value = def_value;
            }
            return nullptr;
        }
        return nullptr;
    }

    T get_value() const {
        return cur_value;
    }

    friend bool operator==(SparseSQRMatrix<T> &lhs, T const &rhs) {
        return lhs.get_value() == rhs;
    }

    friend std::ostream &operator<<(std::ostream &os, SparseSQRMatrix<T> const &obj) {
        os << obj.get_value();
        return os;
    }

    std::size_t size() {
        return origin.size();
    }


    iterator begin() {
        return static_cast<iterator>(cur_iterator.begin());
    }

    iterator end() {
        return static_cast<iterator>(cur_iterator.end());
    }
//
//        iterator begin() {
//            return cur_iterator.begin();
//        }
//
//        iterator end() {
//            return cur_iterator.end();
//        }

//        auto begin() {
//            auto origin_row_iterator = origin.bein();
//            auto row_data_begin = *origin_row_iterator;
//            auto row_ = row_data_begin.first();
//            auto col_data_begin = row_data_begin.second().begin();
//            auto col_ = col_data_begin.first();
//            auto value_ = col_data_begin.second().get_value();
//            return iterator(std::make_tuple(row_, col_, value_));/*return origin.begin(); */}
//
//        auto end() { auto origin_row_iterator = origin.end();
//            auto row_data_end = *origin_row_iterator;
//            auto row_ = row_data_end.first();
//            auto col_data_end = row_data_end.second().begin();
//            auto col_ = col_data_end.first();
//            auto value_ = col_data_end.second().get_value();
//            return iterator(std::make_tuple(row_, col_, value_));/*return origin.end();*/}
//
//        auto operator*() {
//            auto origin_row_iterator = cur_iterator;
//            auto row_data = *origin_row_iterator;
//            auto row_ = row_data.first();
//            auto col_data = row_data.second().begin();
//            auto col_ = col_data.first();
//            auto value_ = col_data.second().get_value();
//            return std::make_tuple(row_, col_, value_);
//        }

//        auto& operator*() {
//            auto origin_row_iterator = m_ptr;
//            auto row_data = *origin_row_iterator;
//            auto row_ = row_data.first();
//            auto col_data = row_data.second().begin();
//            auto col_ = col_data.first();
//            auto value_ = col_data.second().get_value();
//            return std::make_tuple(row_, col_, value_);
//        }

//
//    auto &operator++() {
//        cur_iterator++;
//        return cur_iterator;
//    }

};

