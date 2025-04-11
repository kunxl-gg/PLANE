#include <atomic>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <sys/resource.h>

#include "include/ring_buffer.hpp"

RingBuffer::RingBuffer(const size_t &length) {
	_buffer.resize(length, 0);
	_rptr.store(0, std::memory_order_relaxed);
	_wptr.store(0, std::memory_order_relaxed);
	_size.store(0, std::memory_order_relaxed);
}

RingBuffer& RingBuffer::operator = (const RingBuffer& other) {
	if (this == &other)
		return *this;

	_rptr.store(other._rptr);
	_wptr.store(other._wptr);
	_size.store(other._size);

	_buffer = other._buffer;

	return *this;
}

size_t RingBuffer::capacity() const {
	return _buffer.size();
}

size_t RingBuffer::normalise(size_t ptr) const noexcept {
	return ptr < capacity() ? ptr : ptr - capacity();
}

uint8_t RingBuffer::at(size_t index) noexcept {
	return _buffer[index];
}

bool RingBuffer::write(const byte &a, const byte &b) noexcept {
	size_t wptr = _wptr.load();
	size_t rptr = _rptr.load();
	size_t size = _size.load();

	if (wptr == rptr && size == capacity())
		return false;

	_buffer[wptr] = a;
	_buffer[normalise(wptr + 1)] = b;

	_wptr.store(normalise(wptr + 2), std::memory_order_release);

	size_t currentSize = _size.load(std::memory_order_relaxed);
	if (currentSize < capacity())
		_size.store(currentSize + 2, std::memory_order_release);

	return true;
}

bool RingBuffer::read() noexcept {
	size_t wptr = _wptr.load();
	size_t rptr = _rptr.load();
	size_t size = _size.load();

	if (wptr == rptr && size == capacity())
		return true;

	else return false;
}

void RingBuffer::increment() noexcept {
	size_t rptr = _rptr.load(std::memory_order_relaxed);
	rptr = normalise(rptr + 2);
    _rptr.store(rptr, std::memory_order_release);
}

size_t RingBuffer::getReadIndex() noexcept {
	return _rptr;
}

void RingBuffer::print() noexcept {
	for (int i = 0; i < 10; i++) {
		printf("%d ", _buffer[i]);
	}

	printf("\n");
}
