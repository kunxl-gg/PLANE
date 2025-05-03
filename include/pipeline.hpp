#ifndef PIPELINE_H
#define PIPELINE_H

#include <thread>
#include <atomic>

#include "include/iprocess_block.hpp"
#include "include/lock_free_queue.hpp"

using byte = unsigned char;

class Pipeline {
public:
	Pipeline();
	~Pipeline();

	void init();
	void start();
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
