# Repository Guidelines

## Project Shape

This is a C++20 starter project for implementing and comparing vector-like containers:

- `ArrayVector<T>`: dynamic-array-backed vector in `include/ArrayVector.hpp` and `include/ArrayVector.tpp`
- `LinkedListVector<T>`: linked-list-backed vector in `include/LinkedListVector.hpp` and `include/LinkedListVector.tpp`
- `LinkedListDequeVector<T>`: deque API backed by `LinkedListVector<T>` in `include/LinkedListDequeVector.hpp` and `include/LinkedListDequeVector.tpp`
- `DequeVector<T>`: circular-buffer/deque-style vector in `include/DequeVector.hpp` and `include/DequeVector.tpp`

All implementations inherit from `IVector<T>`.

## Commands

- Build the sample program: `make`
- Run the sample program: `./build/vector_perf`
- Run contract tests: `make test`
- Remove generated build artifacts: `make clean`

## Current State

The repo is intentionally incomplete. Do not treat failing tests as a harness problem by default. The tests are method-level contract checks that show which vector operations still need implementation.

At the current snapshot, `ArrayVector`, `LinkedListVector`, and `LinkedListDequeVector` pass their method-level contract tests, while `DequeVector` is mostly placeholder for an array-backed deque.

## Coding Notes

- Keep template implementations in the corresponding `.tpp` files.
- Prefer the existing simple style over adding new abstractions.
- Preserve the `IVector<T>` public interface unless explicitly asked to change it.
- When adding behavior, run `make test` and use the per-method failures to guide the next implementation step.
- Before making a commit, check whether `README.md`, `AGENTS.md`, or other docs need to be updated to match the code and test status. Include those documentation updates in the same commit when they describe the change being committed.
- Avoid committing generated files under `build/`.
