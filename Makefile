CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Iinclude
BENCH_CXXFLAGS := $(CXXFLAGS) -O3 -DNDEBUG
BENCH_LDLIBS := -lbenchmark -lpthread
BUILD_DIR := build

.PHONY: all test bench clean

all: $(BUILD_DIR)/vector_perf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/vector_perf: src/main.cpp include/*.hpp include/*.tpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/main.cpp -o $@

$(BUILD_DIR)/test_vectors: tests/test_vectors.cpp include/*.hpp include/*.tpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) tests/test_vectors.cpp -o $@

$(BUILD_DIR)/bench_vectors: bench/bench_vectors.cpp bench/*.hpp include/*.hpp include/*.tpp | $(BUILD_DIR)
	$(CXX) $(BENCH_CXXFLAGS) bench/bench_vectors.cpp -o $@ $(BENCH_LDLIBS)

test: $(BUILD_DIR)/test_vectors
	./$(BUILD_DIR)/test_vectors

bench: $(BUILD_DIR)/bench_vectors
	./$(BUILD_DIR)/bench_vectors

clean:
	rm -rf $(BUILD_DIR)
