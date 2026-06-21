#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <memory>
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
    struct Node {
        Key key;
        Value value;
        std::unique_ptr<Node> next;

        Node(const Key& key, const Value& value)
            : key(key),
              value(value) {
        }
    };

    std::size_t hash(const Key& key) const;

    static constexpr std::size_t bucket_count_ = 16;
    std::array<std::unique_ptr<Node>, bucket_count_> buckets_;
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
    const std::size_t bucket_index = hash(key) % bucket_count_;
    const Node* current = buckets_[bucket_index].get();

    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }

        current = current->next.get();
    }
    return false;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key& key, const Value& value) {
    const std::size_t bucket_index = hash(key) % bucket_count_;
    Node* current = buckets_[bucket_index].get();

    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return;
        }

        current = current->next.get();
    }

    auto new_node = std::make_unique<Node>(key, value);
    new_node->next = std::move(buckets_[bucket_index]);
    buckets_[bucket_index] = std::move(new_node);
    ++size_;
}

template <typename Key, typename Value>
Value& HashMap<Key, Value>::at(const Key& key) {
    const std::size_t bucket_index = hash(key) % bucket_count_;
    Node* current = buckets_[bucket_index].get();

    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }

        current = current->next.get();
    }
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

template <typename Key, typename Value>
std::size_t HashMap<Key, Value>::hash(const Key& key) const {
    return std::hash<Key>{}(key);
}
