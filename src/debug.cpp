#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>

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

