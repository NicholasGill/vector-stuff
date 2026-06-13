# vector_perf

Starter project for implementing and comparing vector-like containers in C++20.

The repo currently contains four implementations behind the same `IVector<T>` interface:

- `ArrayVector`: dynamic-array-backed vector
- `LinkedListVector`: linked-list-backed vector
- `LinkedListDequeVector`: deque API implemented by delegating to `LinkedListVector`
- `DequeVector`: deque API implemented by delegating to `ArrayVector`

## Current Status

This project is intentionally in progress. `make test` is expected to fail until all vector implementations are complete.

Current implementation status:

- `ArrayVector` passes its method-level contract tests.
- `LinkedListVector` passes its method-level contract tests and uses sentinel nodes with `std::unique_ptr` ownership for forward links.
- `LinkedListDequeVector` passes its method-level contract tests by using `LinkedListVector` internally.
- `DequeVector` passes its method-level contract tests by using `ArrayVector` internally.
- The test harness now reports method-level pass/fail results for all four vector types.

The latest observed `make test` run passes all tests.

## Build

```sh
make
```

## Run the sample program

```sh
./build/vector_perf
```

## Run tests

```sh
make test
```

The tests compile and run through the method-level contract for each vector implementation.

## Run benchmarks

```sh
make bench
```

The benchmark target uses Google Benchmark and builds with optimization. Install Google Benchmark first if your system does not provide `benchmark/benchmark.h` and `libbenchmark`.

On Ubuntu:

```sh
sudo apt-get install libbenchmark-dev
```

The benchmark compares `std::vector`, a benchmark-local `SmallVector<64>`, and the project vector implementations across common operations such as push, insert, indexed access, pop, and erase.

## Interface

All implementations inherit from `IVector<T>` and support:

- `size`, `capacity`, `empty`
- `at`, `front`, `back`
- `push_back`, `push_front`, `insert`
- `pop_back`, `pop_front`, `erase`
- `clear`

## Codex Notes

Repo-level Codex guidance lives in `AGENTS.md`.

Documentation should be reviewed and updated before each commit when code or test status changes.
