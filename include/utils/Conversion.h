#ifndef CONVERSION_H
#define CONVERSION_H

#include "mbed.h"

/**
 * @brief Converts raw ADC byte inputs into analog voltage values.
 *
 * This function processes raw ADC data and converts it into a vector of
 * corresponding analog voltage values based on the given ADC configuration.
 *
 * @note This function assumes the input data is properly formatted and scaled
 *       according to the ADC's resolution and configuration.
 */
std::vector<float> get_analog_inputs(std::vector<std::array<uint8_t, 3>> byte_inputs, int databits, float vref, float gain);

#endif // CONVERSION_H

