#pragma once

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <memory>
#include <new>

class Printer {
private:

public:
    Printer() {
        std::cout << sizeof(Printer);
        std::cout << "test \n";
    }

    Printer(const Printer &other) {
        std::cout << "copy constructor \n";
    }

    Printer &operator=(const Printer &other) {
        std::cout << "copy Printer \n";
        return *this;
    }

    Printer &operator=(Printer &&other) {
        std::cout << "move Printer \n";
        return *this;
    }

    ~Printer() {
        std::cout << "destructor called \n";
        std::cout << this << "\n";
    }
};


template<typename T>
class My_Vector {
private:
    size_t size_;
    T *elements_;
    size_t capacity_ = 2;

    void resize() {
        capacity_ *= 2;
        T *newElements = static_cast<T *>(operator new(capacity_ * sizeof(T)));

        for (auto i = 0; i < size_; ++i) {
            new(newElements + i) T(std::move(elements_[i]));

            // in compile time
            if constexpr (!std::is_trivially_destructible<T>::value) {
                std::destroy_at(elements_ + i);
            }
        }
        operator delete(elements_);
        elements_ = newElements;
    }

public:
    My_Vector() : size_(0) {
        elements_ = static_cast<T *> (operator new(capacity_ * sizeof(T)));
    }

    My_Vector(const My_Vector &other) : size_(other.size_), capacity_(other.capacity_) {
        elements_ = static_cast<T *> (operator new(capacity_ * sizeof(T)));

        for (size_t i = 0; i < size_; ++i) {
            new(elements_ + i) T(other.elements_[i]);
        }
    }

    My_Vector &operator=(const My_Vector &other);

    My_Vector &operator=(My_Vector &&other) noexcept;

    void push_back(const T &value);

    template<typename... Args>
    void emplace_back(Args&&... args){
        if(size_ == capacity_){
            resize();
        }
        new(elements_ + size_) T(std::forward<Args>(args)...);
        ++size_;
    }

    void clear() {
        // on compile time
        if constexpr (!std::is_trivially_destructible<T>::value) {
            for (auto i = size_; i > 0; --i) {
                std::destroy_at(elements_ + i - 1);
            }
        }

        size_ = 0;
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

    T &at(size_t index);

    const T &at(size_t index) const;

    T &operator[](const size_t index) {
        return elements_[index];
    }

    const T &operator[](const size_t index) const {
        return elements_[index];
    }

    ~My_Vector() {
        clear();
        operator delete(elements_);
    }

    class iterator {
    private:
        T *ptr_;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        iterator(T *ptr) : ptr_(ptr) {}

        reference operator*() const { return *ptr_; }

        pointer operator->() { return ptr_; }

        iterator &operator++() {
            ++ptr_;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator &operator--() {
            -ptr_;
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            -(*this);
            return tmp;
        }

        iterator &operator+=(difference_type offset) {
            ptr_ += offset;
            return *this;
        }

        iterator operator+(difference_type offset) const { return iterator(ptr_ + offset); }

        iterator &operator-=(difference_type offset) {
            ptr_ -= offset;
            return *this;
        }

        iterator operator-(difference_type offset) const { return iterator(ptr_ - offset); }

        difference_type operator-(const iterator &other) const { return ptr_ - other.ptr_; }

        reference operator[](difference_type offset) const { return *(ptr_ + offset); }

        bool operator==(const iterator &other) const { return ptr_ == other.ptr_; }

        bool operator!=(const iterator &other) const { return ptr_ != other.ptr_; }

        bool operator<(const iterator &other) const { return ptr_ < other.ptr_; }

        bool operator<=(const iterator &other) const { return ptr_ <= other.ptr_; }

        bool operator>(const iterator &other) const { return ptr_ > other.ptr_; }

        bool operator>=(const iterator &other) const { return ptr_ >= other.ptr_; }
    };

    iterator begin() { return iterator(elements_); }

    iterator end() { return iterator(elements_ + size_); }
};


template<typename T>
My_Vector<T> &My_Vector<T>::operator=(My_Vector<T> &&other) noexcept {
    std::cout << "move operator \n";
    if (this == &other) return *this;
    clear();
    operator delete(elements_);

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
    std::cout << "copy operator \n";
    if (this == &other) return *this;
    clear();
    operator delete(elements_);

    capacity_ = other.capacity_;
    elements_ = static_cast<T *>(operator new(capacity_ + sizeof(T)));
    size_ = other.size_;

    for (auto i = 0; i < other.size_; ++i) {
        new(elements_ + i) T(other.elements_[i]);
    }
    return *this;
}

template<typename T>
void My_Vector<T>::push_back(const T &value) {
    if (size_ == capacity_) {
        resize();
    }

    new(elements_ + size_) T(value);
    ++size_;
}

template<typename T>
void My_Vector<T>::pop_back() {
    if (size_ > 0) {
        if constexpr (!std::is_trivially_destructible<T>::value) {
            std::destroy_at(&elements_[size_ - 1]);
        }
        --size_;
    }
}

template<typename T>
T &My_Vector<T>::at(size_t index) {
    return elements_[index];
}

template<typename T>
const T &My_Vector<T>::at(size_t index) const {
    return elements_[index];
}
