#include <fstream>
#include <iostream>
#include "include/pipeline.hpp"

bool readConfig(std::string filename, uint8_t &threshold, float weights[9], int &time) {
	std::fstream file(filename);
	if (!file) {
		std::cerr << "Error in opening file: " << filename << "\n";
		return false;
	}

	if (!file >> threshold) {
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

	return true;
}

int main() {
	int time;
	float weights[9];
	uint8_t threshold;
	if (!readConfig("config.txt", threshold, weights, time))
		return 1;

	Pipeline pipeline(threshold, weights, 10);


#ifdef _DEBUG
	pipeline.start();
	std::cout << "Running in _DEBUG mode \n";
	std::this_thread::sleep_for(std::chrono::seconds(time));
	pipeline.stop();
#else
	std::cout << "Running in Release mode\n";
	pipeline.start();
	while (pipeline.should_run());
	pipeline.stop();
#endif

	return 0;
}
