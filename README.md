# PhytoNode Project

PhytoNode is a modular system for collecting, processing, and transmitting sensor data using an ADC connected to a microcontroller. Built on Mbed OS, it enables real-time operations and communicates seamlessly with a Raspberry Pi for advanced data processing.

---

## Project Overview

The system comprises the following core components:

1. <b>`ADC Module`</b>: Interfaces with the AD7124 ADC for high-precision analog-to-digital conversion.
2. <b>`Inter-Thread Communication`</b>: Manages data flow between threads using Mbed OS's `Mail` objects.
3. <b>`Serial Communication`</b>: Ensures efficient data transfer to a Raspberry Pi using FlatBuffers serialization.
4. <b>`Utility Functions`</b>: Provides tools for data conversion and system performance monitoring.

---

## Directory Structure

- <b>`build/`</b>: Build artifacts.
- <b>`include/`</b>: Header files for all modules.
  - <b>`adc/`</b>: ADC module headers.
  - <b>`interfaces/`</b>: Interface headers for inter-thread communication.
  - <b>`serial_mail_sender/`</b>: Headers for serial communication.
  - <b>`utils/`</b>: Utility headers for logging and conversion.
- <b>`libs/`</b>: External libraries.
  - <b>`flatbuffers/`</b>: FlatBuffers library.
- <b>`scripts/`</b>: Configuration and utility scripts.
- <b>`src/`</b>: Source files for project modules.
  - <b>`adc/`</b>: ADC module implementation.
  - <b>`interfaces/`</b>: ReadingQueue implementation.
  - <b>`serial_mail_sender/`</b>: Serial communication logic.
  - <b>`utils/`</b>: Conversion and performance monitoring utilities.
  - <b>`main.cpp`</b>: Application entry point.
- <b>`docs/`</b>: Doxygen-generated documentation.
- <b>`third-party/`</b>: External dependencies as submodules.
  - <b>`flatbuffers/`</b>: FlatBuffers library.
  - <b>`mbed-os/`</b>: Mbed OS source.
- <b>`CMakeLists.txt`</b>: CMake build configuration.


---

## Key Features

### 1. Modular Design
- <b>ADC Module</b>:
  - Manages data acquisition from the AD7124 ADC.
  - Configures channels and performs continuous readings.
- <b>Interfaces</b>:
  - Implements a `ReadingQueue` for inter-thread communication using a singleton pattern.
- <b>Serial Communication</b>:
  - Serializes ADC data into FlatBuffers format and transmits it over UART.
- <b>Utilities</b>:
  - Converts raw ADC data to meaningful voltage values.
  - Monitors memory and CPU usage for performance optimization.

### 2. Serialization with FlatBuffers
- Compact and efficient data representation for reliable communication between the microcontroller and Raspberry Pi.

### 3. Logging and Debugging
- Uses configurable logging macros (`INFO`, `TRACE`, etc.) for consistent and readable debug output.

### 4. Real-Time Operation
- Leverages Mbed OS for multi-threading and real-time scheduling.

---

## Getting Started

### 1. Clone the Repository
```bash
git clone --recurse-submodules https://github.com/ChristophKarlHeck/phyto-node.git
cd phyto-node
```

### 2. Clone the Repository
- Install the required build tools (e.g., CMake, GCC Arm toolchain).
- Configure and build
```bash
placeholder
```

### 3. FLASH the Microcontroller
- Use OpenOCD or pyOCD to flash the firmware
```bash
placeholder
```

### 4. Run the System

- Connect the microcontroller to the Raspberry Pi via UART with the following connections:
  - <b>Microcontroller TX (PC_1)</b> → <b>Raspberry Pi RX (GPIO 15)</b>
  - <b>Microcontroller RX (PC_0)</b> → <b>Raspberry Pi TX (GPIO 14)</b>
  - <b>GND</b> → <b>GND</b>

- Ensure that the Raspberry Pi is running the serial data logger. You can find it here:  
  [serial-data-logger-phyto-node](https://github.com/ChristophKarlHeck/serial-data-logger-phyto-node)

- The microcontroller will continuously send serialized ADC data to the Raspberry Pi, which can decode and store the data for further processing.


## Documentation

Comprehensive documentation for the PhytoNode project is available online. It provides detailed information about each module, including classes, functions, and usage examples.

- <b>View Documentation</b>:  
  [PhytoNode Documentation](https://christophkarlheck.github.io/phyto-node/)

## Enable Logging

- Enable specific log levels (e.g., `LOG_LEVEL_INFO`) in `CMakeLists.txt`.

## Acknowledgments

We would like to thank the following:

- <b><a href="https://github.com/mbed-ce/mbed-os">Mbed OS</a>:</b>  
  For providing a powerful real-time operating system that simplifies development on microcontrollers.

- <b><a href="https://google.github.io/flatbuffers/">FlatBuffers</a>:</b>  
  For enabling efficient and compact data serialization for seamless communication.

- <b>The Developer Community:</b>  
  For ongoing support, contributions, and valuable insights that have helped shape this project.

Your contributions and feedback are highly appreciated!
