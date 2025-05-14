#ifndef DATA_GENERATION_BLOCK_H
#define DATA_GENERATION_BLOCK_H

#include <fstream>
#include <string>

#include "include/iprocess_block.hpp"
#include "include/lock_free_queue.hpp"

using byte = unsigned char;

class DataGenerationBlock : public IProcessBlock {
public:
	DataGenerationBlock() = default;
	DataGenerationBlock(std::string csvPath, Queue *inputQueue, Queue *outputQueue, unsigned numColumns);
	virtual ~DataGenerationBlock() = default;

	bool hasMoreData();
	std::pair<PixelData, PixelData> readCSV();
	std::pair<PixelData, PixelData> generateRandomNumbers();

	void execute() override;
private:
	std::string _csvPath;
	std::ifstream _file;

	Queue *_inputQueue;
	Queue *_outputQueue;

	unsigned int _numColumns;
};

#endif // DATA_GENERATION_BLOCK_H
