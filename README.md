# **PhytoNode Project**

PhytoNode is a modular system for collecting, processing, and transmitting sensor data using an ADC connected to a microcontroller. Built on Mbed OS, it enables real-time operations and communicates seamlessly with a Raspberry Pi for advanced data processing.

---

## **Project Overview**

The system comprises the following core components:
1. **ADC Module**: Interfaces with the AD7124 ADC for high-precision analog-to-digital conversion.
2. **Inter-Thread Communication**: Manages data flow between threads using Mbed OS's `Mail` objects.
3. **Serial Communication**: Ensures efficient data transfer to a Raspberry Pi using FlatBuffers serialization.
4. **Utility Functions**: Provides tools for data conversion and system performance monitoring.

---

## **Directory Structure**

- **`build/`**: Build artifacts.
- **`include/`**: Header files for all modules.
  - **`adc/`**: ADC module headers.
  - **`interfaces/`**: Interface headers for inter-thread communication.
  - **`serial_mail_sender/`**: Headers for serial communication.
  - **`utils/`**: Utility headers for logging and conversion.
- **`libs/`**: External libraries.
  - **`flatbuffers/`**: FlatBuffers library.
- **`scripts/`**: Configuration and utility scripts.
- **`src/`**: Source files for project modules.
  - **`adc/`**: ADC module implementation.
  - **`interfaces/`**: ReadingQueue implementation.
  - **`serial_mail_sender/`**: Serial communication logic.
  - **`utils/`**: Conversion and performance monitoring utilities.
  - **`main.cpp`**: Application entry point.
- **`docs/`**: Doxygen-generated documentation.
- **`third-party/`**: External dependencies as submodules.
  - **`flatbuffers/`**: FlatBuffers library.
  - **`mbed-os/`**: Mbed OS source.
- **`CMakeLists.txt`**: CMake build configuration.


---

\section key_features Key Features

### 1. Modular Design
- **ADC Module**:
  - Manages data acquisition from the AD7124 ADC.
  - Configures channels and performs continuous readings.
- **Interfaces**:
  - Implements a `ReadingQueue` for inter-thread communication using a singleton pattern.
- **Serial Communication**:
  - Serializes ADC data into FlatBuffers format and transmits it over UART.
- **Utilities**:
  - Converts raw ADC data to meaningful voltage values.
  - Monitors memory and CPU usage for performance optimization.

### 2. Serialization with FlatBuffers
- Compact and efficient data representation for reliable communication between the microcontroller and Raspberry Pi.

### 3. Logging and Debugging
- Uses configurable logging macros (`INFO`, `TRACE`, etc.) for consistent and readable debug output.

### 4. Real-Time Operation
- Leverages Mbed OS for multi-threading and real-time scheduling.

---

## **Getting Started**

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
  - **Microcontroller TX (PC_1)** -> **Raspberry Pi RX (GPIO 15)**
  - **Microcontroller RX (PC_0)** -> **Raspberry Pi TX (GPIO 14)**
  - **GND** -> **GND**

- Ensure that the Raspberry Pi is running the serial data logger. You can find it here:  
  [serial-data-logger-phyto-node](https://github.com/ChristophKarlHeck/serial-data-logger-phyto-node)

- The microcontroller will continuously send serialized ADC data to the Raspberry Pi, which can decode and store the data for further processing.


## **Documentation**

Comprehensive documentation for the PhytoNode project is available online. It provides detailed information about each module, including classes, functions, and usage examples.

- **View Documentation**:  
  [PhytoNode Documentation](https://christophkarlheck.github.io/phyto-node/)

## **Enable Logging**
- Enable specific log levels (e.g., LOG_LEVEL_INFO) in `CMakeLists.txt`.

## **Acknowledgments**

We would like to thank the following:

- **[Mbed OS](https://os.mbed.com/):**  
  For providing a powerful real-time operating system that simplifies development on microcontrollers.

- **[FlatBuffers](https://google.github.io/flatbuffers/):**  
  For enabling efficient and compact data serialization for seamless communication.

- **The Developer Community:**  
  For ongoing support, contributions, and valuable insights that have helped shape this project.

Your contributions and feedback are highly appreciated!
