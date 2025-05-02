#include <cstdint>
#include <fstream>
#include <iostream>
#include <thread>

#include "include/filtering_block.hpp"
#include "include/debug.hpp"
#include "include/ring_buffer.hpp"

FilteringBlock::FilteringBlock(byte threshold, float weights[9], RingBuffer &buffer) {
	_inputBuffer = &buffer;
	_threshold = threshold;

	for (int i = 0; i < 9; i++)
		_weights[i] = weights[i];

#ifdef _DEBUG_LOG
	std::cout << _inputBuffer << ": [FilteringBlock] buffer \n";
#endif
}

std::pair<uint8_t, uint8_t> FilteringBlock::applyFilter() {
	float a = 0; float b = 0;

	for (size_t i = 0; i + 1 < 9; i++) {
		a += _weights[i] * _inputBuffer->at(i);
		b += _weights[i + 1] * _inputBuffer->at(i + 1);
	}

	return std::make_pair(a, b);
}

void FilteringBlock::flush() {
	std::fstream file("output.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return;
	}

	for (size_t i = 0; i < _outputBuffer.size(); i += 10) {
		for (int j = 0; j < 10; j++) {
			if (i + j >= _outputBuffer.size()) break;
			unsigned value = _outputBuffer[i + j] >= _threshold ? 1 : 0;
			file << value << " ";
		}
		file << "\n";
	}

	file.close();
}

void FilteringBlock::execute() {
	debug("[FilteringBlock] Running on Thread ID: %d", std::this_thread::get_id());
}
