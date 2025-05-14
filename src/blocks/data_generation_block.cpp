#include <cstdint>
#include <fstream>
#include <string>
#include <utility>
#include <iostream>
#include <random>
#include <thread>

#include "include/data_generation_block.hpp"
#include "include/debug.hpp"
#include "include/debug-manager.hpp"

DataGenerationBlock::DataGenerationBlock(
	std::string csvPath,
	Queue *inputQueue,
	Queue *outputQueue,
	unsigned int numColumns
)
	: _inputQueue(inputQueue), _outputQueue(outputQueue), _numColumns(numColumns) {

#ifndef _DEBUG
	_csvPath = csvPath;

	_file.open(csvPath);
	if (!_file) {
		std::cerr << "Error in opening file: " << _csvPath << std::endl;
	}
#endif
}

bool DataGenerationBlock::hasMoreData() {
	return !_file.eof();
}

std::pair<PixelData, PixelData> DataGenerationBlock::generateRandomNumbers() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 255);

	static unsigned currentRow = 1;
	static unsigned currentCol = 1;

	// Generate two random numbers
	int a = dist(gen);
	int b = dist(gen);

	PixelData p1 = PixelData(currentRow, currentCol, a);
	PixelData p2 = PixelData(currentRow, currentCol + 1, b);

	currentCol += 2;
	if (currentCol <= _numColumns) {
		currentCol = 0;
		currentRow++;
	}

	return std::make_pair(p1, p2);
}

void DataGenerationBlock::execute() {
	debugC(9, kDebugThread, "[DataGenerationBlock] Running on Thread ID: %d", std::this_thread::get_id());

	std::pair<PixelData, PixelData> pair;

	auto start = std::chrono::high_resolution_clock::now();

#ifndef _DEBUG
	pair = readCSV();
#else
	pair = generateRandomNumbers();
#endif

	if (_outputQueue) {
		_outputQueue->enqueue(pair.first);
		_outputQueue->enqueue(pair.second);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	// Ensure execution time is at least 500 ns
	if (elapsed.count() < 500) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(500 - elapsed.count()));
	}
}

