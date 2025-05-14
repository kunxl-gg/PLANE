#ifndef TRACING_BLOCK_HPP
#define TRACING_BLOCK_HPP

#include "include/iprocess_block.hpp"
#include "include/lock_free_queue.hpp"
#include <unordered_map>
#include <mutex>

struct LabelStats {
	uint32_t size = 0;
	uint32_t top = UINT32_MAX;
	uint32_t left = UINT32_MAX;
	uint32_t bottom = 0;
	uint32_t right = 0;

	void update(uint32_t row, uint32_t col) {
		size++;
		if (row < top) top = row;
		if (row > bottom) bottom = row;
		if (col < left) left = col;
		if (col > right) right = col;
	}
};

class TracingBlock : public IProcessBlock {
public:
	TracingBlock(Queue* inputQueue, Queue* outputQueue);
	~TracingBlock();

	virtual void execute() override;

private:
	Queue* _inputQueue;
	Queue* _outputQueue;

	std::unordered_map<uint16_t, LabelStats> _labelStats;
	std::unordered_map<uint16_t, uint16_t> _labelParent;

	std::mutex _mutex;

	uint16_t find(uint16_t label);
	void merge(uint16_t fromLabel, uint16_t toLabel);
	void recycleLabel(uint16_t label);
	void outputFinalStats(uint16_t label, const LabelStats& stats);
};

#endif // TRACING_BLOCK_HPP
