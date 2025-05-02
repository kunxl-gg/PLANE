#include <cstdint>
#include <cstdio>
#include <ctime>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "include/debug.hpp"
#include "include/debug-manager.hpp"

int glevel = -1;

void debug(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [DEBUG]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void debugN(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [DEBUG]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void debugC(int level, uint32_t debugChannel, const char *s, ...) {
	if (level > glevel || !DebugManager::instance().isDebugChannelEnabled(debugChannel))
		return;

    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [DEBUG]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);
	va_list args;
	va_start(args, s);
	vprintf(buffer, args);
	va_end(args);
}

void debugCN(int level, uint32_t debugChannel, const char *s, ...) {
	if (level > glevel || !DebugManager::instance().isDebugChannelEnabled(debugChannel))
		return;

    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [DEBUG]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);
	va_list args;
	va_start(args, s);
	vprintf(buffer, args);
	va_end(args);
}

void info(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [INFO]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void infoN(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [INFO]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void error(const char *s, ...) {
    char buffer[1024];
    std::time_t currenttime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [ERROR]", std::localtime(&currenttime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void errorN(const char *s, ...) {
    char buffer[1024];
    std::time_t currenttime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [ERROR]", std::localtime(&currenttime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void success(const char *s, ...) {
    char buffer[1024];
    std::time_t currenttime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [SUCCESS]", std::localtime(&currenttime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void successN(const char *s, ...) {
    char buffer[1024];
    std::time_t currenttime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [SUCCESS]", std::localtime(&currenttime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void warn(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [WARN]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void DebugManager::addDebugChannel(uint32_t channel, std::string name, std::string desc) {
	for (auto &debugChannel: _debugChannels) {
		if (debugChannel.second._channel == channel)
			warn("Duplicate declaration of engine debug channel '%s'", name.c_str());
	}

	_debugChannels[name] = DebugChannel(channel, name, desc);
}

void DebugManager::addDebugChannels(const DebugChannel *channels) {
	for (unsigned i = 0; channels[i]._channel != 0; i++) {
		addDebugChannel(channels[i]._channel, channels[i]._name, channels[i]._description);
	}
}

bool DebugManager::isDebugChannelEnabled(uint32_t debugChannel) {
	for (std::pair<uint32_t, bool> channel: _debugChannelsEnabled) {
		if (channel.first == debugChannel && _debugChannelsEnabled[debugChannel])
			return true;
	}

	return false;
}

bool DebugManager::enableDebugChannel(const uint32_t &debugChannel) {
	_debugChannelsEnabled[debugChannel] = true;
	return true;
}

bool DebugManager::disableDebugChannel(const uint32_t &debugChannel) {
	_debugChannelsEnabled[debugChannel] = false;
	return true;
}

bool DebugManager::enableDebugChannel(const std::string &name) {
	auto pos = _debugChannels.find(name);

	if (pos != _debugChannels.end()) {
		_debugChannelsEnabled[_debugChannels[name]._channel] = true;
		return true;
	} else {
		return false;
	}
}

bool DebugManager::disableDebugChannel(const std::string &name) {
	auto pos = _debugChannels.find(name);

	if (pos != _debugChannels.end()) {
		_debugChannelsEnabled[_debugChannels[name]._channel] = false;
		return true;
	} else {
		return false;
	}
}
