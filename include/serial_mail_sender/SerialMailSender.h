#ifndef SERIAL_MAIL_SENDER_H
#define SERIAL_MAIL_SENDER_H

#include <vector>
#include <array>

#include "mbed.h" // needed for BufferedSerial
#include "serial_mail_sender/SerialMailGenerated.h" // needed vor SerialMail::Value

class SerialMailSender {
public:
    // Get the single instance of SerialMailSender
    static SerialMailSender& getInstance(void);

    // Delete copy constructor and assignment operator to enforce singleton
    SerialMailSender(const SerialMailSender&) = delete;
    SerialMailSender& operator=(const SerialMailSender&) = delete;

    // Method to serialize and send SerialMail data
    void sendMail(
        std::vector<std::array<uint8_t, 3>> ch0,
        std::vector<std::array<uint8_t, 3>> ch1,
        int node
    );

private:
    // Private constructor
    SerialMailSender(void);

    // Private destructor
    ~SerialMailSender(void) = default;

    // Static BufferedSerial instance
    static BufferedSerial m_serial_port;

    // Function to convert inputs to SerialMail::Value array
    std::vector<SerialMail::Value> convertToSerialMailValues(const std::vector<std::array<uint8_t, 3>>& inputs);
};

#endif // SERIAL_MAIL_SENDER_H
