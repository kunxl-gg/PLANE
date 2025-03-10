APP_NAME := cynlr
BUILD_DIR := ./build
SRC_FILES := $(wildcard ./src/**/*.cpp) $(wildcard ./src/*.cpp)

CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -I/Users/kunaltiwari/cynlr

default: debug run

build:
	@$(CXX) $(CXXFLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(APP_NAME)

debug:
	$(CXX) $(CXXFLAGS) -g -O0 -D_DEBUG $(SRC_FILES) -o $(BUILD_DIR)/$(APP_NAME)

run:
	@./$(BUILD_DIR)/$(APP_NAME)
