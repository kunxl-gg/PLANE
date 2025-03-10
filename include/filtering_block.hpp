#ifndef FILTERING_BLOCK_H
#define FILTERING_BLOCK_H

#include <cstdint>
#include <vector>

#include "include/iprocess_block.hpp"
#include "include/ring_buffer.hpp"

class FilteringBlock : public IProcessBlock {
public:
	FilteringBlock(uint8_t threshold, float weights[9], RingBuffer &buffer);
	virtual ~FilteringBlock() = default;

	std::pair<uint8_t, uint8_t> applySIMDFilter();

	void execute() override;
private:
	uint8_t _threshold;
	float _weights[9];

	RingBuffer *_inputBuffer;
	std::vector<uint8_t> _outputBuffer;
};

#endif // FILTERING_BLOCK_H
