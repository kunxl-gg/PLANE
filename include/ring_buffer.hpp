#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <atomic>
#include <vector>

using byte = unsigned char;

class RingBuffer {
/**
 * @class RingBuffer
 * @brief A lock-free, thread-safe circular buffer for concurrent readers and writers.
 *
 * The RingBuffer class implements a fixed-size circular (ring) buffer designed for
 * concurrent data access. It is optimized for scenarios where multiple threads
 * perform read and write operations concurrently without the overhead of locks.
 *
 * Concurrency details:
 * - Two atomic pointers (_rptr for reading and _wptr for writing) are used to
 *   track the current read and write positions in the buffer.
 * - An atomic counter (_size) tracks the number of elements currently stored.
 * - A reserve-commit mechanism is implied: a reader checks if enough data is available,
 *   "reserves" the data and then commits the read by moving the _rptr.
 *   A writer first checks space availability, then writes data, and finally
 *   updates the _wptr.
 * - False sharing is minimized by aligning atomic members to cache line boundaries.
 *
 * Note: This implementation works on raw bytes (or POD data types). It writes and
 * reads data in pairs, so the read pointer is advanced by two positions each time.
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

	size_t getReadIndex() noexcept;
	void print() noexcept;
private:
	// To avoid False Sharing
	alignas(64) std::atomic<size_t> _rptr;
	alignas(64) std::atomic<size_t> _wptr;
	alignas(64) std::atomic<size_t> _size;
	alignas(64) std::vector<int> _buffer;
};

#endif  // RING_BUFFER_H
