#include <immintrin.h>

#include "include/filtering_block.hpp"
#include "include/ring_buffer.hpp"

FilteringBlock::FilteringBlock(uint8_t threshold, float weights[9], RingBuffer &buffer) {
	_inputBuffer = &buffer;
	_threshold = threshold;

	for (int i = 0; i < 9; i++)
		_weights[i] = weights[i];
}

uint8_t FilteringBlock::applySIMDFilter(uint8_t input[9]) {
	// Load weights into AVX register
	__m256 weights = _mm256_loadu_ps(_weights);

	// Load 9 uint8_t values into a 256-bit register (converted to float)
	__m128i input_vec = _mm_loadu_si128(reinterpret_cast<const __m128i*>(input));
	__m256i input_16 = _mm256_cvtepu8_epi32(input_vec);  // Convert uint8_t → int32
	__m256 input_f32 = _mm256_cvtepi32_ps(input_16);  // Convert int32 → float

	// Multiply input with weights
	__m256 result = _mm256_mul_ps(input_f32, weights);

	// Sum the results
	__m256 sum1 = _mm256_hadd_ps(result, result);
	__m256 sum2 = _mm256_hadd_ps(sum1, sum1);
	float final_value = _mm_cvtss_f32(_mm256_castps256_ps128(sum2));

	return final_value > _threshold ? 255 : 0;
}

void FilteringBlock::execute() {
	// Read the input from the ring buffer
	uint8_t input[10];
	if (!_inputBuffer->read()) return;

	// Apply SIMD filering and write to outputBuffer
	auto result = applySIMDFilter(input);
	_outputBuffer.push_back(result);
}
