#ifndef SERIAL_MAIL_SENDER_H
#define SERIAL_MAIL_SENDER_H

#include <vector>
#include <array>
#include "mbed.h"  // Required for BufferedSerial
#include "serial_mail_sender/SerialMailGenerated.h"  // Required for SerialMail::Value

/**
 * @class SerialMailSender
 * @brief Singleton class responsible for serializing and sending mail data over a serial port.
 *
 * The `SerialMailSender` class provides functionality to serialize ADC readings
 * and transmit them over a serial connection. It ensures efficient and thread-safe
 * communication using a singleton design pattern.
 */
class SerialMailSender {
public:
    /**
     * @brief Gets the singleton instance of the SerialMailSender.
     * @return Reference to the singleton instance of SerialMailSender.
     */
    static SerialMailSender& getInstance(void);

    /// Deleted copy constructor to enforce the singleton pattern.
    SerialMailSender(const SerialMailSender&) = delete;

    /// Deleted copy assignment operator to enforce the singleton pattern.
    SerialMailSender& operator=(const SerialMailSender&) = delete;

    /**
     * @brief Serializes and sends mail data over the serial connection.
     * @param ch0 Downsampled ADC readings for channel 0.
     * @param ch1 Downsampled ADC readings for channel 1.
     * @param node Identifier for the data source node.
     */
    void sendMail(
        std::vector<std::array<uint8_t, 3>> ch0,
        std::vector<std::array<uint8_t, 3>> ch1,
        int node
    );

private:
    /**
     * @brief Private constructor to enforce the singleton pattern.
     */
    SerialMailSender(void);

    /**
     * @brief Destructor to clean up resources.
     */
    ~SerialMailSender(void) = default;

    /**
     * @var m_serial_port
     * @brief Static instance of BufferedSerial for serial communication.
     *
     * The serial port is used to transmit serialized mail data.
     */
    static BufferedSerial m_serial_port;

    /**
     * @brief Converts ADC inputs to a SerialMail::Value array.
     * @param inputs Vector of 3-byte arrays representing ADC inputs.
     * @return Vector of SerialMail::Value objects suitable for serialization.
     */
    std::vector<SerialMail::Value> convertToSerialMailValues(const std::vector<std::array<uint8_t, 3>>& inputs);
};

#endif // SERIAL_MAIL_SENDER_H