#include <thread>

#include "include/data_generation_block.hpp"
#include "include/debug.hpp"
#include "include/filtering_block.hpp"
#include "include/labelling_block.hpp"
#include "include/lock_free_queue.hpp"
#include "include/pipeline.hpp"

Pipeline::Pipeline() : _running(false) {}

Pipeline::~Pipeline() {
	for (auto block: _blocks) {
		delete block;
	}

	for (auto queue: _queues) {
		delete queue;
	}
}

void Pipeline::init() {
	info("Initialising the Pipeline...");

	Queue *q1 = new Queue(1024);
	Queue *q2 = new Queue(1024);

	addQueue(q1);
	addQueue(q2);

	DataGenerationBlock *dataBlock = new DataGenerationBlock();
	FilteringBlock *filterBlock = new FilteringBlock();
	LabellingBlock *labellingBlock = new LabellingBlock(q1, q2);

	addBlock(dataBlock);
	addBlock(filterBlock);
	addBlock(labellingBlock);
}

void Pipeline::stop() {
	info("Stopping the Pipeline...");
	_running = false;

	for (std::thread &thread: _threads) {
		if (thread.joinable()) thread.join();
	}
	_threads.clear();
}

void Pipeline::addBlock(IProcessBlock *block) {
	_blocks.push_back(block);
	return;
}

void Pipeline::addQueue(Queue *queue) {
	_queues.push_back(queue);
	return;
}

void Pipeline::start() {
	_running.store(true, std::memory_order_release);
	for (IProcessBlock *block: _blocks) {
		_threads.emplace_back(&Pipeline::execute, this, block);
	}

#ifdef _DEBUG
#else
	debug("_RELEASE mode Placeholder: Add Release logic here.");
#endif
}

void Pipeline::execute(IProcessBlock *block) {
	while (_running.load(std::memory_order_acquire)) {
		block->execute();
	}
}

