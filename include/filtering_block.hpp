#ifndef FILTERING_BLOCK_H
#define FILTERING_BLOCK_H

#include <vector>

#include "include/iprocess_block.hpp"
#include "include/ring_buffer.hpp"

using byte = unsigned char;

class FilteringBlock : public IProcessBlock {
public:
	FilteringBlock() = default;
	FilteringBlock(byte threshold, float weights[9], RingBuffer &buffer);
	virtual ~FilteringBlock() = default;

	void flush();
	std::pair<byte, byte> applyFilter();

	void execute() override;
private:
	byte _threshold;
	float _weights[9];

	RingBuffer *_inputBuffer;
	std::vector<uint8_t> _outputBuffer;
};

#endif // FILTERING_BLOCK_H
