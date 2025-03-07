#include <cstddef>
#include <cstdint>
#include <atomic>
#include <vector>

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

class RingBuffer {
/**
 *
 *
 *
 */
public:
	// Constructors and Destructors
	RingBuffer() = default;
	RingBuffer(const size_t &length);
	~RingBuffer() = default;

	size_t capacity() const;
	size_t normalise(size_t ptr) noexcept;

	void read() noexcept;
	bool write(const uint8_t &a, const uint8_t &b) noexcept;
protected:
	size_t aquire_read_block();
	void copy_read_block();
	void release_read_block();

	size_t aquire_write_block();
	void copy_write_block();
	void release_write_block();
private:
	alignas(64) std::atomic<size_t> _rptr;
	alignas(64) std::atomic<size_t> _wptr;
	alignas(64) std::atomic<size_t> _size;
	alignas(64) std::atomic<size_t> _free;
	alignas(64) std::vector<uint8_t> _buffer;
};

#endif  // RING_BUFFER_H
