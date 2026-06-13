#pragma once

#include "IVector.hpp"

#include <cstddef>

#include <memory>

template <typename T>
class ArrayVector : public IVector<T> {
public:
    ArrayVector();
    explicit ArrayVector(std::size_t capacity);

    // Destructor is automatically handled by unique pointer via RAII

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
    std::size_t size_;
    std::size_t capacity_ = 0;
    std::unique_ptr<T[]> data;
};

#include "ArrayVector.tpp"
