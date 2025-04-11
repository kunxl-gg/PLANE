#include <iostream>

#include "include/pipeline.hpp"

Pipeline::Pipeline(size_t bufferSize, std::string csvPath, byte threshold, float weights[9])
	: _running(false),
	_buffer(bufferSize),
	_dataBlock(csvPath, _buffer),
	_filterBlock(threshold, weights, _buffer) {
}

void Pipeline::start() {
	std::cout << "Starting Pipeline...\n";

	_running = true;
	_dataThread = std::thread(&Pipeline::runDataGeneration, this);
	_filterThread = std::thread(&Pipeline::runFiltering, this);
}

void Pipeline::stop() {
	std::cout << "Stopping Pipeline...\n";

	_running = false;

	if (_dataThread.joinable()) {
		_dataThread.join();
	}

	if (_filterThread.joinable()) {
		_filterThread.join();
	}

	_filterBlock.flush();
}

bool Pipeline::should_run() {
	return _dataBlock.hasMoreData();
}

void Pipeline::runDataGeneration() {
	while (_running.load(std::memory_order_relaxed)) {
		_dataBlock.execute();
	}
}

void Pipeline::runFiltering() {
	while (_running.load(std::memory_order_relaxed)) {
		_filterBlock.execute();
	}
}
