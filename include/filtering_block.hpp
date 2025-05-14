#ifndef FILTERING_BLOCK_H
#define FILTERING_BLOCK_H

#include <vector>

#include "include/iprocess_block.hpp"
#include "include/lock_free_queue.hpp"
#include "include/ring_buffer.hpp"

using byte = unsigned char;

class FilteringBlock : public IProcessBlock {
public:
	FilteringBlock(byte threshold, const float weights[9], Queue *inputQueue, Queue *outputQueue);
	virtual ~FilteringBlock() = default;

	void flush();
	std::pair<PixelData, PixelData> applyFilter();

	void execute() override;
private:
	byte _threshold;
	float _weights[9];

	Queue *_inputQueue;
	Queue *_outputQueue;
};

#endif // FILTERING_BLOCK_H
