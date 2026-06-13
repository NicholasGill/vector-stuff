# vector_perf

Starter project for comparing vector-like containers implemented with:

- a dynamic array (`ArrayVector`)
- a linked list (`LinkedListVector`)
- a deque-style circular buffer (`DequeVector`)

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

The implementations are intentionally stubbed. The test harness compiles now,
but the contract tests will fail until each container's behavior is implemented.

## Interface

All implementations inherit from `IVector<T>` and support:

- `size`, `capacity`, `empty`
- `at`, `front`, `back`
- `push_back`, `push_front`, `insert`
- `pop_back`, `pop_front`, `erase`
- `clear`

