#include <thread>

#include "include/debug.hpp"
#include "include/lock_free_queue.hpp"
#include "include/labelling_block.hpp"

LabellingBlock::LabellingBlock(Queue *inputQueue, Queue *outputQueue)
	: _inputQueue(inputQueue), _outputQueue(outputQueue) {}

LabellingBlock::~LabellingBlock() {

}

void LabellingBlock::execute() {
	debug("[LabellingBlock] Running on Thread ID: %d", std::this_thread::get_id());
}
