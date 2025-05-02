#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <random>
#include <thread>

#include "include/data_generation_block.hpp"
#include "include/debug.hpp"

DataGenerationBlock::DataGenerationBlock(std::string csvPath, RingBuffer &buffer) {
	_buffer = &buffer;
	_csvPath = csvPath;

	_file.open(csvPath);
	if (!_file) {
		std::cerr << "Error in opening file: " << _csvPath << std::endl;
	}
}

bool DataGenerationBlock::hasMoreData() {
	return !_file.eof();
}

std::pair<byte, byte> DataGenerationBlock::readCSV() {
	if (!_file.is_open()) {
		std::cerr << "Error: File not open." << std::endl;
	}

	uint8_t first, second;
	char comma;

	_file >> first >> comma >> second;
	return std::make_pair(first, second);

}

std::pair<byte, byte> DataGenerationBlock::generateRandomNumbers() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 255);

	// Generate two random numbers
	int a = dist(gen);
	int b = dist(gen);

	return std::make_pair(a, b);
}

void DataGenerationBlock::execute() {
	debug("[DataGenerationBlock] Running on Thread ID: %d", std::this_thread::get_id());
}

