#pragma once

#include <cstdio>

template<typename T>
class My_Vector {
private:
    size_t size_;
    T *elements_;
    size_t capacity_ = 2;

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

    My_Vector<T> &operator=(const My_Vector<T> &other);

    My_Vector<T> &operator=(My_Vector &&other) noexcept;

    void push_back(const T &value);

    void clear() {
        delete elements_;
        elements_ = new T[capacity_];
    }

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


template<typename T>
My_Vector<T> &My_Vector<T>::operator=(My_Vector<T> &&other) noexcept {
    if (this == &other) return *this;
    delete[]elements_;

    capacity_ = other.capacity_;
    elements_ = other.elements_;
    size_ = other.size_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.elements_ = nullptr;
    return *this;
}

template<typename T>
My_Vector<T> &My_Vector<T>::operator=(const My_Vector<T> &other) {
    if (this == &other) return *this;
    delete[]elements_;

    capacity_ = other.capacity_;
    elements_ = new T[capacity_];
    size_ = other.size_;

    for (auto i = 0; i < other.size_; ++i) {
        elements_[i] = other.elements_[i];
    }
    return *this;
}

template<typename T>
void My_Vector<T>::push_back(const T &value) {
    if (size_ == capacity_) {
        capacity_ += 9;

        auto temp = new T[capacity_];
        for (auto i = 0; i < size_; ++i) {
            temp[i] = elements_[i];
        }
        delete[] elements_;
        elements_ = temp;
    }

    elements_[size_++] = value;
}
