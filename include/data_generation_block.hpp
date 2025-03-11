#ifndef DATA_GENERATION_BLOCK_H
#define DATA_GENERATION_BLOCK_H

#include <fstream>
#include <string>

#include "include/iprocess_block.hpp"
#include "include/ring_buffer.hpp"

class DataGenerationBlock : public IProcessBlock {
public:
	DataGenerationBlock(RingBuffer &buffer, std::string csvPath);
	virtual ~DataGenerationBlock() = default;

	std::pair<uint8_t, uint8_t> readCSV();
	std::pair<uint8_t, uint8_t> generateRandomNumbers();

	void execute() override;
private:
	std::ifstream _file;
	std::string _csvPath;
	RingBuffer *_buffer;
};

#endif // DATA_GENERATION_BLOCK_H
