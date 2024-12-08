#ifndef MBED_STATS_WRAPPER_H
#define MBED_STATS_WRAPPER_H

/**
 * @file MbedStatsWrapper.h
 * @brief Provides utility functions to print Mbed OS system statistics.
 *
 * This header declares functions for printing memory usage and CPU statistics
 * of the system. These utilities are helpful for debugging and performance monitoring.
 */

/**
 * @brief Prints the current memory usage statistics.
 *
 * This function retrieves and displays memory usage details, including
 * heap and stack usage, to help monitor and debug memory-related issues.
 *
 * Example output:
 * ```
 * Heap size: 1024 bytes, Used: 512 bytes, Free: 512 bytes
 * Stack size: 2048 bytes, Used: 1024 bytes, Free: 1024 bytes
 * ```
 */
void print_memory_usage();

/**
 * @brief Prints the current CPU usage statistics.
 *
 * This function retrieves and displays details about the CPU usage,
 * including idle time percentage, thread activity, and other CPU metrics.
 *
 * Example output:
 * ```
 * CPU idle: 75%, Active threads: 4
 * ```
 */
void print_cpu_stats();

#endif // MBED_STATS_WRAPPER_H
