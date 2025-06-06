#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <stdint.h>
#include <string>
#include <unordered_map>

enum DebugLevels {
	kDebugQuant = 1,
	kDebugLog,
	kDebugThread,
};

struct DebugChannel {
	DebugChannel() : _channel(0) {}
	DebugChannel(uint32_t c, std::string name, std::string desc)
		: _name(name), _description(desc), _channel(c) {}

	std::string _name;
	std::string _description;
	uint32_t _channel;
};

#define DEBUG_CHANNEL_END {0, NULL, NULL}

class DebugManager {
public:
	static DebugManager &instance() {
		static DebugManager instance;
		return instance;
	}

	void removeDebugChannel(uint32_t channel);
	void addDebugChannels(const DebugChannel *channels);
	void addDebugChannel(uint32_t channel, std::string name, std::string desc);

	bool isDebugChannelEnabled(uint32_t debugChannel);
	bool enableDebugChannel(const uint32_t &debugChannel);
	bool enableDebugChannel(const std::string &debugChannel);
	bool disableDebugChannel(const uint32_t &debugChannel);
	bool disableDebugChannel(const std::string &debugChannel);
private:
	std::unordered_map<std::string, DebugChannel> _debugChannels;
	std::unordered_map<uint32_t, bool> _debugChannelsEnabled;
};

extern "C" int glevel;

#endif // DEBUG_MANAGER_H
