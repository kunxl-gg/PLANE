#include <fstream>
#include <iostream>

#include "include/pipeline.hpp"

bool readConfig(std::string filename, unsigned &threshold, float weights[9], int &time, int &timePeriod) {
	std::fstream file(filename);
	if (!file) {
		std::cerr << "Error in opening file: " << filename << "\n";
		return false;
	}

	file >> threshold;
	if (file.fail()) {
		std::cerr << "Error in reading threshold\n";
		return false;
	}

	file >> time;
	if (file.fail()) {
		std::cerr << "Error in reading time\n";
		return false;
	}

	file >> timePeriod;
	if (file.fail()) {
		std::cerr << "Error in reading time period\n";
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
	int timePeriod;
	float weights[9];
	unsigned threshold;

	if (!readConfig("config.txt", threshold, weights, time, timePeriod))
		return 1;

	printf("Time: %d Threshold: %u \n", time, threshold);
	for (size_t i = 0; i < 9; i++)
		printf("%f ", weights[i]);
	printf("\n");

	Pipeline pipeline(threshold, weights, 10);


#ifdef _DEBUG
	printf("%s ", "Running in _DEBUG mode\n");
	pipeline.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
	pipeline.stop();
#else
	printf("%s ", "Running in _RELEASE mode \n");
	pipeline.start();
	while (pipeline.should_run());
	pipeline.stop();
#endif

	return 0;
}
