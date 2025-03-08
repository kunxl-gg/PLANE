#ifndef FILTERING_BLOCK_H
#define FILTERING_BLOCK_H

#include <cstdint>

#include "include/iprocess_block.hpp"
#include "include/ring_buffer.hpp"

class FilteringBlock : public IProcessBlock {
public:
	FilteringBlock(uint8_t threshold, float weights[9], RingBuffer &buffer);
	~FilteringBlock();

	uint8_t applySIMDFilter(uint8_t input[9]);

	void execute() override;
private:
	uint8_t _threshold;
	float _weights[9];

	RingBuffer *_inputBuffer;
	std::vector<uint8_t> _outputBuffer;
};

#endif // FILTERING_BLOCK_H
