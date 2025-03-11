#include <cstdint>
#include <iostream>
#include <thread>

#include "include/filtering_block.hpp"
#include "include/ring_buffer.hpp"

FilteringBlock::FilteringBlock(uint8_t threshold, float weights[9], RingBuffer &buffer) {
	_inputBuffer = &buffer;
	_threshold = threshold;

	for (int i = 0; i < 9; i++)
		_weights[i] = weights[i];

#ifdef _DEBUG_LOG
	std::cout << _inputBuffer << ": [FilteringBlock] buffer \n";
#endif
}

std::pair<uint8_t, uint8_t> FilteringBlock::applyFilter() {
	// Iterate for now
	float a = 0; float b = 0;

	for (int i = 0; i < 9; i++) {
		a += _weights[i] * _inputBuffer->at(i);
		b += _weights[i + 1] * _inputBuffer->at(i + 1);
	}

	return std::make_pair(a, b);
}

void FilteringBlock::flush() {
	FILE *file = fopen("output.txt", "w");
	if (!file) {
		perror("Error opening file");
		return;
	}

	for (size_t i = 0; i < _outputBuffer.size(); i += 10) {
		for (int j = 0; j < 10; j++) {
			uint8_t value = _outputBuffer[i + j] >= _threshold ? 1 : 0;
			fprintf(file, "%d ", value);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

void FilteringBlock::execute() {
#ifdef _DEBUG_LOG
	std::cout << "[FilteringBlock] Running on Thread ID: " << std::this_thread::get_id() << "\n";
#endif

	auto start = std::chrono::high_resolution_clock::now();

	// Read the input from the ring buffer
	if (!_inputBuffer->read())
		return;

	// Apply SIMD filering and write to outputBuffer
	auto result = applyFilter();
	_outputBuffer.push_back(result.first);
	_outputBuffer.push_back(result.second);

	_inputBuffer->increment();

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	// Ensure execution time is at least 500 ns
	if (elapsed.count() < 500) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(500 - elapsed.count()));
	}
}
