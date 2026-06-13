#pragma once

#include <stdexcept>

template <typename T>
std::size_t LinkedListVector<T>::size() const {
    return size_;
}

template <typename T>
std::size_t LinkedListVector<T>::capacity() const {
    return size_;
}

template <typename T>
bool LinkedListVector<T>::empty() const {
    return size_ == 0;
}

template <typename T>
T& LinkedListVector<T>::at(std::size_t) {
    throw std::out_of_range("LinkedListVector::at is not implemented yet");
}

template <typename T>
const T& LinkedListVector<T>::at(std::size_t) const {
    throw std::out_of_range("LinkedListVector::at is not implemented yet");
}

template <typename T>
T& LinkedListVector<T>::front() {
    throw std::out_of_range("LinkedListVector::front is not implemented yet");
}

template <typename T>
const T& LinkedListVector<T>::front() const {
    throw std::out_of_range("LinkedListVector::front is not implemented yet");
}

template <typename T>
T& LinkedListVector<T>::back() {
    throw std::out_of_range("LinkedListVector::back is not implemented yet");
}

template <typename T>
const T& LinkedListVector<T>::back() const {
    throw std::out_of_range("LinkedListVector::back is not implemented yet");
}

template <typename T>
void LinkedListVector<T>::push_back(const T&) {
}

template <typename T>
void LinkedListVector<T>::push_front(const T&) {
}

template <typename T>
void LinkedListVector<T>::insert(std::size_t, const T&) {
}

template <typename T>
void LinkedListVector<T>::pop_back() {
}

template <typename T>
void LinkedListVector<T>::pop_front() {
}

template <typename T>
void LinkedListVector<T>::erase(std::size_t) {
}

template <typename T>
void LinkedListVector<T>::clear() {
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
}

