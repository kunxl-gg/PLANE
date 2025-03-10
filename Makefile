# Application settings
APP_NAME := cynlr
BUILD_DIR := ./build
SRC_FILES := $(wildcard ./src/**/*.cpp) $(wildcard ./src/*.cpp)

# Compiler and flags
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -I/Users/kunaltiwari/cynlr

default: debug run

# Default build
build:
	@$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(APP_NAME)

# Debug build
debug:
	$(CXX) $(CXXFLAGS) -g -O0 -D_DEBUG $(SRC_FILES) -o $(BUILD_DIR)/$(APP_NAME)

# Run the application
run:
	@./$(BUILD_DIR)/$(APP_NAME)

.PHONY: build debug run
