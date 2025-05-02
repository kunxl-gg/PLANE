#include <thread>

#include "include/data_generation_block.hpp"
#include "include/debug.hpp"
#include "include/filtering_block.hpp"
#include "include/labelling_block.hpp"
#include "include/pipeline.hpp"

Pipeline::Pipeline() : _running(false) {}

Pipeline::~Pipeline() {
	for (auto block: _blocks) {
		delete block;
	}
}

void Pipeline::init() {
	info("Initialising the Pipeline...");

	DataGenerationBlock *dataBlock = new DataGenerationBlock();
	FilteringBlock *filterBlock = new FilteringBlock();
	LabellingBlock *labellingBlock = new LabellingBlock();

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

void Pipeline::start() {
	_running = true;
	for (IProcessBlock *block: _blocks) {
		_threads.emplace_back(&Pipeline::execute, this, block);
	}

#ifdef _DEBUG
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
#else
	debug("_RELEASE mode Placeholder: Add Release logic here.");
#endif
}

void Pipeline::execute(IProcessBlock *block) {
	while (_running.load(std::memory_order_relaxed)) {
		block->execute();
	}
}

