#include "include/tracing_block.hpp"
#include <iostream>

TracingBlock::TracingBlock(Queue* inputQueue, Queue* outputQueue)
	: _inputQueue(inputQueue), _outputQueue(outputQueue) {}

TracingBlock::~TracingBlock() {}

uint16_t TracingBlock::find(uint16_t label) {
	if (_labelParent[label] != label) {
		_labelParent[label] = find(_labelParent[label]);
	}
	return _labelParent[label];
}

void TracingBlock::merge(uint16_t fromLabel, uint16_t toLabel) {
	uint16_t rootFrom = find(fromLabel);
	uint16_t rootTo = find(toLabel);

	if (rootFrom == rootTo) return;

	// Merge sizes and bounding boxes
	auto& statsFrom = _labelStats[rootFrom];
	auto& statsTo = _labelStats[rootTo];

	statsTo.size += statsFrom.size;
	statsTo.top = std::min(statsTo.top, statsFrom.top);
	statsTo.bottom = std::max(statsTo.bottom, statsFrom.bottom);
	statsTo.left = std::min(statsTo.left, statsFrom.left);
	statsTo.right = std::max(statsTo.right, statsFrom.right);

	// Point rootFrom to rootTo
	_labelParent[rootFrom] = rootTo;

	// Clear old label info
	_labelStats.erase(rootFrom);
}

void TracingBlock::recycleLabel(uint16_t label) {
	_labelStats.erase(label);
	_labelParent.erase(label);

	// Inform the labelling block (optional: enqueue a special PixelData)
	_outputQueue->enqueue(PixelData(0xFFFFFFFF, 0xFFFFFFFF, label));
}

void TracingBlock::outputFinalStats(uint16_t label, const LabelStats& stats) {
	std::cout << "Label " << label << ": size=" << stats.size
	          << ", box=(" << stats.top << "," << stats.left
	          << ") to (" << stats.bottom << "," << stats.right << ")\n";
}

void TracingBlock::execute() {
	PixelData p;
	while (!_inputQueue->empty()) {
		p = _inputQueue->at(_inputQueue->head());

		// dequeue
		if (!_inputQueue->try_dequeue())
			break;

		if (p._row == 0xFFFFFFFF && p._col == 0xFFFFFFFF) {
			// End signal for a label
			uint16_t label = static_cast<uint16_t>(p._val);
			uint16_t root = find(label);
			if (_labelStats.find(root) != _labelStats.end()) {
				outputFinalStats(root, _labelStats[root]);
				recycleLabel(root);
			}
			continue;
		}

		uint16_t label = static_cast<uint16_t>(p._val);
		uint16_t root = find(label);

		if (_labelStats.find(root) == _labelStats.end()) {
			_labelStats[root] = LabelStats();
			_labelParent[root] = root;
		}

		_labelStats[root].update(p._row, p._col);
	}
}
