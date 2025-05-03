#include <stddef.h>
#include <algorithm>

#include "include/debug.hpp"
#include "include/lock_free_queue.hpp"

template<typename T>
LockFreeQueue<T>::LockFreeQueue(const size_t capacity) {
	if (_capacity == 0) {
		error("Capacity must be > 0");
		return;
	}

	_capacity = capacity;
	_buffer = new T[capacity];
}

template<typename T>
LockFreeQueue<T>::~LockFreeQueue<T>() {
	size_t head = _head.load(std::memory_order_acquire);
	size_t tail = _tail.load(std::memory_order_release);

	if (head != tail) {
		_buffer[head].~T();
		head++;
	}

	delete _buffer;
}

template<typename T>
bool LockFreeQueue<T>::empty() const noexcept {
	return _head.load(std::memory_order_acquire) == _tail.load(std::memory_order_acquire);
}

template<typename T>
bool LockFreeQueue<T>::full() const noexcept {
	size_t head = _head.load(std::memory_order_acquire);
	size_t tail = _tail.load(std::memory_order_acquire);
	return (tail - head) >= _capacity;
}

template<typename T>
size_t LockFreeQueue<T>::normalise(const size_t &ptr) const noexcept {
	return ptr < _capacity ? ptr : ptr - _capacity;
}

template<typename T>
bool enqueue(const T &item) noexcept {
	return enqueueImp(item);
}

template<typename T>
bool LockFreeQueue<T>::enqueue(T &&item) noexcept {
	return enqueueImp(std::move(item));
}

template<typename T>
bool LockFreeQueue<T>::try_dequeue(T &out) noexcept {
	size_t head = _head.load(std::memory_order_relaxed);
	size_t tail = _tail.load(std::memory_order_relaxed);

	if (head == tail) return false;

	T *ptr = &_buffer[head];
	out = std::move(*ptr);
	_head.store(head + 1, std::memory_order_relaxed);

	ptr->~T();
	return true;
}

template<typename T>
template<typename U>
bool LockFreeQueue<T>::enqueueImpl(U&& item) noexcept {
	size_t tail = _tail.load(std::memory_order_relaxed);
	size_t head = _head.load(std::memory_order_acquire);
	if ((tail - head) >= _capacity) {
		return false;
	}
	void* slot = static_cast<void*>(&_buffer[normalise(tail)]);
	new (slot) T(std::forward<U>(item));
	_tail.store(tail + 1, std::memory_order_release);
	return true;
}

extern template class LockFreeQueue<PixelData>;
