# Include Directory

The `include` directory contains header files for the various modules of the **PhytoNode Project**. These headers define the public interfaces and utilities used throughout the project.

## **Directory Structure**

- **`adc/`**: Headers for the ADC module.
  - **`AD7124.h`**: Declares the interface for interacting with the AD7124 ADC module, including initialization, channel configuration, and data acquisition.
  - **`AD7124-defs.h`**: Contains constants, macros, and register definitions specific to the AD7124 ADC.
- **`interfaces/`**: Interface for inter-thread communication.
  - **`ReadingQueue.h`**: Declares the `ReadingQueue` class, which manages a thread-safe message queue for ADC data.
- **`serial_mail_sender/`**: Headers for serial communication.
  - **`SerialMailSender.h`**: Declares the `SerialMailSender` class, which handles data serialization with FlatBuffers and UART communication.
- **`utils/`**: Utility headers for various support functions.
  - **`Conversion.h`**: Declares the `get_analog_inputs` function for converting raw ADC data into voltage values.
  - **`Logger.h`**: Provides macros (`INFO`, `TRACE`, etc.) for consistent and configurable logging.
  - **`MbedStatsWrapper.h`**: Declares functions for monitoring memory and CPU usage.

## Modules Overview

### 1. `adc`
- **`AD7124.h`**: 
  - Interface for the AD7124 Analog-to-Digital Converter (ADC).
  - Provides methods for initialization, channel configuration, and reading voltage data.
- **`AD7124-defs.h`**: 
  - Definitions for AD7124 registers, bit masks, and settings.

### 2. `interfaces`
- **`ReadingQueue.h`**: 
  - Singleton class for managing inter-thread communication.
  - Uses Mbed OS's `Mail` object to pass ADC readings between threads.

### 3. `serial_mail_sender`
- **`SerialMailSender.h`**: 
  - Singleton for serializing ADC data and sending it over a serial connection.
  - Handles data formatting and transmission.

### 4. `utils`
- **`Conversion.h`**:
  - Converts raw ADC data into analog voltage values based on ADC configuration.
- **`Logger.h`**:
  - Provides macros for logging at various levels (TRACE, DEBUG, INFO, WARN, ERROR).
  - Configurable through compile-time definitions.
- **`MbedStatsWrapper.h`**:
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
- Use `Doxygen` to generate detailed API documentation.


