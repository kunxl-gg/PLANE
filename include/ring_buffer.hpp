#include <cstdint>

class RingBuffer {
public:
	/**
	 * Constructor for the RingBuffer class
	 */
	RingBuffer();

	/**
	 * Destructor for the RingBuffer class
	 */
	~RingBuffer();

	/**
	 * Deleting the Copy Constructor of the RingBuffer class
	 */
	RingBuffer(const RingBuffer &ringBuffer) = delete;
private:
	uint8_t _capacity = 10;
};
