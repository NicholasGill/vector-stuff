#pragma once

template <typename T>
std::size_t DequeVector<T>::size() const {
    return storage_.size();
}

template <typename T>
std::size_t DequeVector<T>::capacity() const {
    return storage_.capacity();
}

template <typename T>
bool DequeVector<T>::empty() const {
    return storage_.empty();
}

template <typename T>
T& DequeVector<T>::at(std::size_t index) {
    return storage_.at(index);
}

template <typename T>
const T& DequeVector<T>::at(std::size_t index) const {
    return storage_.at(index);
}

template <typename T>
T& DequeVector<T>::front() {
    return storage_.front();
}

template <typename T>
const T& DequeVector<T>::front() const {
    return storage_.front();
}

template <typename T>
T& DequeVector<T>::back() {
    return storage_.back();
}

template <typename T>
const T& DequeVector<T>::back() const {
    return storage_.back();
}

template <typename T>
void DequeVector<T>::push_back(const T& value) {
    storage_.push_back(value);
}

template <typename T>
void DequeVector<T>::push_front(const T& value) {
    storage_.push_front(value);
}

template <typename T>
void DequeVector<T>::insert(std::size_t index, const T& value) {
    storage_.insert(index, value);
}

template <typename T>
void DequeVector<T>::pop_back() {
    storage_.pop_back();
}

template <typename T>
void DequeVector<T>::pop_front() {
    storage_.pop_front();
}

template <typename T>
void DequeVector<T>::erase(std::size_t index) {
    storage_.erase(index);
}

template <typename T>
void DequeVector<T>::clear() {
    storage_.clear();
}
