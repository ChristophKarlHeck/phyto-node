# Source Directory

The <b>src</b> directory contains the implementation files for various modules of the PhytoNode Project. These files define the functionality of the system, including ADC data acquisition, inter-thread communication, serial communication, and utility functions.

## Directory Structure

- <b>adc/</b>: ADC module implementation.
  - <b>AD7124.cpp</b>: Handles ADC functionality using the AD7124 module, including channel configuration and data acquisition.
- <b>interfaces/</b>: Interface for inter-thread communication.
  - <b>ReadingQueue.cpp</b>: Implements a thread-safe message queue for ADC data using Mbed OS `Mail`.
- <b>serial_mail_sender/</b>: Handles serial communication.
  - <b>SerialMailSender.cpp</b>: Serializes ADC data using FlatBuffers and sends it over UART to the Raspberry Pi.
- <b>utils/</b>: Utility implementations.
  - <b>Conversion.cpp</b>: Converts raw ADC data into analog voltage values.
  - <b>MbedStatsWrapper.cpp</b>: Monitors system performance, including memory and CPU usage.
- <b>main.cpp</b>: Application entry point.
  - Initializes the ADC reading thread and manages communication with the Raspberry Pi.

## Modules Overview

### 1. adc
- <b>AD7124.cpp</b>:
  - Implements the interface for the AD7124 Analog-to-Digital Converter (ADC) as a singleton.
  - Handles initialization, channel configuration, and data acquisition.

### 2. interfaces
- <b>ReadingQueue.cpp</b>:
  - Implements a singleton-based message queue for inter-thread communication.
  - Uses Mbed OS's `Mail` object to manage ADC data.

### 3. serial_mail_sender
- <b>SerialMailSender.cpp</b>:
  - Serializes ADC data using FlatBuffers as a singleton.
  - Sends data to the Raspberry Pi over UART using a synchronization marker.

### 4. utils
- <b>Conversion.cpp</b>:
  - Converts raw ADC data into analog voltage values in millivolts.
- <b>MbedStatsWrapper.cpp</b>:
  - Prints memory usage and CPU statistics to help monitor system performance.

### 5. main.cpp
- The main entry point of the application.
- Initializes the ADC reading thread.
- Manages data retrieval from the `ReadingQueue` and transmission using `SerialMailSender`.

## Key Features

1. **Modular Design**:
   - Each module has a dedicated directory with its own implementation files.

2. **Inter-Thread Communication**:
   - Data is passed between threads using the `ReadingQueue`.

3. **Serialization with FlatBuffers**:
   - Ensures efficient and compact data transfer between the microcontroller and Raspberry Pi.

4. **Utility Functions**:
   - Includes utilities for data conversion and system performance monitoring.

## How to Use

1. **Compile the Code**:
   - Use the CMake build system configured for the PhytoNode project.
   - The <b>main.cpp</b> file acts as the entry point.

2. **Extend Functionality**:
   - Add new `.cpp` files under the relevant module directories.
   - Ensure corresponding `.h` files are located in the `include` directory.

3. **Logging**:
   - Enable logging by defining `ENABLE_LOGGING` and setting a log level (e.g., `LOG_LEVEL_INFO`) in `CMakeLists.txt`.

4. **Integration with Raspberry Pi**:
   - Connect the UART pins (TX, RX, GND) between the microcontroller and Raspberry Pi.
   - Ensure that the Raspberry Pi runs a compatible script to decode and store the received data.

## Contribution Guidelines

1. Follow the directory structure for adding new modules.
2. Use Doxygen comments for all functions and classes.
3. Replace `printf` with the `INFO` logging macro for consistency.
4. Update this `README.md` with details of any new modules.

## Additional Information

- For detailed module documentation, refer to the [Doxygen documentation](../docs/README.md).
- The application is designed for the NUCLEO_WB55RG development board with Mbed OS.