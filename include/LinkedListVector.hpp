#pragma once

#include "IVector.hpp"

#include <cstddef>
#include <memory>

template <typename T>
class LinkedListVector : public IVector<T> {
public:
    LinkedListVector();
    ~LinkedListVector() override = default;

    std::size_t size() const override;
    std::size_t capacity() const override;
    bool empty() const override;

    T& at(std::size_t index) override;
    const T& at(std::size_t index) const override;

    T& front() override;
    const T& front() const override;
    T& back() override;
    const T& back() const override;

    void push_back(const T& value) override;
    void push_front(const T& value) override;
    void insert(std::size_t index, const T& value) override;

    void pop_back() override;
    void pop_front() override;
    void erase(std::size_t index) override;

    void clear() override;

private:
    struct Node {
        T value;
        std::unique_ptr<Node> next;
        Node* prev = nullptr;
    };

    std::size_t size_ = 0;
    std::unique_ptr<Node> head_;
    Node* tail_ = nullptr;
};

#include "LinkedListVector.tpp"
