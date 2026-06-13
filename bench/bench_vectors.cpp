#include "ArrayVector.hpp"
#include "DequeVector.hpp"
#include "LinkedListDequeVector.hpp"
#include "LinkedListVector.hpp"

#include <benchmark/benchmark.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {

template <typename T>
class StdVectorAdapter {
public:
    std::size_t size() const {
        return storage_.size();
    }

    std::size_t capacity() const {
        return storage_.capacity();
    }

    bool empty() const {
        return storage_.empty();
    }

    T& at(std::size_t index) {
        return storage_.at(index);
    }

    const T& at(std::size_t index) const {
        return storage_.at(index);
    }

    T& front() {
        return storage_.front();
    }

    const T& front() const {
        return storage_.front();
    }

    T& back() {
        return storage_.back();
    }

    const T& back() const {
        return storage_.back();
    }

    void push_back(const T& value) {
        storage_.push_back(value);
    }

    void push_front(const T& value) {
        storage_.insert(storage_.begin(), value);
    }

    void insert(std::size_t index, const T& value) {
        storage_.insert(storage_.begin() + static_cast<std::ptrdiff_t>(index), value);
    }

    void pop_back() {
        storage_.pop_back();
    }

    void pop_front() {
        storage_.erase(storage_.begin());
    }

    void erase(std::size_t index) {
        storage_.erase(storage_.begin() + static_cast<std::ptrdiff_t>(index));
    }

    void clear() {
        storage_.clear();
    }

private:
    std::vector<T> storage_;
};

template <typename T, std::size_t InlineCapacity>
class SmallVector {
public:
    SmallVector()
        : size_(0),
          capacity_(InlineCapacity),
          heap_(nullptr) {
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("SmallVector::at index out of range");
        }
        return data()[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("SmallVector::at index out of range");
        }
        return data()[index];
    }

    T& front() {
        return at(0);
    }

    const T& front() const {
        return at(0);
    }

    T& back() {
        return at(size_ - 1);
    }

    const T& back() const {
        return at(size_ - 1);
    }

    void push_back(const T& value) {
        insert(size_, value);
    }

    void push_front(const T& value) {
        insert(0, value);
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("SmallVector::insert index out of range");
        }

        ensure_capacity(size_ + 1);
        T* values = data();
        for (std::size_t i = size_; i > index; --i) {
            values[i] = values[i - 1];
        }

        values[index] = value;
        ++size_;
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("SmallVector::pop_back on empty vector");
        }
        --size_;
    }

    void pop_front() {
        erase(0);
    }

    void erase(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("SmallVector::erase index out of range");
        }

        T* values = data();
        for (std::size_t i = index; i + 1 < size_; ++i) {
            values[i] = values[i + 1];
        }

        --size_;
    }

    void clear() {
        size_ = 0;
    }

private:
    T* data() {
        return heap_ == nullptr ? inline_.data() : heap_.get();
    }

    const T* data() const {
        return heap_ == nullptr ? inline_.data() : heap_.get();
    }

    void ensure_capacity(std::size_t required) {
        if (required <= capacity_) {
            return;
        }

        std::size_t new_capacity = std::max(required, capacity_ * 2);
        auto new_heap = std::make_unique<T[]>(new_capacity);
        const T* old_data = data();

        for (std::size_t i = 0; i < size_; ++i) {
            new_heap[i] = old_data[i];
        }

        heap_ = std::move(new_heap);
        capacity_ = new_capacity;
    }

    std::size_t size_;
    std::size_t capacity_;
    std::array<T, InlineCapacity> inline_;
    std::unique_ptr<T[]> heap_;
};

template <typename Vec>
void fill_vector(Vec& vec, std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        vec.push_back(static_cast<int>(i));
    }
}

template <typename Vec>
static void BM_PushBack(benchmark::State& state) {
    const auto size = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        Vec vec;
        for (std::size_t i = 0; i < size; ++i) {
            vec.push_back(static_cast<int>(i));
        }
        benchmark::DoNotOptimize(vec.size());
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long long>(size));
}

