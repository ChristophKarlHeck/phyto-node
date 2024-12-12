/**
 * @file main.cpp
 * @brief Entry point for the PhytoNode application.
 *
 * This file initializes the ADC reading thread, retrieves processed data from the ReadingQueue,
 * and sends it over a serial connection.
 *
 * @details
 * - Modify the following variables in `mbed-os/connectivity/FEATURE_BLE/source/cordio/mbed_lib.json`:
 *   - `"desired-att-mtu": 250`
 *   - `"rx-acl-buffer-size": 255`
 * - Avoid using pins `PB_6` and `PB_7`, as they are reserved for `CONSOLE_TX` and `CONSOLE_RX`.
 */

// *** Third-Party Library Headers ***
#include "mbed.h"

// *** Project-Specific Headers ***
#include "adc/AD7124.h"
#include "interfaces/ReadingQueue.h"
#include "serial_mail_sender/SerialMailSender.h"

// *** DEFINE GLOBAL CONSTANTS ***

/// Downsampling rate for ADC readings in milliseconds.
#define DOWNSAMPLING_RATE 1 // ms

/// Conversion constants for ADC readings.
#define DATABITS 8388608
#define VREF 2.5
#define GAIN 4.0

/// SPI frequency for ADC communication in Hz.
#define SPI_FREQUENCY 10000000 // 10 MHz

/// Number of values to collect in each channel vector before sending mail.
#define VECTOR_SIZE 1

/// Node identifier for serial communication.
#define NODE 3

/// Thread for reading data from ADC.
Thread reading_data_thread;

/**
 * @brief Reads data from the ADC and processes it.
 *
 * This function runs in the `reading_data_thread` and continuously reads
 * voltage data from both ADC channels. The processed data is stored in the
 * ReadingQueue for inter-thread communication.
 */
void get_input_model_values_from_adc(void) {
    AD7124& adc = AD7124::getInstance(SPI_FREQUENCY);
    adc.read_voltage_from_both_channels(DOWNSAMPLING_RATE, VECTOR_SIZE);
}

/**
 * @brief Main entry point for the PhytoNode application.
 *
 * Initializes the ADC reading thread and continuously retrieves
 * processed data from the ReadingQueue. The data is then sent
 * over a serial connection using the SerialMailSender.
 * 
 * @return 0 on successful execution.
 */
int main() {	
    // Start reading data from ADC thread
    reading_data_thread.start(callback(get_input_model_values_from_adc));


    while (true) {
        // Access the shared ReadingQueue instance
        ReadingQueue& reading_queue = ReadingQueue::getInstance();

        // Wait indefinitely for mail
        auto mail = reading_queue.mail_box.try_get_for(rtos::Kernel::Clock::duration_u32::max());
        if (mail) {
            // Retrieve the message from the mail box
            ReadingQueue::mail_t* reading_mail = mail;

            auto ch0_values = reading_mail->ch0;
            auto ch1_values = reading_mail->ch1;

            // Free the allocated mail to avoid memory leaks
            reading_queue.mail_box.free(reading_mail); 
            
            // Access the serial mail sender
            SerialMailSender& serial_mail_sender = SerialMailSender::getInstance();

            // Send serial mail
            serial_mail_sender.sendMail(
                ch0_values,
                ch1_values,
                NODE
            );
        }
    }

    // main() is expected to loop forever.
    // If main() actually returns, the processor will halt.
    return 0;
}