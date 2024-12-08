# Include Directory

The <b>include</b> directory contains header files for the various modules of the PhytoNode Project. These headers define the public interfaces and utilities used throughout the project.

## Directory Structure

- <b>adc/</b>: Headers for the ADC module.
  - <b>AD7124.h</b>: Declares the interface for interacting with the AD7124 ADC module, including initialization, channel configuration, and data acquisition.
  - <b>AD7124-defs.h</b>: Contains constants, macros, and register definitions specific to the AD7124 ADC.
- <b>interfaces/</b>: Interface for inter-thread communication.
  - <b>ReadingQueue.h</b>: Declares the `ReadingQueue` class, which manages a thread-safe message queue for ADC data.
- <b>serial_mail_sender/</b>: Headers for serial communication.
  - <b>SerialMailSender.h</b>: Declares the `SerialMailSender` class, which handles data serialization with FlatBuffers and UART communication.
- <b>utils/</b>: Utility headers for various support functions.
  - <b>Conversion.h</b>: Declares the `get_analog_inputs` function for converting raw ADC data into voltage values.
  - <b>Logger.h</b>: Provides macros (`INFO`, `TRACE`, etc.) for consistent and configurable logging.
  - <b>MbedStatsWrapper.h</b>: Declares functions for monitoring memory and CPU usage.

## Modules Overview

### 1. adc
- <b>AD7124.h</b>:
  - Interface for the AD7124 Analog-to-Digital Converter (ADC).
  - Provides methods for initialization, channel configuration, and reading voltage data.
- <b>AD7124-defs.h</b>:
  - Definitions for AD7124 registers, bit masks, and settings.

### 2. interfaces
- <b>ReadingQueue.h</b>:
  - Singleton class for managing inter-thread communication.
  - Uses Mbed OS's `Mail` object to pass ADC readings between threads.

### 3. serial_mail_sender
- <b>SerialMailSender.h</b>:
  - Singleton for serializing ADC data and sending it over a serial connection.
  - Handles data formatting and transmission.

### 4. utils
- <b>Conversion.h</b>:
  - Converts raw ADC data into analog voltage values based on ADC configuration.
- <b>Logger.h</b>:
  - Provides macros for logging at various levels (`TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`).
  - Configurable through compile-time definitions.
- <b>MbedStatsWrapper.h</b>:
  - Utility functions to print memory and CPU statistics using Mbed OS APIs.

## How to Use

1. **Include Headers in Source Files:**
   - Import the relevant headers in your `.cpp` files to use the modules. For example:
     ```cpp
     #include "adc/AD7124.h"
     #include "utils/Logger.h"
     ```

2. **Enable Logging:**
   - Configure the desired logging level in the `CMakeLists.txt`:
     ```cmake
     target_compile_definitions(PhytoNode PRIVATE ENABLE_LOGGING LOG_LEVEL_TRACE)
     ```

3. **Extend Utilities:**
   - Add new headers to this directory following the module structure.

## Contribution Guidelines

1. Document all header files using Doxygen-style comments.
2. Ensure consistency in naming conventions and directory structure.
3. Add new modules or utilities with appropriate comments and examples.

## Additional Information

- For detailed documentation, refer to the [project-level README.md](../README.md).
- Use Doxygen to generate detailed API documentation.