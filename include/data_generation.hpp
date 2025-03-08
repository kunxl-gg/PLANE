#ifndef DATA_GENERATION_BLOCK_H
#define DATA_GENERATION_BLOCK_H

#include "include/iprocess_block.hpp"
#include "include/ring_buffer.hpp"

class DataGenerationBlock : public IProcessBlock {
public:
	DataGenerationBlock(RingBuffer &buffer);
	~DataGenerationBlock();

	void readCSV();
	void generateRandomNumbers();

	void execute();
private:
	RingBuffer *_buffer;
};

#endif // DATA_GENERATION_BLOCK_H
