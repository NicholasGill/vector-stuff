#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class IVector {
public:
    virtual ~IVector() = default;

    virtual std::size_t size() const = 0;
    virtual std::size_t capacity() const = 0;
    virtual bool empty() const = 0;

    virtual T& at(std::size_t index) = 0;
    virtual const T& at(std::size_t index) const = 0;

    virtual T& front() = 0;
    virtual const T& front() const = 0;
    virtual T& back() = 0;
    virtual const T& back() const = 0;

    virtual void push_back(const T& value) = 0;
    virtual void push_front(const T& value) = 0;
    virtual void insert(std::size_t index, const T& value) = 0;

    virtual void pop_back() = 0;
    virtual void pop_front() = 0;
    virtual void erase(std::size_t index) = 0;

    virtual void clear() = 0;
};

