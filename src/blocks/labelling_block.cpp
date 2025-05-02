#include <thread>

#include "include/debug.hpp"
#include "include/labelling_block.hpp"

LabellingBlock::~LabellingBlock() {

}

void LabellingBlock::execute() {
	debug("[LabellingBlock] Running on Thread ID: %d", std::this_thread::get_id());
}
