#include "include/data_generation_block.hpp"
#include "include/debug.hpp"
#include "include/filtering_block.hpp"
#include "include/pipeline.hpp"

Pipeline::Pipeline() : _running(false) {}

Pipeline::~Pipeline() {
	for (auto block: _blocks) {
		delete block;
	}
}

void Pipeline::start() {
	info("Starting Pipeline...");

	DataGenerationBlock *dataBlock = new DataGenerationBlock();
	FilteringBlock *filterBlock = new FilteringBlock();

	addBlock(dataBlock);
	addBlock(filterBlock);
}

void Pipeline::stop() {
	info("Stopping Pipeline...");
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

void Pipeline::run() {
	_running = true;

#ifdef _DEBUG
	for (IProcessBlock *block: _blocks) {
		_threads.emplace_back(&Pipeline::execute, this, block);
	}
#else
	debug("_RELEASE mode Placeholder: Add Release logic here.");
#endif
}

void Pipeline::execute(IProcessBlock *block) {
	while (_running.load(std::memory_order_relaxed)) {
		block->execute();
	}
}

