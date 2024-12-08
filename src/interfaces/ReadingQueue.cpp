/**
 * @file ReadingQueue.cpp
 * @brief Implementation of the ReadingQueue class for inter-thread communication.
 */

#include "interfaces/ReadingQueue.h"
#include "utils/logger.h"

/**
 * @brief Access the singleton instance of the ReadingQueue.
 *
 * @return Reference to the single instance of ReadingQueue.
 *
 * @details
 * This method ensures that only one instance of the ReadingQueue
 * exists throughout the application's lifetime. The instance is
 * created on the first call and destroyed automatically at the
 * end of the program's execution.
 */
ReadingQueue& ReadingQueue::getInstance() {
    static ReadingQueue instance;  // Guaranteed to be destroyed, initialized on first use
    return instance;
}

/**
 * @brief Constructs a ReadingQueue instance.
 *
 * @details
 * This private constructor prevents direct instantiation of the class,
 * ensuring that the singleton design pattern is enforced. Any necessary
 * initialization for the queue can be added here.
 */
ReadingQueue::ReadingQueue(void) {
    INFO("ReadingQueue initialized.");
    // Initialization code, if necessary
}

/**
 * @brief Destroys the ReadingQueue instance.
 *
 * @details
 * This private destructor ensures proper cleanup of resources
 * when the singleton instance is destroyed at program termination.
 * Add any cleanup logic here if necessary.
 */
ReadingQueue::~ReadingQueue() {
    INFO("ReadingQueue destroyed.");
    // Cleanup code, if necessary
}
