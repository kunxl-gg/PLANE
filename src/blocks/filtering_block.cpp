#include <cstdint>
#include <thread>

#include "include/filtering_block.hpp"
#include "include/debug-manager.hpp"
#include "include/debug.hpp"
#include "include/ring_buffer.hpp"

FilteringBlock::FilteringBlock(byte threshold, const float weights[9],
		Queue *inputQueue, Queue *outputQueue) :
	_threshold(threshold),
	_inputQueue(inputQueue),
	_outputQueue(outputQueue) {

	std::copy(weights, weights + 9, _weights);
#ifdef _DEBUG_LOG
	std::cout << _inputBuffer << ": [FilteringBlock] buffer \n";
#endif
}

std::pair<PixelData, PixelData> FilteringBlock::applyFilter() {
	float weightedSumA = 0; float weightedSumB = 0;
	uint32_t rowA = 0; uint32_t colA = 0;
	uint32_t rowB = 0; uint32_t colB = 0;

	for (size_t i = 0; i + 1 < 10; i++) {
		weightedSumA += _weights[i] * _inputQueue->at(i)._val;
		weightedSumB += _weights[i + 1] * _inputQueue->at(i + 1)._val;

		if (i == 4) {
			rowA = _inputQueue->at(i)._row;
			rowB = _inputQueue->at(i + 1)._row;

			colA = _inputQueue->at(i)._col;
			colB = _inputQueue->at(i + 1)._col;
		}
	}

	weightedSumA = weightedSumA < _threshold ? 0 : 1;
	weightedSumB = weightedSumB < _threshold ? 0 : 1;

	PixelData pixelA = PixelData(rowA, colA, weightedSumA);
	PixelData pixelB = PixelData(rowB, colB, weightedSumB);
	return std::make_pair(pixelA, pixelB);
}

void FilteringBlock::execute() {
	debugC(9, kDebugThread, "[FilteringBlock] Running on Thread ID: %d", std::this_thread::get_id());

	auto start = std::chrono::high_resolution_clock::now();

	uint32_t head = _inputQueue->head();
	uint32_t tail = _inputQueue->tail();

	if (tail - head + 1 < 9)
		return;

	auto result = applyFilter();
	_outputQueue->enqueue(result.first);
	_outputQueue->enqueue(result.second);

	_inputQueue->try_dequeue();
	_inputQueue->try_dequeue();

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	// Ensure execution time is at least 500 ns
	if (elapsed.count() < 500) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(500 - elapsed.count()));
	}
}
