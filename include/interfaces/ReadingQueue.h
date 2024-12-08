#ifndef READING_QUEUE_H
#define READING_QUEUE_H

#include "mbed.h"
#include <vector>
#include <array>

/**
 * @class ReadingQueue
 * @brief Singleton class for managing inter-thread communication using a mailbox.
 *
 * The `ReadingQueue` class provides a thread-safe mechanism for inter-thread communication
 * using an Mbed OS Mailbox. It stores and manages messages containing ADC readings for
 * multiple channels.
 */
class ReadingQueue {
public:
    /**
     * @brief Gets the singleton instance of the ReadingQueue.
     * @return Reference to the singleton instance of the ReadingQueue.
     */
    static ReadingQueue& getInstance();

    /**
     * @struct mail_t
     * @brief Structure used for inter-thread communication.
     *
     * The `mail_t` structure contains vectors of downsampled ADC readings for
     * multiple channels. Each vector holds 3-byte arrays representing the data.
     */
    typedef struct {
        std::vector<std::array<uint8_t, 3>> ch0;  ///< Downsampled ADC values for channel 0.
        std::vector<std::array<uint8_t, 3>> ch1;  ///< Downsampled ADC values for channel 1.
    } mail_t;

    /**
     * @var mail_box
     * @brief Mailbox for storing inter-thread messages.
     *
     * The mailbox can hold up to 4 messages by default. It uses the `mail_t` structure
     * to store data passed between threads.
     */
    Mail<mail_t, 4> mail_box;  ///< Queue for inter-thread communication (size 4).

private:
    /**
     * @brief Private constructor to enforce the singleton pattern.
     *
     * The constructor initializes any necessary resources for the mailbox.
     */
    ReadingQueue(void);

    /**
     * @brief Private destructor.
     *
     * Ensures proper cleanup of resources when the ReadingQueue is destroyed.
     */
    ~ReadingQueue();

    // Deleted copy constructor and assignment operator to prevent copies
    ReadingQueue(const ReadingQueue&) = delete;  ///< Deleted copy constructor.
    ReadingQueue& operator=(const ReadingQueue&) = delete;  ///< Deleted assignment operator.
};

#endif // READING_QUEUE_H