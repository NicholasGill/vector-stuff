#include "BenchmarkVectors.hpp"

#include "ArrayVector.hpp"
#include "DequeVector.hpp"
#include "LinkedListDequeVector.hpp"
#include "LinkedListVector.hpp"

#include <benchmark/benchmark.h>

#include <cstddef>
#include <string>

namespace {

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
