#pragma once

#include <cstdio>

template<typename T>
class My_Vector {
private:
    size_t size_;
    T *elements_;
    size_t capacity_ = 5;

public:
    My_Vector() : size_(0) {
        elements_ = new T[capacity_];

    }

//private question
    My_Vector(const My_Vector &other) : size_(other.size_), capacity_(other.capacity_) {
        elements_ = new T[capacity_];

        for (size_t i = 0; i < size_; ++i) {
            elements_[i] = other.elements_[i];
        }
    }

    My_Vector &operator=(const T &other);

    My_Vector &operator=(T &&other) noexcept;

    void push_back(const T &value);

    void clear();

    void pop_back();

    [[nodiscard]] bool empty() const {
        return size_ == 0;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    [[nodiscard]] size_t capacity() const {
        return capacity_;
    }

    T operator[](const T);

    ~My_Vector() {
        delete[] elements_;
        elements_ = nullptr;
    }
};
