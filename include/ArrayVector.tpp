#pragma once

#include <stdexcept>

// Creates an empty vector with a default starting capacity.
template <typename T>
ArrayVector<T>::ArrayVector()
    : size_(0),
      capacity_(10),
      data(std::make_unique<T[]>(capacity_)) {
}

// Creates an empty vector with the requested starting capacity.
template <typename T>
ArrayVector<T>::ArrayVector(std::size_t capacity)
    : size_(0),
      capacity_(capacity),
      data(std::make_unique<T[]>(capacity_)) {
}

// Returns the number of elements currently stored.
template <typename T>
std::size_t ArrayVector<T>::size() const {
    return size_;
}

// Returns the number of elements that can be stored before growing.
template <typename T>
std::size_t ArrayVector<T>::capacity() const {
    return capacity_;
}

// Returns true when the vector contains no elements.
template <typename T>
bool ArrayVector<T>::empty() const {
    return size_ == 0;
}

// Returns the element at index, or throws if index is out of range.
template <typename T>
T& ArrayVector<T>::at(std::size_t index) {
    if (index < size_) {
        return data[index];
    }
    throw std::out_of_range("index out of range");
}

// Returns the element at index without allowing modification.
template <typename T>
const T& ArrayVector<T>::at(std::size_t index) const {
    if (index < size_) {
        return data[index];
    }
    throw std::out_of_range("index out of range");
}

// Returns the first element, or throws if the vector is empty.
template <typename T>
T& ArrayVector<T>::front() {
    if (empty()) {
        throw std::out_of_range("ArrayVector::front on empty vector");
    }
    return data[0];
}

// Returns the first element without allowing modification.
template <typename T>
const T& ArrayVector<T>::front() const {
    if (empty()) {
        throw std::out_of_range("ArrayVector::front on empty vector");
    }
    return data[0];
}

// Returns the last element, or throws if the vector is empty.
template <typename T>
T& ArrayVector<T>::back() {
    if (empty()) {
        throw std::out_of_range("ArrayVector::back on empty vector");
    }
    return data[size_ - 1];
}

// Returns the last element without allowing modification.
template <typename T>
const T& ArrayVector<T>::back() const {
    if (empty()) {
        throw std::out_of_range("ArrayVector::back on empty vector");
    }
    return data[size_ - 1];
}

// Adds value to the end of the vector.
template <typename T>
void ArrayVector<T>::push_back(const T& value) {
    insert(size_, value);
}

// Adds value to the beginning of the vector.
template <typename T>
void ArrayVector<T>::push_front(const T& value) {
    insert(0, value);
}

// Inserts value before the element at index.
template <typename T>
void ArrayVector<T>::insert(std::size_t index, const T& value) {
    if (index > size_) {
        throw std::out_of_range("ArrayVector::insert out of range");
    }

    if (size_ >= capacity_) {
        const std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        auto new_data = std::make_unique<T[]>(new_capacity);

        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data[i];
        }

        data = std::move(new_data);
        capacity_ = new_capacity;
    }

    for (std::size_t i = size_; i > index; --i) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    ++size_;
}

// Removes the last element, or throws if the vector is empty.
template <typename T>
void ArrayVector<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("ArrayVector::pop_back on empty vector");
    }
    erase(size_ - 1);
}

// Removes the first element, or throws if the vector is empty.
template <typename T>
void ArrayVector<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("ArrayVector::pop_front on empty vector");
    }
    erase(0);
}

// Removes the element at index, or throws if index is out of range.
template <typename T>
void ArrayVector<T>::erase(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("ArrayVector::erase out of range");
    }

    for (std::size_t i = index; i + 1 < size_; ++i) {
        data[i] = data[i + 1];
    }

    --size_;
}

// Removes all elements while keeping the vector usable.
template <typename T>
void ArrayVector<T>::clear() {
    size_ = 0;
}
