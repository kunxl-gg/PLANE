#ifndef PIPELINE_H
#define PIPELINE_H

#include <thread>
#include <atomic>

#include "include/data_generation_block.hpp"
#include "include/filtering_block.hpp"
#include "include/ring_buffer.hpp"

using byte = unsigned char;

class Pipeline {
public:
	Pipeline() = default;
	Pipeline(size_t bufferSize, std::string csvPath, byte threshold, float weights[9]);
	~Pipeline() = default;

	void start();
	void stop();
	bool should_run();

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
