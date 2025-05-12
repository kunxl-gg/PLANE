#ifndef LOCK_FREE_QUEUE_HPP
#define LOCK_FREE_QUEUE_HPP

#include <__thread/id.h>
#include <atomic>
#include <cstddef>
#include <cstdio>
#include <utility>
#include <cassert>

struct PixelData {
	uint32_t _row;
	uint32_t _col;
	uint32_t _val;

	PixelData()
		: _row(0), _col(0), _val(0) {}

	PixelData(uint32_t row, uint32_t col, uint32_t val)
		: _row(row), _col(col), _val(val) {}
};

template<typename T>
class LockFreeQueue {
public:
	explicit LockFreeQueue(size_t capacity)
		:	_buffer(new T[capacity]), _capacity(capacity) {
		assert(_capacity > 0 && "Capacity must be > 0");
	}

	~LockFreeQueue() {
		delete[] _buffer;
	}

	LockFreeQueue(const LockFreeQueue&) = delete;
	LockFreeQueue& operator=(const LockFreeQueue&) = delete;

	bool enqueue(const T& item) noexcept {
		return enqueueImpl(item);
	}

	bool enqueue(T&& item) noexcept {
		return enqueueImpl(std::move(item));
	}

	bool try_dequeue(T& out) noexcept {
		size_t head = _head.load(std::memory_order_relaxed);
		size_t tail = _tail.load(std::memory_order_acquire);

		if (head == tail) return false;

		size_t index = normalise(head);
		T* ptr = &_buffer[index];
		out = std::move(*ptr);

		ptr->~T();

		_head.store(head + 1, std::memory_order_release);
		return true;
	}

	bool empty() const noexcept {
		return _head.load(std::memory_order_acquire) == _tail.load(std::memory_order_acquire);
	}

	bool full() const noexcept {
		size_t head = _head.load(std::memory_order_acquire);
		size_t tail = _tail.load(std::memory_order_acquire);
		return (tail - head) >= _capacity;
	}

	size_t capacity() const noexcept { return _capacity; }

	void print(std::__thread_id id) const noexcept {
		size_t head = _head.load(std::memory_order_relaxed);
		size_t tail = _tail.load(std::memory_order_relaxed);

		head = normalise(head);
		tail = normalise(tail);

		printf("Buffer State %d", id);
		for (size_t index = head; index < tail; index++) {
			printf("%d ", _buffer[index]._val);
		}
		printf("\n");
	}

private:
	T* _buffer;
	size_t _capacity;
	alignas(64) std::atomic<size_t> _head{0};
	alignas(64) std::atomic<size_t> _tail{0};

	size_t normalise(size_t ptr) const noexcept {
		return ptr % _capacity;
	}

	template<typename U>
	bool enqueueImpl(U&& item) noexcept {
		size_t tail = _tail.load(std::memory_order_relaxed);
		size_t head = _head.load(std::memory_order_acquire);

		if ((tail - head) >= _capacity)
			return false;

		size_t index = normalise(tail);
		void* slot = static_cast<void*>(&_buffer[index]);
		new (slot) T(std::forward<U>(item));

		_tail.store(tail + 1, std::memory_order_release);
		return true;
	}
};

// Type alias
using Queue = LockFreeQueue<PixelData>;

#endif // LOCK_FREE_QUEUE_HPP
