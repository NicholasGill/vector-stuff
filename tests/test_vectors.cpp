#include "ArrayVector.hpp"
#include "DequeVector.hpp"
#include "LinkedListDequeVector.hpp"
#include "LinkedListVector.hpp"

#include <cstddef>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

struct TestFailure : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct TestCase {
    std::string name;
    std::function<void()> run;
};

void expect(bool condition, const std::string& message) {
    if (!condition) {
        throw TestFailure(message);
    }
}

template <typename Func>
void expect_out_of_range(Func func, const std::string& message) {
    try {
        func();
    } catch (const std::out_of_range&) {
        return;
    }

    throw TestFailure(message);
}

template <typename Vec>
void expect_contents(Vec& vec, const std::vector<int>& expected) {
    expect(vec.size() == expected.size(), "size does not match expected contents");

    for (std::size_t i = 0; i < expected.size(); ++i) {
        expect(vec.at(i) == expected[i], "element mismatch at index " + std::to_string(i));
    }
}

template <typename Vec>
void test_starts_empty(const std::string& name) {
    Vec vec;

    expect(vec.empty(), name + ": new vector should be empty");
    expect(vec.size() == 0, name + ": new vector size should be zero");
}

template <typename Vec>
void test_empty_access_throws(const std::string& name) {
    Vec vec;

    expect_out_of_range([&]() { vec.at(0); }, name + ": at(0) on empty vector should throw");
    expect_out_of_range([&]() { vec.front(); }, name + ": front on empty vector should throw");
    expect_out_of_range([&]() { vec.back(); }, name + ": back on empty vector should throw");
}

template <typename Vec>
void test_empty_removes_throw(const std::string& name) {
    Vec vec;

    expect_out_of_range([&]() { vec.pop_back(); }, name + ": pop_back on empty vector should throw");
    expect_out_of_range([&]() { vec.pop_front(); }, name + ": pop_front on empty vector should throw");
    expect_out_of_range([&]() { vec.erase(0); }, name + ": erase on empty vector should throw");
}

template <typename Vec>
void test_push_back(const std::string& name) {
    Vec vec;

    vec.push_back(10);
    vec.push_back(20);

    expect(!vec.empty(), name + ": vector should not be empty after push_back");
    expect_contents(vec, {10, 20});
    expect(vec.front() == 10, name + ": front should return first element");
    expect(vec.back() == 20, name + ": back should return last element");
}

template <typename Vec>
void test_push_front(const std::string& name) {
    (void)name;
    Vec vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_front(5);

    expect_contents(vec, {5, 10, 20});
}

template <typename Vec>
void test_insert(const std::string& name) {
    (void)name;
    Vec vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.insert(1, 15);
    vec.insert(vec.size(), 30);

    expect_contents(vec, {10, 15, 20, 30});
}

template <typename Vec>
void test_insert_past_end_throws(const std::string& name) {
    Vec vec;

    vec.push_back(10);

    expect_out_of_range([&]() { vec.insert(vec.size() + 1, 99); }, name + ": insert past end should throw");
}

template <typename Vec>
void test_at_modifies_element(const std::string& name) {
    Vec vec;

    vec.push_back(10);
    vec.at(0) = 42;

    expect(vec.at(0) == 42, name + ": at should return a modifiable reference");
}

template <typename Vec>
void test_at_size_throws(const std::string& name) {
    Vec vec;

    vec.push_back(10);

    expect_out_of_range([&]() { vec.at(vec.size()); }, name + ": at(size) should throw");
}

template <typename Vec>
void test_pop_back(const std::string& name) {
    (void)name;
    Vec vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.pop_back();

    expect_contents(vec, {10});
}

template <typename Vec>
void test_pop_front(const std::string& name) {
    (void)name;
    Vec vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.pop_front();

    expect_contents(vec, {20, 30});
}

template <typename Vec>
void test_erase(const std::string& name) {
    (void)name;
    Vec vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.erase(1);

    expect_contents(vec, {10, 30});
}

template <typename Vec>
void test_erase_size_throws(const std::string& name) {
    Vec vec;

    vec.push_back(10);

    expect_out_of_range([&]() { vec.erase(vec.size()); }, name + ": erase(size) should throw");
}

template <typename Vec>
void test_clear(const std::string& name) {
    Vec vec;

    vec.push_back(10);
    vec.push_back(20);
    expect(!vec.empty(), name + ": vector should not be empty before clear");

    vec.clear();

    expect(vec.empty(), name + ": clear should make vector empty");
    expect(vec.size() == 0, name + ": clear should reset size");
    expect_out_of_range([&]() { vec.at(0); }, name + ": at(0) after clear should throw");
}

template <typename Vec>
void add_vector_tests(std::vector<TestCase>& tests, const std::string& name) {
    tests.push_back({name + " starts empty", [name]() { test_starts_empty<Vec>(name); }});
    tests.push_back({name + " empty access throws", [name]() { test_empty_access_throws<Vec>(name); }});
    tests.push_back({name + " empty removes throw", [name]() { test_empty_removes_throw<Vec>(name); }});
    tests.push_back({name + " push_back", [name]() { test_push_back<Vec>(name); }});
    tests.push_back({name + " push_front", [name]() { test_push_front<Vec>(name); }});
    tests.push_back({name + " insert", [name]() { test_insert<Vec>(name); }});
    tests.push_back({name + " insert past end throws", [name]() { test_insert_past_end_throws<Vec>(name); }});
    tests.push_back({name + " at modifies element", [name]() { test_at_modifies_element<Vec>(name); }});
    tests.push_back({name + " at(size) throws", [name]() { test_at_size_throws<Vec>(name); }});
    tests.push_back({name + " pop_back", [name]() { test_pop_back<Vec>(name); }});
    tests.push_back({name + " pop_front", [name]() { test_pop_front<Vec>(name); }});
    tests.push_back({name + " erase", [name]() { test_erase<Vec>(name); }});
    tests.push_back({name + " erase(size) throws", [name]() { test_erase_size_throws<Vec>(name); }});
    tests.push_back({name + " clear", [name]() { test_clear<Vec>(name); }});
}

} // namespace

int main() {
    std::vector<TestCase> tests;
    add_vector_tests<ArrayVector<int>>(tests, "ArrayVector");
    add_vector_tests<LinkedListVector<int>>(tests, "LinkedListVector");
    add_vector_tests<LinkedListDequeVector<int>>(tests, "LinkedListDequeVector");
    add_vector_tests<DequeVector<int>>(tests, "DequeVector");

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

    std::cout << "All tests passed.\n";
    return 0;
}
