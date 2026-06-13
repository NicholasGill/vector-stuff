# vector_perf

Starter project for implementing and comparing vector-like containers in C++20.

The repo currently contains three implementations behind the same `IVector<T>` interface:

- `ArrayVector`: dynamic-array-backed vector
- `LinkedListVector`: linked-list-backed vector
- `DequeVector`: deque-style circular buffer

## Current Status

This project is intentionally in progress. `make test` is expected to fail until all vector methods are implemented.

Current implementation status:

- `ArrayVector` has partial behavior for `at`, `front`, `back`, `push_back`, `pop_back`, `clear`, `size`, `capacity`, and `empty`.
- `ArrayVector` still needs correct implementations for `push_front`, `insert`, `pop_front`, `erase`, and empty-removal error handling.
- `LinkedListVector` is mostly a placeholder.
- `DequeVector` is mostly a placeholder.
- The test harness now reports method-level pass/fail results for all three vector types.

The latest observed `make test` run reports `29 test(s) failed`.

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

The tests compile and run, but they intentionally return a failing exit code while the implementations are incomplete.

## Interface

All implementations inherit from `IVector<T>` and support:

- `size`, `capacity`, `empty`
- `at`, `front`, `back`
- `push_back`, `push_front`, `insert`
- `pop_back`, `pop_front`, `erase`
- `clear`

## Codex Notes

Repo-level Codex guidance lives in `AGENTS.md`.
