/**
 * @file Conversion.cpp
 * @brief Provides utility functions for data conversion in the PhytoNode project.
 */

#include "utils/Conversion.h" // Include the header for the function declaration
#include "utils/logger.h"     // Include the logger for INFO statements

/**
 * @brief Converts raw ADC measurements into analog voltage values.
 * 
 * @param byte_inputs A vector of 3-byte arrays representing raw ADC measurements.
 * @param databits The number of bits used for ADC resolution (e.g., 8388608 for 24-bit ADC).
 * @param vref The reference voltage of the ADC in volts.
 * @param gain The gain applied to the ADC measurements.
 * 
 * @return A vector of converted voltage values in millivolts.
 * 
 * @details
 * This function processes raw ADC data represented as 3-byte arrays, calculates
 * the corresponding analog voltage based on the ADC's resolution, reference voltage,
 * and gain, and returns the values in millivolts.
 */
std::vector<float> get_analog_inputs(std::vector<std::array<uint8_t, 3>> byte_inputs, int databits, float vref, float gain) {
    INFO("Converting raw ADC inputs to analog voltages.");

    // Store the converted voltage values
    std::vector<float> inputs;

    // Loop through each raw ADC measurement
    for (unsigned int i = 0; i < byte_inputs.size(); i++) {
        // Combine the 3-byte array into a single 24-bit integer value
        int measurement = (((int)byte_inputs[i][0] << 16) | (int)byte_inputs[i][1] << 8) | ((int)byte_inputs[i][2] << 0);

        // Calculate the voltage from the measurement
        float voltage = (float)measurement / (float)databits - 1;
        voltage = voltage * vref / gain;
        voltage *= 1000; // Convert to millivolts

        // Store the converted voltage in the output vector
        inputs.push_back(voltage);
    }

    // Log the converted values for debugging
    for (size_t i = 0; i < inputs.size(); ++i) {
        INFO("inputs[%zu] = %.3f mV", i, inputs[i]);
    }

    return inputs;
}