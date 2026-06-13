#include "ArrayVector.hpp"
#include "DequeVector.hpp"
#include "IVector.hpp"
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
void run_vector_contract(const std::string& name) {
    Vec vec;

    expect(vec.empty(), name + ": new vector should be empty");
    expect(vec.size() == 0, name + ": new vector size should be zero");
    expect_out_of_range([&]() { vec.at(0); }, name + ": at(0) on empty vector should throw");
    expect_out_of_range([&]() { vec.front(); }, name + ": front on empty vector should throw");
    expect_out_of_range([&]() { vec.back(); }, name + ": back on empty vector should throw");

    vec.push_back(10);
    vec.push_back(20);
    vec.push_front(5);
    expect_contents(vec, {5, 10, 20});
    expect(!vec.empty(), name + ": vector should not be empty after inserts");
    expect(vec.front() == 5, name + ": front should return first element");
    expect(vec.back() == 20, name + ": back should return last element");

    vec.insert(1, 7);
    vec.insert(vec.size(), 30);
    expect_contents(vec, {5, 7, 10, 20, 30});

    vec.at(2) = 11;
    expect_contents(vec, {5, 7, 11, 20, 30});

    vec.erase(1);
    expect_contents(vec, {5, 11, 20, 30});

    vec.pop_front();
    vec.pop_back();
    expect_contents(vec, {11, 20});

    expect_out_of_range([&]() { vec.at(vec.size()); }, name + ": at(size) should throw");
    expect_out_of_range([&]() { vec.insert(vec.size() + 1, 99); }, name + ": insert past end should throw");
    expect_out_of_range([&]() { vec.erase(vec.size()); }, name + ": erase(size) should throw");

    vec.clear();
    expect(vec.empty(), name + ": clear should make vector empty");
    expect(vec.size() == 0, name + ": clear should reset size");
}

struct TestCase {
    std::string name;
    std::function<void()> run;
};

} // namespace

int main() {
    const std::vector<TestCase> tests = {
        {"ArrayVector", []() { run_vector_contract<ArrayVector<int>>("ArrayVector"); }},
        {"LinkedListVector", []() { run_vector_contract<LinkedListVector<int>>("LinkedListVector"); }},
        {"DequeVector", []() { run_vector_contract<DequeVector<int>>("DequeVector"); }},
    };

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

