#include <string>

#include "include/argparse.hpp"
#include "include/debug.hpp"
#include "include/pipeline.hpp"

int main(int argv, const char *argc[]) {
	float weights[9];
	std::string csvPath;
	unsigned numColumns = 0;
	unsigned time = 0;
	byte threshold = 0;

	// Read Config file.
	if (!readConfig("config.txt", csvPath, threshold, weights, time, numColumns))
		return 1;

	// Add debugFlags to the debug Manager.
	DebugManager::instance().addDebugChannels(debugFlagList);

	// Parse Command line arguments.
	parseCommandLine(argv, argc);

	// Initialise Pipeline Config
	PipelineConfig config(time, csvPath, numColumns, weights, threshold);
	config.print();

	// Initialise the Pipeline.
	Pipeline pipeline = Pipeline();

#ifdef _DEBUG
	info("Running in _DEBUG mode");
	pipeline.init(config);
	pipeline.start();
	pipeline.stop();
#else
	info("Running in _RELEASE mode");
	pipeline.init(config);
	pipeline.start();
	pipeline.stop();
#endif

	return 0;
}
