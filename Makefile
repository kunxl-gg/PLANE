# Application settings
APP_NAME := cynlr
BUILD_DIR := ./build
SRC_FILES := $(wildcard ./src/*.cpp)

# Compiler and flags
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -I/Users/kunaltiwari/cynlr/include/

default: run

# Default build
build:
	@$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(APP_NAME)

# Debug build
debug:
	@$(CXX) $(CXXFLAGS) -g -O0 $(SRC_FILES) -o $(BUILD_DIR)/$(APP_NAME)

# Run the application
run: build
	@./$(BUILD_DIR)/$(APP_NAME)

.PHONY: build debug run
