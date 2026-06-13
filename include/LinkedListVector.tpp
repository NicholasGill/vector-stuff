#pragma once

#include <stdexcept>

template <typename T>
LinkedListVector<T>::LinkedListVector()
    : size_(0),
      head_(std::make_unique<Node>()) {
    head_->next = std::make_unique<Node>();
    tail_ = head_->next.get();
    tail_->prev = head_.get();
}

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
T& LinkedListVector<T>::at(std::size_t index) {
    std::size_t i = 0;
    if (index >= size_) {
        throw std::out_of_range("LinkedListVector::at index out of range");
    }

    auto cur = head_->next.get();
    while (cur != tail_) {
        if (i == index) {
            return cur->value;
        }
        cur = cur->next.get();
        ++i;
    }

    throw std::out_of_range("LinkedListVector::at index out of range");
}

template <typename T>
const T& LinkedListVector<T>::at(std::size_t index) const {
    std::size_t i = 0;
    if (index >= size_) {
        throw std::out_of_range("LinkedListVector::at index out of range");
    }

    auto cur = head_->next.get();
    while (cur != tail_) {
        if (i == index) {
            return cur->value;
        }
        cur = cur->next.get();
        ++i;
    }

    throw std::out_of_range("LinkedListVector::at index out of range");
}

template <typename T>
T& LinkedListVector<T>::front() {
    if (empty()) {
        throw std::out_of_range("LinkedListVector::front empty");
    }
    return (head_->next) -> value;
}

template <typename T>
const T& LinkedListVector<T>::front() const {
    if (empty()) {
        throw std::out_of_range("LinkedListVector::front empty");
    }
    return head_->next->value;
}

template <typename T>
T& LinkedListVector<T>::back() {
    if (empty()) {
        throw std::out_of_range("LinkedListVector::front empty");
    }
    return (tail_->prev) -> value;
}

template <typename T>
const T& LinkedListVector<T>::back() const {
    if (empty()) {
        throw std::out_of_range("LinkedListVector::back empty");
    }
    return tail_->prev->value;
}

template <typename T>
void LinkedListVector<T>::push_back(const T& value) {
    insert(size_, value);
}

template <typename T>
void LinkedListVector<T>::push_front(const T& value) {
    insert(0, value);
}

template <typename T>
void LinkedListVector<T>::insert(std::size_t index, const T& value) {
    if (index > size_) {
        throw std::out_of_range("LinkedListVector::insert index out of range");
    }

    Node* previous = head_.get();
    for (std::size_t i = 0; i < index; ++i) {
        previous = previous->next.get();
    }

    auto new_node = std::make_unique<Node>();
    new_node->value = value;
    new_node->prev = previous;
    new_node->next = std::move(previous->next);
    new_node->next->prev = new_node.get();
    previous->next = std::move(new_node);
    ++size_;
}

template <typename T>
void LinkedListVector<T>::pop_back() {
}

template <typename T>
void LinkedListVector<T>::pop_front() {
}

template <typename T>
void LinkedListVector<T>::erase(std::size_t index) {
}

template <typename T>
void LinkedListVector<T>::clear() {
    size_ = 0;
    head_->next = std::make_unique<Node>();
    tail_ = head_->next.get();
    tail_->prev = head_.get();
}
