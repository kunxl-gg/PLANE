#include <iostream>

#include "include/pipeline.hpp"

Pipeline::Pipeline(uint8_t threshold, float weights[9], size_t bufferSize)
	: _running(false),
	  _buffer(bufferSize),
	  _dataBlock(_buffer, "data.csv"),
	  _filterBlock(threshold, weights, _buffer) {
}

Pipeline::~Pipeline() {
}

void Pipeline::start() {
	printf("%s",  "Starting Pipeline...\n");

	_running = true;
	_dataThread = std::thread(&Pipeline::runDataGeneration, this);
	_filterThread = std::thread(&Pipeline::runFiltering, this);
}

void Pipeline::stop() {
	printf("%s", "Stopping Pipeline...\n");

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
	return false;
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
