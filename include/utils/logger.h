#ifndef LOGGER_H
#define LOGGER_H

/**
 * @file logger.h
 * @brief Logging utility for debugging and runtime information output.
 *
 * This header file provides logging macros for different log levels, allowing
 * developers to control the verbosity of log messages at compile time.
 *
 * @note Logging behavior is controlled by defining specific log level macros
 *       such as `LOG_LEVEL_TRACE`, `LOG_LEVEL_DEBUG`, etc. Undefined levels
 *       will disable logging for those levels.
 */

// Uncomment the following lines to enable logging and set the default log level
//#define ENABLE_LOGGING
//#define LOG_LEVEL_INFO

// Log level macros
#if defined(LOG_LEVEL_TRACE)
/**
 * @brief Logs trace messages for detailed debugging.
 * @param x Format string for the log message.
 * @param ... Additional arguments for the format string.
 */
    #define TRACE(x, ...) printf("[TRACE: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs debug messages for general debugging.
 * @param x Format string for the log message.
 * @param ... Additional arguments for the format string.
 */
    #define DEBUG(x, ...) printf("[DEBUG: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs informational messages.
 * @param x Format string for the log message.
 * @param ... Additional arguments for the format string.
 */
    #define INFO(x, ...) printf("[INFO: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs warnings indicating potential issues.
 * @param x Format string for the log message.
 * @param ... Additional arguments for the format string.
 */
    #define WARN(x, ...) printf("[WARN: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Logs error messages indicating serious issues.
 * @param x Format string for the log message.
 * @param ... Additional arguments for the format string.
 */
    #define ERROR(x, ...) printf("[ERROR: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

#elif defined(LOG_LEVEL_DEBUG)
    #define TRACE(x, ...)
    #define DEBUG(x, ...) printf("[DEBUG: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define INFO(x, ...) printf("[INFO: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define WARN(x, ...) printf("[WARN: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define ERROR(x, ...) printf("[ERROR: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

#elif defined(LOG_LEVEL_INFO)
    #define TRACE(x, ...)
    #define DEBUG(x, ...)
    #define INFO(x, ...) printf("[INFO: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define WARN(x, ...) printf("[WARN: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define ERROR(x, ...) printf("[ERROR: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

#elif defined(LOG_LEVEL_WARN)
    #define TRACE(x, ...)
    #define DEBUG(x, ...)
    #define INFO(x, ...)
    #define WARN(x, ...) printf("[WARN: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
    #define ERROR(x, ...) printf("[ERROR: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

#elif defined(LOG_LEVEL_ERROR)
    #define TRACE(x, ...)
    #define DEBUG(x, ...)
    #define INFO(x, ...)
    #define WARN(x, ...)
    #define ERROR(x, ...) printf("[ERROR: %s:%d] " x "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

#else
    #define TRACE(x, ...)
    #define DEBUG(x, ...)
    #define INFO(x, ...)
    #define WARN(x, ...)
    #define ERROR(x, ...)
#endif

#endif // LOGGER_H
