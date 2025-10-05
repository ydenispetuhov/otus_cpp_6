//
// Created by PetukhovDG on 25.09.2025.
//

#ifndef OTUS_CPP_6_CELL_H
#define OTUS_CPP_6_CELL_H

#include <ostream>

template<typename T, int def_value = 0>
struct Cell {
private:
    T m_value = def_value;
    int m_row{};
    int m_col{};
public:

    virtual ~Cell() {}

    Cell(int row = 0, int col = 0, int val_ = def_value)
    : m_row(row)
    , m_col(col)
    , m_value(val_){ }

    auto operator=(int const &val) {

        return nullptr;
    }

    friend bool operator==(Cell<T, def_value> &lhs, T const &rhs) {
        return lhs.get_value() == rhs;
    }

    friend std::ostream &operator<<(std::ostream &os, Cell<T, def_value> const &obj) {
        if (obj.m_value == def_value)
            os << def_value;
        else
            os << obj.m_value;
        return os;
    }

    T get_value() const {
        return m_value;
    }
};
#endif //OTUS_CPP_6_CELL_H
