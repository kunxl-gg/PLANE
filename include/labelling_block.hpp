#ifndef LABELLING_BLOCK_H
#define LABELLING_BLOCK_H

#include "include/iprocess_block.hpp"
#include "include/lock_free_queue.hpp"
#include <_types/_uint16_t.h>
#include <vector>


class LabellingBlock : public IProcessBlock {
public:
	LabellingBlock(Queue *inputQueue, Queue *outputQueue, int width);
	~LabellingBlock();

	virtual void execute() override;
private:
	Queue *_inputQueue;
	Queue *_outputQueue;

	int _width;
	int _currentRow;
	int _currentCol;
	uint16_t _nextLabel;

	std::vector<uint16_t> _parent;
	std::vector<uint16_t> _rank;

	void resetRow();
	uint16_t find(uint16_t x);
	void unite(uint16_t x, uint16_t y);
	void processPixel(const PixelData& p);
};

#endif // LABELLING_BLOCK_H
