#include <fstream>
#include <iostream>
#include <string>

#include "include/debug.hpp"
#include "include/pipeline.hpp"

bool readConfig(
		std::string filename,
		std::string &csvPath,
		unsigned &threshold,
		float weights[],
		unsigned &time
	) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error in opening file: " << filename << "\n";
		return false;
	}

	if (!(file >> csvPath)) {
		std::cerr << "Error in reading csvPath \n";
		return false;
	}

	if (!(file >> threshold)) {
		std::cerr << "Error in reading threshold\n";
		return false;
	}

	if (!(file >> time)) {
		std::cerr << "Error in reading time\n";
		return false;
	}

	float value;
	for (int i = 0; i < 9; i++) {
		if (!(file >> value)) {
			std::cerr << "Error in reading weight: " << i << "\n";
			return false;
		}

		weights[i] = value;
	}

	std::cout << "Config loaded successfully:\n"
			  << "  CSV Path     : " << csvPath << "\n"
			  << "  Threshold    : " << static_cast<int>(threshold) << "\n"
			  << "  Time         : " << time << " ms\n"
			  << "  Weights      : [";

	for (int i = 0; i < 9; ++i) {
		std::cout << weights[i];
		if (i + 1 < 9)
			std::cout << ", ";
	}
	std::cout << "]\n";

	return true;
}

int main() {
	float weights[9];
	std::string csvPath;
	unsigned time = 0;
	unsigned threshold = 0;

	if (!readConfig("config.txt", csvPath, threshold, weights, time))
		return 1;

	// Initialise the Pipeline.
	Pipeline pipeline(10, csvPath, threshold, weights);

#ifdef _DEBUG
	info("Running in _DEBUG mode");
	pipeline.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
	pipeline.stop();
#else
	info("Running in _RELEASE mode");
	pipeline.start();
	while (pipeline.should_run());
	pipeline.stop();
#endif

	return 0;
}
