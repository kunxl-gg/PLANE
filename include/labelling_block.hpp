#ifndef LABELLING_BLOCK_H
#define LABELLING_BLOCK_H

#include "include/iprocess_block.hpp"
#include "include/lock_free_queue.hpp"

class LabellingBlock : public IProcessBlock {
public:
	LabellingBlock(Queue *inputQueue, Queue *outputQueue);
	~LabellingBlock();

	virtual void execute() override;
private:
	Queue *_inputQueue;
	Queue *_outputQueue;
};

#endif // LABELLING_BLOCK_H
