#pragma once

template <typename T>
std::size_t LinkedListDequeVector<T>::size() const {
    return storage_.size();
}

template <typename T>
std::size_t LinkedListDequeVector<T>::capacity() const {
    return storage_.capacity();
}

template <typename T>
bool LinkedListDequeVector<T>::empty() const {
    return storage_.empty();
}

template <typename T>
T& LinkedListDequeVector<T>::at(std::size_t index) {
    return storage_.at(index);
}

template <typename T>
const T& LinkedListDequeVector<T>::at(std::size_t index) const {
    return storage_.at(index);
}

template <typename T>
T& LinkedListDequeVector<T>::front() {
    return storage_.front();
}

template <typename T>
const T& LinkedListDequeVector<T>::front() const {
    return storage_.front();
}

template <typename T>
T& LinkedListDequeVector<T>::back() {
    return storage_.back();
}

template <typename T>
const T& LinkedListDequeVector<T>::back() const {
    return storage_.back();
}

template <typename T>
void LinkedListDequeVector<T>::push_back(const T& value) {
    storage_.push_back(value);
}

template <typename T>
void LinkedListDequeVector<T>::push_front(const T& value) {
    storage_.push_front(value);
}

template <typename T>
void LinkedListDequeVector<T>::insert(std::size_t index, const T& value) {
    storage_.insert(index, value);
}

template <typename T>
void LinkedListDequeVector<T>::pop_back() {
    storage_.pop_back();
}

template <typename T>
void LinkedListDequeVector<T>::pop_front() {
    storage_.pop_front();
}

template <typename T>
void LinkedListDequeVector<T>::erase(std::size_t index) {
    storage_.erase(index);
}

template <typename T>
void LinkedListDequeVector<T>::clear() {
    storage_.clear();
}
