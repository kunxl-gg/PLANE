#ifndef PIPELINE_H
#define PIPELINE_H

#include <thread>
#include <atomic>

#include "include/data_generation.hpp"
#include "include/filtering_block.hpp"
#include "include/ring_buffer.hpp"

class Pipeline {
public:
	Pipeline(uint8_t threshold, float weights[9], size_t bufferSize);
	~Pipeline();

	void start();
	void stop();

private:
	std::atomic<bool> _running;
	std::thread _dataThread;
	std::thread _filterThread;

	RingBuffer _buffer;
	DataGenerationBlock _dataBlock;
	FilteringBlock _filterBlock;

private:
	void runDataGeneration();
	void runFiltering();
};

#endif // PIPELINE_H
