#include <thread>

#include "include/data_generation_block.hpp"
#include "include/debug.hpp"
#include "include/filtering_block.hpp"
#include "include/labelling_block.hpp"
#include "include/tracing_block.hpp"
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

void Pipeline::init(const PipelineConfig &config) {
	info("Initialising the Pipeline...");

	Queue *rawDataQueue = new Queue(1024);
	Queue *filteredDataQueue = new Queue(1024);
	Queue *labelledDataQueue = new Queue(1024);

	addQueue(rawDataQueue);
	addQueue(filteredDataQueue);
	addQueue(labelledDataQueue);

	DataGenerationBlock *dataBlock = new DataGenerationBlock(
		config._csvPath,
		nullptr,
		rawDataQueue,
		config._numColumns
	);

	FilteringBlock *filteringBlock = new FilteringBlock(
		config._threshold,
		config._weights,
		rawDataQueue,
		filteredDataQueue
	);

	LabellingBlock *labellingBlock = new LabellingBlock(
		filteredDataQueue,
		labelledDataQueue,
		config._numColumns
	);

	addBlock(dataBlock);
	addBlock(filteringBlock);
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

void Pipeline::start(unsigned time) {
	_running.store(true, std::memory_order_release);
	for (IProcessBlock *block: _blocks) {
		_threads.emplace_back(&Pipeline::execute, this, block);
	}

#ifdef _DEBUG
	// Keep this thread alive for `time` milliseconds
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
#else
	debug("_RELEASE mode Placeholder: Add Release logic here.");
#endif
}

void Pipeline::execute(IProcessBlock *block) {
	while (_running.load(std::memory_order_acquire)) {
		block->execute();
	}
}

