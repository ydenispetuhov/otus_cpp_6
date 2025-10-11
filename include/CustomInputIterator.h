//
// Created by PetukhovDG on 10.10.2025.
//

#ifndef OTUS_CPP_6_CUSTOMINPUTITERATOR_H
#define OTUS_CPP_6_CUSTOMINPUTITERATOR_H

#include <numeric>

template<typename T>
struct CustomInputIterator {
public:
    // Определения типов через using
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::input_iterator_tag;

    // Конструктор
    CustomInputIterator(pointer ptr) : m_ptr(ptr) {}

    // Операции разыменования
    reference operator*() const { return *m_ptr; }

    pointer operator->() { return m_ptr; }

    // Инкремент (префиксный и постфиксный)
    CustomInputIterator &operator++() {
        m_ptr++;
        return *this;
    }

    CustomInputIterator operator++(int) {
        CustomInputIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    // Операторы сравнения
    friend bool operator==(const CustomInputIterator &a, const CustomInputIterator &b) {
        return a.m_ptr == b.m_ptr;
    }

    friend bool operator!=(const CustomInputIterator &a, const CustomInputIterator &b) {
        return !(a == b);
    }

private:
    pointer m_ptr;
};

#endif //OTUS_CPP_6_CUSTOMINPUTITERATOR_H
