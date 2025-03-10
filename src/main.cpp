#include "include/pipeline.hpp"

int main() {
	float weights[9] = { 1.0, 0.5, -1.0, 0.5, 0, -0.5, -1.0, -0.5, 1.0 };
	Pipeline pipeline(128, weights, 1024);

	pipeline.start();

	std::this_thread::sleep_for(std::chrono::seconds(200));

	pipeline.stop();

	return 0;
}
