#include <cstddef>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#if __has_include("HashMap.hpp")
#include "HashMap.hpp"
#define VECTOR_PERF_HAS_HASH_MAP 1
#else
#define VECTOR_PERF_HAS_HASH_MAP 0
#endif

#if __has_include("Heap.hpp")
#include "Heap.hpp"
#define VECTOR_PERF_HAS_HEAP 1
#else
#define VECTOR_PERF_HAS_HEAP 0
#endif

#if __has_include("RingBuffer.hpp")
#include "RingBuffer.hpp"
#define VECTOR_PERF_HAS_RING_BUFFER 1
#else
#define VECTOR_PERF_HAS_RING_BUFFER 0
#endif

namespace {

struct TestFailure : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct TestCase {
    std::string name;
    std::function<void()> run;
};

[[maybe_unused]] void expect(bool condition, const std::string& message) {
    if (!condition) {
        throw TestFailure(message);
    }
}

template <typename Exception, typename Func>
void expect_throws(Func func, const std::string& message) {
    try {
        func();
    } catch (const Exception&) {
        return;
    }

    throw TestFailure(message);
}

#if VECTOR_PERF_HAS_HASH_MAP

void test_hash_map_starts_empty() {
    HashMap<std::string, int> map;

    expect(map.empty(), "new map should be empty");
    expect(map.size() == 0, "new map size should be zero");
    expect(!map.contains("missing"), "new map should not contain arbitrary keys");
}

void test_hash_map_insert_lookup_and_update() {
    HashMap<std::string, int> map;

    map.insert("one", 1);
    map.insert("two", 2);

    expect(!map.empty(), "map should not be empty after insert");
    expect(map.size() == 2, "map should count inserted keys");
    expect(map.contains("one"), "map should contain inserted key");
    expect(map.at("one") == 1, "at should return inserted value");

    map.insert("one", 11);

    expect(map.size() == 2, "updating an existing key should not change size");
    expect(map.at("one") == 11, "insert on an existing key should update value");
}

void test_hash_map_at_modifies_value() {
    HashMap<std::string, int> map;

    map.insert("answer", 41);
    map.at("answer") = 42;

    expect(map.at("answer") == 42, "at should return a modifiable reference");
}

void test_hash_map_missing_key_throws() {
    HashMap<std::string, int> map;

    expect_throws<std::out_of_range>([&]() { map.at("missing"); }, "at on missing key should throw");
    expect_throws<std::out_of_range>([&]() { map.erase("missing"); }, "erase on missing key should throw");
}

void test_hash_map_erase_and_clear() {
    HashMap<std::string, int> map;

    map.insert("one", 1);
    map.insert("two", 2);
    map.erase("one");

    expect(map.size() == 1, "erase should reduce size");
    expect(!map.contains("one"), "erase should remove key");
    expect(map.contains("two"), "erase should preserve other keys");

    map.clear();

    expect(map.empty(), "clear should make map empty");
    expect(map.size() == 0, "clear should reset size");
    expect(!map.contains("two"), "clear should remove existing keys");
}

void add_hash_map_tests(std::vector<TestCase>& tests) {
    tests.push_back({"HashMap starts empty", test_hash_map_starts_empty});
    tests.push_back({"HashMap insert lookup and update", test_hash_map_insert_lookup_and_update});
    tests.push_back({"HashMap at modifies value", test_hash_map_at_modifies_value});
    tests.push_back({"HashMap missing key throws", test_hash_map_missing_key_throws});
    tests.push_back({"HashMap erase and clear", test_hash_map_erase_and_clear});
}

#endif

#if VECTOR_PERF_HAS_HEAP

void test_heap_starts_empty() {
    Heap<int> heap;

    expect(heap.empty(), "new heap should be empty");
    expect(heap.size() == 0, "new heap size should be zero");
}

void test_heap_empty_access_throws() {
    Heap<int> heap;

    expect_throws<std::out_of_range>([&]() { heap.top(); }, "top on empty heap should throw");
    expect_throws<std::out_of_range>([&]() { heap.pop(); }, "pop on empty heap should throw");
}

void test_heap_push_top_and_pop_order() {
    Heap<int> heap;

    heap.push(4);
    heap.push(10);
    heap.push(7);
    heap.push(1);

    expect(heap.size() == 4, "heap should count pushed values");
    expect(heap.top() == 10, "default heap should expose largest value first");

    heap.pop();
    expect(heap.top() == 7, "pop should remove current top");
    heap.pop();
    expect(heap.top() == 4, "heap should preserve priority order after repeated pop");
    heap.pop();
    expect(heap.top() == 1, "last remaining value should become top");
    heap.pop();
    expect(heap.empty(), "heap should be empty after popping all values");
}

void test_heap_custom_comparator() {
    Heap<int, std::greater<int>> heap;

    heap.push(4);
    heap.push(10);
    heap.push(1);

    expect(heap.top() == 1, "std::greater heap should expose smallest value first");
}

void test_heap_clear() {
    Heap<int> heap;

    heap.push(1);
    heap.push(2);
    heap.clear();

    expect(heap.empty(), "clear should make heap empty");
    expect(heap.size() == 0, "clear should reset size");
    expect_throws<std::out_of_range>([&]() { heap.top(); }, "top after clear should throw");
}

void add_heap_tests(std::vector<TestCase>& tests) {
    tests.push_back({"Heap starts empty", test_heap_starts_empty});
    tests.push_back({"Heap empty access throws", test_heap_empty_access_throws});
    tests.push_back({"Heap push top and pop order", test_heap_push_top_and_pop_order});
    tests.push_back({"Heap custom comparator", test_heap_custom_comparator});
    tests.push_back({"Heap clear", test_heap_clear});
}

#endif

#if VECTOR_PERF_HAS_RING_BUFFER

void test_ring_buffer_starts_empty() {
    RingBuffer<int> buffer(3);

    expect(buffer.empty(), "new ring buffer should be empty");
    expect(!buffer.full(), "new ring buffer should not be full");
    expect(buffer.size() == 0, "new ring buffer size should be zero");
    expect(buffer.capacity() == 3, "ring buffer should report construction capacity");
}

void test_ring_buffer_zero_capacity_throws() {
    expect_throws<std::invalid_argument>([]() { RingBuffer<int> buffer(0); }, "zero capacity should throw");
}

void test_ring_buffer_empty_access_throws() {
    RingBuffer<int> buffer(2);

    expect_throws<std::out_of_range>([&]() { buffer.front(); }, "front on empty ring buffer should throw");
    expect_throws<std::out_of_range>([&]() { buffer.back(); }, "back on empty ring buffer should throw");
    expect_throws<std::out_of_range>([&]() { buffer.pop_front(); }, "pop_front on empty ring buffer should throw");
}

void test_ring_buffer_push_pop_and_wrap() {
    RingBuffer<int> buffer(3);

    buffer.push_back(10);
    buffer.push_back(20);
    buffer.push_back(30);

    expect(buffer.full(), "ring buffer should be full at capacity");
    expect(buffer.front() == 10, "front should return oldest value");
    expect(buffer.back() == 30, "back should return newest value");
    expect_throws<std::overflow_error>([&]() { buffer.push_back(40); }, "push_back on full ring buffer should throw");

    buffer.pop_front();
    buffer.push_back(40);

    expect(buffer.full(), "ring buffer should be full after wraparound push");
    expect(buffer.front() == 20, "front should advance after pop_front");
    expect(buffer.back() == 40, "back should track wrapped push_back");

    buffer.pop_front();
    expect(buffer.front() == 30, "ring buffer should preserve FIFO order after wraparound");
    buffer.pop_front();
    expect(buffer.front() == 40, "wrapped value should remain in FIFO order");
    buffer.pop_front();
    expect(buffer.empty(), "ring buffer should be empty after popping all values");
}

void test_ring_buffer_clear() {
    RingBuffer<int> buffer(2);

    buffer.push_back(10);
    buffer.push_back(20);
    buffer.clear();

    expect(buffer.empty(), "clear should make ring buffer empty");
    expect(!buffer.full(), "clear should make ring buffer not full");
    expect(buffer.size() == 0, "clear should reset size");
    expect(buffer.capacity() == 2, "clear should preserve capacity");
}

void add_ring_buffer_tests(std::vector<TestCase>& tests) {
    tests.push_back({"RingBuffer starts empty", test_ring_buffer_starts_empty});
    tests.push_back({"RingBuffer zero capacity throws", test_ring_buffer_zero_capacity_throws});
    tests.push_back({"RingBuffer empty access throws", test_ring_buffer_empty_access_throws});
    tests.push_back({"RingBuffer push pop and wrap", test_ring_buffer_push_pop_and_wrap});
    tests.push_back({"RingBuffer clear", test_ring_buffer_clear});
}

#endif

} // namespace

int main() {
    std::vector<TestCase> tests;

#if VECTOR_PERF_HAS_HASH_MAP
    add_hash_map_tests(tests);
#else
    std::cout << "[SKIP] HashMap tests: include/HashMap.hpp not found\n";
#endif

#if VECTOR_PERF_HAS_HEAP
    add_heap_tests(tests);
#else
    std::cout << "[SKIP] Heap tests: include/Heap.hpp not found\n";
#endif

#if VECTOR_PERF_HAS_RING_BUFFER
    add_ring_buffer_tests(tests);
#else
    std::cout << "[SKIP] RingBuffer tests: include/RingBuffer.hpp not found\n";
#endif

    int failures = 0;
    for (const auto& test : tests) {
        try {
            test.run();
            std::cout << "[PASS] " << test.name << "\n";
        } catch (const std::exception& ex) {
            ++failures;
            std::cout << "[FAIL] " << test.name << ": " << ex.what() << "\n";
        }
    }

    if (failures > 0) {
        std::cout << failures << " test(s) failed.\n";
        return 1;
    }

    std::cout << "All available container tests passed.\n";
    return 0;
}
