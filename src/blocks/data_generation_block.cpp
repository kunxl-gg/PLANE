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

DataGenerationBlock::DataGenerationBlock(RingBuffer &buffer, std::string csvPath) {
	_buffer = &buffer;
	_csvPath = csvPath;

	_file.open(csvPath);
	if (!_file) {
		std::cerr << "Error in opening file: " << _csvPath << std::endl;
	}
}

DataGenerationBlock& DataGenerationBlock::operator=(const DataGenerationBlock &other)  {
	return *this;
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
#ifdef _DEBUG_LOG
	std::cout << "[DataGenerationBlock] Running on Thread ID: " << std::this_thread::get_id() << "\n";
#endif

#ifdef _DEBUG
	auto start = std::chrono::high_resolution_clock::now();

	auto input = generateRandomNumbers();
	bool result = _buffer->write(input.first, input.second);

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	if (result && elapsed.count() < 500) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(500 - elapsed.count()));
	}

#else
	auto start = std::chrono::high_resolution_clock::now();

	bool result = false;
	if (!_file.eof()) {
		auto input = readCSV();
		result = _buffer->write(input.first, input.second);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	if (result && elapsed.count() < 500) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(500 - elapsed.count()));
	}
#endif
}

