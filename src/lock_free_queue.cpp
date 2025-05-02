#include <atomic>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

template<typename T>
class LockFreeQueue {
public:
    static_assert(std::is_nothrow_copy_assignable<T>::value || std::is_nothrow_move_assignable<T>::value,
                  "T must be nothrow copy- or move-assignable");

    explicit LockFreeQueue(size_t capacity)
        : _capacity(nextPowerOfTwo(capacity)),
          _buffer(static_cast<T*>(operator new[](sizeof(T) * _capacity)))
    {
        if (_capacity == 0) {
            throw std::invalid_argument("Capacity must be > 0");
        }
        // head and tail automatically zero-initialized
    }

    ~LockFreeQueue() {
        // Destroy any remaining objects
        size_t head = _head.load(std::memory_order_relaxed);
        size_t tail = _tail.load(std::memory_order_relaxed);
        while (head != tail) {
            _buffer[mask(head)]->~T();
            ++head;
        }
        operator delete[](_buffer);
    }

    // No copying
    LockFreeQueue(const LockFreeQueue&) = delete;
    LockFreeQueue& operator=(const LockFreeQueue&) = delete;

    // Enqueue by copy or move. Returns false if full.
    bool enqueue(const T& item) noexcept {
        return enqueueImpl(item);
    }
    bool enqueue(T&& item) noexcept {
        return enqueueImpl(std::move(item));
    }

    // Dequeue. Returns false if empty.
    bool try_dequeue(T& out) noexcept {
        size_t head = _head.load(std::memory_order_relaxed);
        size_t tail = _tail.load(std::memory_order_acquire);
        if (head == tail) {
            return false; // empty
        }
        T* ptr = reinterpret_cast<T*>(&_buffer[mask(head)]);
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

private:
    size_t _capacity;
    T* _buffer;
    alignas(64) std::atomic<size_t> _head{0};
    alignas(64) std::atomic<size_t> _tail{0};

    static size_t nextPowerOfTwo(size_t v) {
        // simple bit-twiddling
        if (v == 0) return 1;
        --v;
        for (size_t shift = 1; shift < sizeof(size_t) * 8; shift <<= 1) {
            v |= v >> shift;
        }
        return v + 1;
    }

    inline size_t mask(size_t idx) const noexcept {
        return idx & (_capacity - 1);
    }

    template<typename U>
    bool enqueueImpl(U&& item) noexcept {
        size_t tail = _tail.load(std::memory_order_relaxed);
        size_t head = _head.load(std::memory_order_acquire);
        if ((tail - head) >= _capacity) {
            return false; // full
        }
        // placement-new into buffer slot
        void* slot = static_cast<void*>(&_buffer[mask(tail)]);
        new (slot) T(std::forward<U>(item));
        _tail.store(tail + 1, std::memory_order_release);
        return true;
    }
};
