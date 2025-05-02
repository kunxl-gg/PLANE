#ifndef PIPELINE_H
#define PIPELINE_H

#include <thread>
#include <atomic>

#include "include/iprocess_block.hpp"

using byte = unsigned char;

class Pipeline {
public:
	Pipeline();
	~Pipeline();

	void run();
	void start();
	void stop();
	bool should_run();

	void addBlock(IProcessBlock *block);
	void execute(IProcessBlock *block);
private:
	std::atomic<bool> _running;

	std::vector<std::thread> _threads;
	std::vector<IProcessBlock *> _blocks;
private:
	void runDataGeneration();
	void runFiltering();
};

#endif // PIPELINE_H
