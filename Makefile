CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Iinclude
BUILD_DIR := build

.PHONY: all test clean

all: $(BUILD_DIR)/vector_perf

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/vector_perf: src/main.cpp include/*.hpp include/*.tpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/main.cpp -o $@

$(BUILD_DIR)/test_vectors: tests/test_vectors.cpp include/*.hpp include/*.tpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) tests/test_vectors.cpp -o $@

test: $(BUILD_DIR)/test_vectors
	./$(BUILD_DIR)/test_vectors

clean:
	rm -rf $(BUILD_DIR)

