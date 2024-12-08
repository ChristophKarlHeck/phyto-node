/**
 * @file SerialMailSender.cpp
 * @brief Implementation of the SerialMailSender class for serial communication using FlatBuffers.
 */

#include "serial_mail_sender/SerialMailSender.h"
#include "flatbuffers/flatbuffers.h"
#include "utils/logger.h"

#define BAUDRATE 115200 ///< UART baud rate for serial communication

/**
 * @brief Initialize the static BufferedSerial instance.
 * 
 * TX: PC_1, RX: PC_0 (NUCLEO board)
 * Raspberry Pi connection:
 * - TX -> GPIO 15 (RX)
 * - RX -> GPIO 14 (TX)
 * - GND -> GND
 */
BufferedSerial SerialMailSender::m_serial_port(PC_1, PC_0, BAUDRATE);

/**
 * @brief Access the singleton instance of SerialMailSender.
 * 
 * @return Reference to the single instance of SerialMailSender.
 */
SerialMailSender& SerialMailSender::getInstance(void) {
    static SerialMailSender instance;
    return instance;
}

/**
 * @brief Constructs a SerialMailSender instance.
 * 
 * Sets the serial port format to 8 data bits, no parity, and 1 stop bit (8N1).
 */
SerialMailSender::SerialMailSender(void) {
    m_serial_port.set_format(8, BufferedSerial::None, 1);  // 8N1 format
}

/**
 * @brief Converts a vector of 3-byte arrays into a vector of SerialMail::Value structs.
 * 
 * @param inputs A vector of 3-byte arrays to be converted.
 * @return A vector of SerialMail::Value objects.
 */
std::vector<SerialMail::Value> SerialMailSender::convertToSerialMailValues(const std::vector<std::array<uint8_t, 3>>& inputs) {
    std::vector<SerialMail::Value> raw_input_bytes;
    raw_input_bytes.reserve(inputs.size()); // Reserve space for efficiency

    for (const auto& input : inputs) {
        // Create SerialMail::Value from each 3-byte array
        raw_input_bytes.emplace_back(SerialMail::Value(input[0], input[1], input[2]));
    }

    return raw_input_bytes;
}

/**
 * @brief Serializes and sends ADC data using FlatBuffers over UART.
 * 
 * @details
 * This method prepares the data for transmission using FlatBuffers.
 * It includes a synchronization marker, the size of the FlatBuffer, 
 * and the serialized data.
 */
void SerialMailSender::sendMail(
    std::vector<std::array<uint8_t, 3>> ch0,
    std::vector<std::array<uint8_t, 3>> ch1,
    int node) {

    // Prepare the FlatBufferBuilder
    flatbuffers::FlatBufferBuilder builder(1024);

    // Convert data to FlatBuffers format
    std::vector<SerialMail::Value> raw_input_bytes_ch0 = convertToSerialMailValues(ch0);
    std::vector<SerialMail::Value> raw_input_bytes_ch1 = convertToSerialMailValues(ch1);
    auto ch0_flatbuffers = builder.CreateVectorOfStructs(raw_input_bytes_ch0.data(), raw_input_bytes_ch0.size());
    auto ch1_flatbuffers = builder.CreateVectorOfStructs(raw_input_bytes_ch1.data(), raw_input_bytes_ch1.size());

    // Create the SerialMail object
    auto orc = SerialMail::CreateSerialMail(builder, ch0_flatbuffers, ch1_flatbuffers, node);
    builder.Finish(orc);

    // Get the buffer pointer and size
    uint8_t* buf = builder.GetBufferPointer();
    uint32_t size = builder.GetSize();

    // Send a synchronization marker (e.g., 0xAAAA)
    uint16_t sync_marker = 0xAAAA;
    m_serial_port.write(reinterpret_cast<const char*>(&sync_marker), sizeof(sync_marker));

    // Send the size (4 bytes)
    m_serial_port.write(reinterpret_cast<const char*>(&size), sizeof(size));

    // Send the FlatBuffers buffer
    m_serial_port.write(reinterpret_cast<const char*>(buf), size);

    // Log message details
    auto now = Kernel::Clock::now().time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now).count();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now).count() % 1000;

    printf("Serial Mail(size:%lu) sent at: %lld seconds and %lld milliseconds\n", size, seconds, milliseconds);
}
