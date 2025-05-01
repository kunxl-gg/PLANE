#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

/**
 * Print a debug message to the console.
 * Appends a newline.
 */
void debug(const char *s, ...);

/**
 * Print a debug message to the console.
 * Does not appends a newline.
 */
void debugN(const char *s, ...);

/**
 * Print a debug message to the text console (stdout), but only if
 * the gDebugLevel equals at least the specified level AND
 * if the specified special debug level is active.
 * As a rule of thumb, the more important the message, the lower the level.
 * Automatically appends a newline.
 * @see enableDebugChannel
 *
 * @param level         Debug level that must be active for the message to be printed.
 * @param debugChannel  Channel to check against.
 * @param s             Message to print.
 */
void debugC(int level, uint32_t debugChannel, const char *s, ...);

/**
 * Print an info message to the console.
 * Appends a newline.
 */
void info(const char *s, ...);

/**
 * Print an info message to the console.
 * Does not appends a newline.
 */
void infoN(const char *s, ...);

/**
 * Print a warning message to the console.
 * Appends a newline.
 */
void warn(const char *s, ...);

/**
 * Print a warning message to the console.
 * Does not appends a newline.
 */
void warnN(const char *s, ...);

/**
 * Print an error message to the console.
 * Appends a newline.
 */
void error(const char *s, ...);

/**
 * Print an error message to the console.
 * Does not appends a newline.
 */
void errorN(const char *s, ...);

/**
 * Print a success message to the console.
 * Appends a newline.
 */
void success(const char *s, ...);

/**
 * Print a success message to the console.
 * Does not appends a newline.
 */
void successN(const char *s, ...);

#endif // PIXL_DEBUG_HPP
