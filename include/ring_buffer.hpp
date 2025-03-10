#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <atomic>
#include <vector>

class RingBuffer {
/**
 *
 *
 *
 */
public:
	RingBuffer() = default;
	RingBuffer(const size_t &length);
	~RingBuffer() = default;

	size_t capacity() const;
	size_t normalise(size_t ptr) noexcept;

	uint8_t at(size_t index) noexcept;
	void increment() noexcept;

	bool read() noexcept;
	bool write(const uint8_t &a, const uint8_t &b) noexcept;
private:
	alignas(64) std::atomic<size_t> _rptr;
	alignas(64) std::atomic<size_t> _wptr;
	alignas(64) std::atomic<size_t> _size;
	alignas(64) std::atomic<size_t> _free;
	alignas(64) std::vector<int> _buffer;
};

#endif  // RING_BUFFER_H
