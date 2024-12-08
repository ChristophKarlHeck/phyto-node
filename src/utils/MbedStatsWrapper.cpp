/**
 * @file MbedStatsWrapper.cpp
 * @brief Utility functions to display memory and CPU statistics in Mbed OS.
 */

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "utils/logger.h"

#define MAX_THREAD_INFO 10 ///< Maximum number of threads for stack statistics
#define MAX_THREAD_STACK 384 ///< Maximum thread stack size
#define SAMPLE_TIME_MS   2000 ///< Sample time for CPU statistics in milliseconds
#define LOOP_TIME_MS     3000 ///< Loop time for statistics collection in milliseconds

static uint64_t prev_idle_time = 0; ///< Tracks the previous idle time for CPU usage calculation

/**
 * @brief Prints the current memory usage statistics.
 * 
 * @details
 * - Retrieves heap and stack information using Mbed OS APIs.
 * - Logs detailed statistics for debugging and performance monitoring.
 */
void print_memory_usage() {
    INFO("Collecting memory usage statistics.");

    // Print heap statistics
    mbed_stats_heap_t heap_info;
    mbed_stats_stack_t stack_info[MAX_THREAD_INFO];

    mbed_stats_heap_get(&heap_info);
    INFO("Heap Info:");
    INFO("\tBytes allocated currently: %ld", heap_info.current_size);
    INFO("\tMax bytes allocated at a given time: %ld", heap_info.max_size);
    INFO("\tCumulative sum of bytes ever allocated: %ld", heap_info.total_size);
    INFO("\tCurrent number of bytes allocated for the heap: %ld", heap_info.reserved_size);
    INFO("\tCurrent number of allocations: %ld", heap_info.alloc_cnt);
    INFO("\tNumber of failed allocations: %ld", heap_info.alloc_fail_cnt);

    mbed_stats_stack_get(&stack_info[0]);
    INFO("Cumulative Stack Info:");
    INFO("\tMaximum number of bytes used on the stack: %ld", stack_info[0].max_size);
    INFO("\tCurrent number of bytes allocated for the stack: %ld", stack_info[0].reserved_size);
    INFO("\tNumber of stacks stats accumulated in the structure: %ld", stack_info[0].stack_cnt);

    mbed_stats_stack_get_each(stack_info, MAX_THREAD_INFO);
    INFO("Thread Stack Info:");
    for (int i = 0; i < MAX_THREAD_INFO; i++) {
        if (stack_info[i].thread_id != 0) {
            INFO("\tThread: %d", i);
            INFO("\t\tThread Id: 0x%08lX", stack_info[i].thread_id);
            INFO("\t\tMaximum number of bytes used on the stack: %ld", stack_info[i].max_size);
            INFO("\t\tCurrent number of bytes allocated for the stack: %ld", stack_info[i].reserved_size);
            INFO("\t\tNumber of stacks stats accumulated in the structure: %ld", stack_info[i].stack_cnt);
        }
    }
}

/**
 * @brief Prints the current CPU usage statistics.
 * 
 * @details
 * - Retrieves CPU uptime, idle time, and sleep times using Mbed OS APIs.
 * - Calculates CPU usage as a percentage and logs the statistics.
 */
void print_cpu_stats() {
    INFO("Collecting CPU usage statistics.");

    mbed_stats_cpu_t stats;
    mbed_stats_cpu_get(&stats);

    // Calculate the percentage of CPU usage
    uint64_t diff_usec = (stats.idle_time - prev_idle_time);
    uint8_t idle = (diff_usec * 100) / (SAMPLE_TIME_MS * 1000);
    uint8_t usage = 100 - idle;
    prev_idle_time = stats.idle_time;

    INFO("CPU Info:");
    INFO("\tTime (us): Up: %lld", stats.uptime);
    INFO("\tIdle: %lld", stats.idle_time);
    INFO("\tSleep: %lld", stats.sleep_time);
    INFO("\tDeepSleep: %lld", stats.deep_sleep_time);
    INFO("\tIdle: %d%% Usage: %d%%", idle, usage);
}