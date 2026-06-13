# vector_perf

Starter project for implementing and comparing vector-like containers in C++20.

The repo currently contains three implementations behind the same `IVector<T>` interface:

- `ArrayVector`: dynamic-array-backed vector
- `LinkedListVector`: linked-list-backed vector
- `DequeVector`: deque-style circular buffer

## Current Status

This project is intentionally in progress. `make test` is expected to fail until all vector implementations are complete.

Current implementation status:

- `ArrayVector` passes its method-level contract tests.
- `LinkedListVector` passes its method-level contract tests and uses sentinel nodes with `std::unique_ptr` ownership for forward links.
- `DequeVector` is mostly a placeholder.
- The test harness now reports method-level pass/fail results for all three vector types.

The latest observed `make test` run reports `11 test(s) failed`, all in `DequeVector`.

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

The tests compile and run, but they intentionally return a failing exit code while `DequeVector` remains incomplete.

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
