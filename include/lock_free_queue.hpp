#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <atomic>

struct PixelData {
	uint32_t _row;
	uint32_t _col;
	uint32_t _val;
};

template<typename T>
class LockFreeQueue {
public:
	explicit LockFreeQueue(size_t capacity);
	~LockFreeQueue();

	// Disable copying
	LockFreeQueue(const LockFreeQueue&) = delete;
	LockFreeQueue& operator=(const LockFreeQueue&) = delete;

	bool enqueue(const T& item) noexcept;
	bool enqueue(T&& item) noexcept;
	bool try_dequeue(T& out) noexcept;

	bool empty() const noexcept;
	bool full() const noexcept;
	size_t normalise(const size_t &ptr) const noexcept;
	size_t capacity() const noexcept { return _capacity; }

	template<typename U>
	bool enqueueImpl(U &&item) noexcept;
private:
	T *_buffer;
	size_t _capacity;
	alignas(64) std::atomic<size_t> _head{0};
	alignas(64) std::atomic<size_t> _tail{0};
};

typedef LockFreeQueue<PixelData> Queue;

#endif // THREAD_SAFE_QUEUE_H
