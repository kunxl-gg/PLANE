#include "include/ring_buffer.hpp"

RingBuffer::RingBuffer(const size_t &length) {
	_buffer.resize(length, 0);
	_rptr = 0;
	_wptr = 0;
	_size = 0;
	_free = 0;
}

size_t RingBuffer::capacity() const {
	return _buffer.size();
}

size_t RingBuffer::normalise(size_t ptr) noexcept {
	return ptr < capacity() ? ptr : ptr - capacity();
}

bool RingBuffer::read() noexcept {
	size_t r = _rptr.load();
	size_t w = _wptr.load();

	if (w != r)
		return false;

	else return true;
}

bool RingBuffer::write(const uint8_t &a, const uint8_t &b) noexcept {
	size_t w = _wptr.load();
	size_t r = _rptr.load();

	if (w == r)
		return false;

	_buffer[w] = a;
	_buffer[normalise(w + 1)] = b;
	_wptr.store(normalise(w + 2));
	return true;
}
