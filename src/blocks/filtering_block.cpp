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

std::pair<uint8_t, uint8_t> FilteringBlock::applySIMDFilter() {
	// Iterate for now
	float a = 0; float b = 0;

	for (int i = 0; i < 9; i++) {
		a += _weights[i] * _inputBuffer->at(i);
		b += _weights[i + 1] * _inputBuffer->at(i + 1);
	}

	return std::make_pair(a, b);
}

void FilteringBlock::execute() {
	std::cout << "[FilteringBlock] Running on Thread ID: " << std::this_thread::get_id() << "\n";

	// Read the input from the ring buffer
	if (!_inputBuffer->read())
		return;

	// Apply SIMD filering and write to outputBuffer
	auto result = applySIMDFilter();
	_outputBuffer.push_back(result.first);
	_outputBuffer.push_back(result.second);

	_inputBuffer->increment();
}
