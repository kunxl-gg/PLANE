#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <atomic>
#include <cstddef>

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
    size_t capacity() const noexcept { return _capacity; }
private:
	T *_buffer; // array to store the buffer;
    const size_t _capacity;    // ring-buffer size (power-of-two)
    alignas(64) std::atomic<size_t> _head{0};     // next read position :contentReference[oaicite:0]{index=0}
    alignas(64) std::atomic<size_t> _tail{0};     // next write position :contentReference[oaicite:1]{index=1}

    // Helpers to mask indices to [0, _capacity)
    inline size_t mask(size_t idx) const noexcept { return idx & (_capacity - 1); }
};

typedef LockFreeQueue<PixelData> Queue;

#endif // THREAD_SAFE_QUEUE_H
