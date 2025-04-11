#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <atomic>
#include <vector>

using byte = unsigned char;

class RingBuffer {
/**
 *
 *
 *
 */
public:
	RingBuffer() = default;
	RingBuffer(const size_t &length);
	RingBuffer& operator = (const RingBuffer & other);
	~RingBuffer() = default;

	size_t capacity() const;
	size_t normalise(size_t ptr) const noexcept;

	uint8_t at(size_t index) noexcept;
	void increment() noexcept;

	bool read() noexcept;
	bool write(const byte &a, const byte &b) noexcept;

	void print() noexcept;
private:
	// To avoid False Sharing
	alignas(64) std::atomic<size_t> _rptr;
	alignas(64) std::atomic<size_t> _wptr;
	alignas(64) std::atomic<size_t> _size;
	alignas(64) std::vector<int> _buffer;
};

#endif  // RING_BUFFER_H
