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

uint8_t RingBuffer::at(size_t index) noexcept {
	return _buffer[index];
}

bool RingBuffer::read() noexcept {
	size_t wptr = _wptr.load();
	size_t rptr = _rptr.load();

	if (wptr != rptr)
		return false;

	else return true;
}

void RingBuffer::increment() noexcept {
	size_t rptr = _rptr.load(std::memory_order_relaxed);
	rptr = normalise(rptr + 2);

    _rptr.store(rptr, std::memory_order_release);
}

bool RingBuffer::write(const uint8_t &a, const uint8_t &b) noexcept {
	size_t wptr = _wptr.load();
	size_t rptr = _rptr.load();

	if (wptr == rptr)
		return false;

	_buffer[wptr] = a;
	_buffer[normalise(wptr + 1)] = b;

	_wptr.store(normalise(wptr + 2));
	return true;
}
