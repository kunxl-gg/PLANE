#include "include/labelling_block.hpp"
#include <iostream>
#include <algorithm>

LabellingBlock::LabellingBlock(Queue *inputQueue, Queue *outputQueue, int width)
	: _inputQueue(inputQueue), _outputQueue(outputQueue),
	  _width(width), _currentRow(0), _currentCol(0), _nextLabel(1),
	  _parent(2 * width), _rank(2 * width, 0)
{
	// Initialize parent to self
	for (int i = 0; i < 2 * width; ++i) {
		_parent[i] = i;
	}
}

LabellingBlock::~LabellingBlock() {}

void LabellingBlock::execute() {
	if (_inputQueue->empty()) return;

	size_t head = _inputQueue->head();
	PixelData p = _inputQueue->at(head);
	while (!_inputQueue->try_dequeue());

	if (p._row != _currentRow || p._col != _currentCol) {
		std::cerr << "Unexpected pixel order. Expected ("
		          << _currentRow << "," << _currentCol << ") but got ("
		          << p._row << "," << p._col << ")\n";
		return;
	}

	processPixel(p);

	// Output to next stage
	_outputQueue->enqueue(p);

	// Move to next column or new _row
	_currentCol++;
	if (_currentCol >= _width) {
		_currentCol = 0;
		_currentRow++;
		resetRow();
	}
}

void LabellingBlock::resetRow() {
	// Union-find arrays already large enough, just reset parents for the new _row
	for (int i = 0; i < _width; ++i) {
		// move next _row's parent base to front
		_parent[i] = _parent[i + _width];
		_rank[i] = _rank[i + _width];
	}
	// clear new _row slots
	for (int i = 0; i < _width; ++i) {
		_parent[i + _width] = i + _width;
		_rank[i + _width] = 0;
	}
}

uint16_t LabellingBlock::find(uint16_t x) {
	if (_parent[x] != x) {
		_parent[x] = find(_parent[x]);
	}
	return _parent[x];
}

void LabellingBlock::unite(uint16_t x, uint16_t y) {
	x = find(x);
	y = find(y);
	if (x == y) return;

	if (_rank[x] < _rank[y]) std::swap(x, y);
	_parent[y] = x;
	if (_rank[x] == _rank[y]) _rank[x]++;
}

void LabellingBlock::processPixel(const PixelData& p_in) {
	PixelData p = p_in; // Copy to modify
	uint16_t label = 0;

	if (!p._val) {
		_outputQueue->enqueue(p);
		return;
	}

	int curIdx = _currentCol + _width;      // Current _row
	int leftIdx = (_currentCol > 0) ? (_currentCol - 1 + _width) : -1;
	int topIdx = _currentCol;               // Previous _row

	bool leftConnected = false, topConnected = false;
	uint16_t leftLabel = 0, topLabel = 0;

	if (_currentCol > 0) {
		leftLabel = _parent[leftIdx];
		leftConnected = leftLabel != 0 && p._val;
	}
	topLabel = _parent[topIdx];
	topConnected = topLabel != 0 && p._val;

	if (leftConnected && topConnected) {
		if (find(leftLabel) != find(topLabel)) {
			unite(leftLabel, topLabel);
		}
		label = find(leftLabel);
	} else if (leftConnected) {
		label = find(leftLabel);
	} else if (topConnected) {
		label = find(topLabel);
	} else {
		label = _nextLabel++;
	}

	_parent[curIdx] = label;
	_outputQueue->enqueue(p);
}