template <typename Vec>
static void BM_PushFront(benchmark::State& state) {
    const auto size = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        Vec vec;
        for (std::size_t i = 0; i < size; ++i) {
            vec.push_front(static_cast<int>(i));
        }
        benchmark::DoNotOptimize(vec.size());
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long long>(size));
}

template <typename Vec>
static void BM_InsertMiddle(benchmark::State& state) {
    const auto size = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        Vec vec;
        for (std::size_t i = 0; i < size; ++i) {
            vec.insert(vec.size() / 2, static_cast<int>(i));
        }
        benchmark::DoNotOptimize(vec.size());
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long long>(size));
}

template <typename Vec>
static void BM_AtSequential(benchmark::State& state) {
    const auto size = static_cast<std::size_t>(state.range(0));
    Vec vec;
    fill_vector(vec, size);

    for (auto _ : state) {
        std::size_t sum = 0;
        for (std::size_t i = 0; i < size; ++i) {
            sum += static_cast<std::size_t>(vec.at(i));
        }
        benchmark::DoNotOptimize(sum);
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long long>(size));
}

template <typename Vec>
static void BM_PopBack(benchmark::State& state) {
    const auto size = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        Vec vec;
        fill_vector(vec, size);
        state.ResumeTiming();

        while (!vec.empty()) {
            vec.pop_back();
        }
        benchmark::DoNotOptimize(vec.size());
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long long>(size));
}

template <typename Vec>
static void BM_PopFront(benchmark::State& state) {
    const auto size = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        Vec vec;
        fill_vector(vec, size);
        state.ResumeTiming();

        while (!vec.empty()) {
            vec.pop_front();
        }
        benchmark::DoNotOptimize(vec.size());
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long long>(size));
}

template <typename Vec>
static void BM_EraseMiddle(benchmark::State& state) {
    const auto size = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        Vec vec;
        fill_vector(vec, size);
        state.ResumeTiming();

        while (!vec.empty()) {
            vec.erase(vec.size() / 2);
        }
        benchmark::DoNotOptimize(vec.size());
    }
    state.SetItemsProcessed(state.iterations() * static_cast<long long>(size));
}

template <typename Vec>
void register_container(const char* name) {
    constexpr int min_size = 100;
    constexpr int max_size = 10000;

    benchmark::RegisterBenchmark((std::string(name) + "/push_back").c_str(), &BM_PushBack<Vec>)
        ->Range(min_size, max_size);
    benchmark::RegisterBenchmark((std::string(name) + "/push_front").c_str(), &BM_PushFront<Vec>)
        ->Range(min_size, max_size);
    benchmark::RegisterBenchmark((std::string(name) + "/insert_middle").c_str(), &BM_InsertMiddle<Vec>)
        ->Range(min_size, max_size);
    benchmark::RegisterBenchmark((std::string(name) + "/at_sequential").c_str(), &BM_AtSequential<Vec>)
        ->Range(min_size, max_size);
    benchmark::RegisterBenchmark((std::string(name) + "/pop_back").c_str(), &BM_PopBack<Vec>)
        ->Range(min_size, max_size);
    benchmark::RegisterBenchmark((std::string(name) + "/pop_front").c_str(), &BM_PopFront<Vec>)
        ->Range(min_size, max_size);
    benchmark::RegisterBenchmark((std::string(name) + "/erase_middle").c_str(), &BM_EraseMiddle<Vec>)
        ->Range(min_size, max_size);
}

} // namespace

int main(int argc, char** argv) {
    register_container<StdVectorAdapter<int>>("std_vector");
    register_container<SmallVector<int, 64>>("small_vector_64");
    register_container<ArrayVector<int>>("array_vector");
    register_container<LinkedListVector<int>>("linked_list_vector");
    register_container<LinkedListDequeVector<int>>("linked_list_deque_vector");
    register_container<DequeVector<int>>("deque_vector_array_backed");

    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
