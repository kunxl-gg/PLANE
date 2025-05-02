#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <fstream>
#include <iostream>
#include <string>

#include "include/debug-manager.hpp"

enum DebugLevels {
	kDebugQuant = 1,
	kDebugLog,
	kDebugThread,
};

const DebugChannel debugFlagList[] = {
	{kDebugQuant, "quant", "Quantisation debug output"},
	{kDebugLog, "log", "General debug output"},
	{kDebugThread, "thread", "Threading debug output"},
};

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

void parseCommandLine(int argv, const char *argc[]) {
	std::string debugFlags;
	int debugLevel = -1;

	if (argv == 1) return;

	for (int i = 1; i < argv; i++) {
		std::string arg = argc[i];

		if (arg.rfind("--debugflags=") == 0) {
			std::string debugflag = arg.substr(13);
			DebugManager::instance().enableDebugChannel(debugflag);
		} else if (arg.rfind("--debuglevel=") == 0) {
			std::string debuglevel = arg.substr(13);
			glevel= std::stoi(debuglevel);
		}
	}
}

#endif // ARGPARSE_H
