#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <thread>

#include "include/data_generation_block.hpp"

DataGenerationBlock::DataGenerationBlock(RingBuffer &buffer, std::string csvPath) {
	_buffer = &buffer;
	_csvPath = csvPath;

	std::cout << _buffer << ": [DataGenerationBlock] buffer \n";
}

void DataGenerationBlock::readCSV() {
	std::ifstream file(_csvPath);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << _csvPath << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::vector<uint8_t> values;
		uint8_t num;

		while (ss >> num) {
			values.push_back(num);
			if (ss.peek() == ',') ss.ignore(); // Ignore commas
		}

		for (size_t i = 0; i + 1 < values.size(); i += 2) {
			_buffer->write(values[i], values[i + 1]);
		}
	}
}

void DataGenerationBlock::generateRandomNumbers() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint8_t> dist(0, 255);

	// Generate two random numbers
	uint8_t a = dist(gen);
	uint8_t b = dist(gen);

	 _buffer->write(a, b);
}

void DataGenerationBlock::execute() {
#ifdef _DEBUG_LOG
	std::cout << "[DataGenerationBlock] Running on Thread ID: " << std::this_thread::get_id() << "\n";
#endif

#ifdef _DEBUG
	generateRandomNumbers();
#else
	readCSV();
#endif
}

