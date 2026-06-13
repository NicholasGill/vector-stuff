#pragma once

#include "IVector.hpp"
#include "LinkedListVector.hpp"

#include <cstddef>

template <typename T>
class LinkedListDequeVector : public IVector<T> {
public:
    LinkedListDequeVector() = default;
    ~LinkedListDequeVector() override = default;

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
    LinkedListVector<T> storage_;
};

#include "LinkedListDequeVector.tpp"
