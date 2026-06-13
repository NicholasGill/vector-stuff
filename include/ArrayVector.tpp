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
T& ArrayVector<T>::at(std::size_t) {
    throw std::out_of_range("ArrayVector::at is not implemented yet");
}

// Returns the element at index without allowing modification.
template <typename T>
const T& ArrayVector<T>::at(std::size_t) const {
    throw std::out_of_range("ArrayVector::at is not implemented yet");
}

// Returns the first element, or throws if the vector is empty.
template <typename T>
T& ArrayVector<T>::front() {
    throw std::out_of_range("ArrayVector::front is not implemented yet");
}

// Returns the first element without allowing modification.
template <typename T>
const T& ArrayVector<T>::front() const {
    throw std::out_of_range("ArrayVector::front is not implemented yet");
}

// Returns the last element, or throws if the vector is empty.
template <typename T>
T& ArrayVector<T>::back() {
    throw std::out_of_range("ArrayVector::back is not implemented yet");
}

// Returns the last element without allowing modification.
template <typename T>
const T& ArrayVector<T>::back() const {
    throw std::out_of_range("ArrayVector::back is not implemented yet");
}

// Adds value to the end of the vector.
template <typename T>
void ArrayVector<T>::push_back(const T&) {
}

// Adds value to the beginning of the vector.
template <typename T>
void ArrayVector<T>::push_front(const T&) {
}

// Inserts value before the element at index.
template <typename T>
void ArrayVector<T>::insert(std::size_t, const T&) {
}

// Removes the last element, or throws if the vector is empty.
template <typename T>
void ArrayVector<T>::pop_back() {
}

// Removes the first element, or throws if the vector is empty.
template <typename T>
void ArrayVector<T>::pop_front() {
}

// Removes the element at index, or throws if index is out of range.
template <typename T>
void ArrayVector<T>::erase(std::size_t) {
}

// Removes all elements while keeping the vector usable.
template <typename T>
void ArrayVector<T>::clear() {
    size_ = 0;
}
