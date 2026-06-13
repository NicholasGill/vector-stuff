#pragma once

#include <stdexcept>

template <typename T>
std::size_t ArrayVector<T>::size() const {
    return size_;
}

template <typename T>
std::size_t ArrayVector<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool ArrayVector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
T& ArrayVector<T>::at(std::size_t) {
    throw std::out_of_range("ArrayVector::at is not implemented yet");
}

template <typename T>
const T& ArrayVector<T>::at(std::size_t) const {
    throw std::out_of_range("ArrayVector::at is not implemented yet");
}

template <typename T>
T& ArrayVector<T>::front() {
    throw std::out_of_range("ArrayVector::front is not implemented yet");
}

template <typename T>
const T& ArrayVector<T>::front() const {
    throw std::out_of_range("ArrayVector::front is not implemented yet");
}

template <typename T>
T& ArrayVector<T>::back() {
    throw std::out_of_range("ArrayVector::back is not implemented yet");
}

template <typename T>
const T& ArrayVector<T>::back() const {
    throw std::out_of_range("ArrayVector::back is not implemented yet");
}

template <typename T>
void ArrayVector<T>::push_back(const T&) {
}

template <typename T>
void ArrayVector<T>::push_front(const T&) {
}

template <typename T>
void ArrayVector<T>::insert(std::size_t, const T&) {
}

template <typename T>
void ArrayVector<T>::pop_back() {
}

template <typename T>
void ArrayVector<T>::pop_front() {
}

template <typename T>
void ArrayVector<T>::erase(std::size_t) {
}

template <typename T>
void ArrayVector<T>::clear() {
    size_ = 0;
}

