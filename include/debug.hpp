#ifndef DEBUG_H
#define DEBUG_H

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

#endif // DEBUG_H
