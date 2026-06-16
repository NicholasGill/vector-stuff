#pragma once

#include <cstddef>
#include <stdexcept>

template <typename Key, typename Value>
class HashMap {
public:
    HashMap() = default;

    std::size_t size() const;
    bool empty() const;
    bool contains(const Key& key) const;

    void insert(const Key& key, const Value& value);

    Value& at(const Key& key);
    const Value& at(const Key& key) const;

    void erase(const Key& key);
    void clear();

private:
    std::size_t size_ = 0;
};

template <typename Key, typename Value>
std::size_t HashMap<Key, Value>::size() const {
    return size_;
}

template <typename Key, typename Value>
bool HashMap<Key, Value>::empty() const {
    return size_ == 0;
}

template <typename Key, typename Value>
bool HashMap<Key, Value>::contains(const Key& key) const {
    (void)key;
    return false;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key& key, const Value& value) {
    (void)key;
    (void)value;
}

template <typename Key, typename Value>
Value& HashMap<Key, Value>::at(const Key& key) {
    (void)key;
    throw std::out_of_range("HashMap::at missing key");
}

template <typename Key, typename Value>
const Value& HashMap<Key, Value>::at(const Key& key) const {
    (void)key;
    throw std::out_of_range("HashMap::at missing key");
}

template <typename Key, typename Value>
void HashMap<Key, Value>::erase(const Key& key) {
    (void)key;
    throw std::out_of_range("HashMap::erase missing key");
}

template <typename Key, typename Value>
void HashMap<Key, Value>::clear() {
    size_ = 0;
}
