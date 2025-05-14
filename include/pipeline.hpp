#ifndef PIPELINE_H
#define PIPELINE_H

#include <algorithm>
#include <thread>
#include <atomic>

#include "include/debug.hpp"
#include "include/iprocess_block.hpp"
#include "include/lock_free_queue.hpp"

using byte = unsigned char;

class PipelineConfig {
public:
	unsigned int _time;

	// Data Generation Block
	std::string _csvPath;
	unsigned int _numColumns;

	// Filtering Block
	byte _threshold;
	float _weights[9];

	PipelineConfig(unsigned time, std::string csvPath, unsigned numColumns,
			float weights[9], byte threshold)
		: _time(time), _csvPath(std::move(csvPath)), _numColumns(numColumns), _threshold(threshold) {
			std::copy(weights, weights + 10, _weights);
		}

	void print() {
		info("CSV Path       : %s", _csvPath.c_str());
		info("Threshold      : %u", _threshold);
		info("Time           : %u ms", _time);
		info("No. of Columns : %zu", _numColumns);

		std::ostringstream oss;
		oss << "Weights        : [";
		for (int i = 0; i < 9; ++i) {
			oss << _weights[i];
			if (i + 1 < 9)
				oss << ", ";
		}
		oss << "]";
		info("%s", oss.str().c_str());

	}
};

class Pipeline {
public:
	Pipeline();
	~Pipeline();

	void init(const PipelineConfig &config);
	void start(unsigned time);
	void stop();
	bool should_run();

	void addBlock(IProcessBlock *block);
	void execute(IProcessBlock *block);

	void addQueue(Queue *queue);
private:
	std::atomic<bool> _running;

	std::vector<IProcessBlock *> _blocks;
	std::vector<Queue *> _queues;
	std::vector<std::thread> _threads;
private:
	void runDataGeneration();
	void runFiltering();
};

#endif // PIPELINE_H
