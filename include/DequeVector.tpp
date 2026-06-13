#pragma once

#include <stdexcept>

template <typename T>
std::size_t DequeVector<T>::size() const {
    return size_;
}

template <typename T>
std::size_t DequeVector<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool DequeVector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
T& DequeVector<T>::at(std::size_t index) {
    throw std::out_of_range("DequeVector::at is not implemented yet");
}

template <typename T>
const T& DequeVector<T>::at(std::size_t index) const {
    throw std::out_of_range("DequeVector::at is not implemented yet");
}

template <typename T>
T& DequeVector<T>::front() {
    throw std::out_of_range("DequeVector::front is not implemented yet");
}

template <typename T>
const T& DequeVector<T>::front() const {
    throw std::out_of_range("DequeVector::front is not implemented yet");
}

template <typename T>
T& DequeVector<T>::back() {
    throw std::out_of_range("DequeVector::back is not implemented yet");
}

template <typename T>
const T& DequeVector<T>::back() const {
    throw std::out_of_range("DequeVector::back is not implemented yet");
}

template <typename T>
void DequeVector<T>::push_back(const T& value) {
}

template <typename T>
void DequeVector<T>::push_front(const T& value) {
}

template <typename T>
void DequeVector<T>::insert(std::size_t index, const T& value) {
}

template <typename T>
void DequeVector<T>::pop_back() {
}

template <typename T>
void DequeVector<T>::pop_front() {
}

template <typename T>
void DequeVector<T>::erase(std::size_t index) {
}

template <typename T>
void DequeVector<T>::clear() {
    size_ = 0;
    front_index_ = 0;
}
