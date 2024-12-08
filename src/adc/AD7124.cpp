/**
 * @file ADC7124.cpp
 * @brief Implementation of the ADC7124 class for reading voltages.
 */

#include "adc/AD7124.h"
#include "adc/ad7124-defs.h"
#include "interfaces/ReadingQueue.h"
#include "utils/logger.h"


/**
 * @brief Gets the singleton instance of the AD7124 class.
 * @param spi_frequency The SPI clock frequency in Hz.
 * @return Reference to the singleton instance of the AD7124 class.
 */
AD7124& AD7124::getInstance(int spi_frequency) {
    static AD7124 instance(spi_frequency);
    return instance;
}

/**
 * @brief Constructs an AD7124 object and initializes SPI communication.
 * @param spi_frequency The SPI clock frequency in Hz.
 */
AD7124::AD7124(int spi_frequency)
    : m_spi(PA_7, PA_6, PA_5), m_spi_frequency(spi_frequency),
      m_flag_0(false), m_flag_1(false), m_read(1), m_write(0) {
    INFO("AD7124::AD7124(int spi_frequency)");

    m_spi.format(8, 0);           // 8 bits per frame, SPI Mode 0 (CPOL=0, CPHA=0)
    m_spi.frequency(m_spi_frequency); // Set the SPI frequency
}

/**
 * @brief Resets the AD7124 device to its default state.
 */
void AD7124::reset(void) {
    INFO("Resetting the AD7124 device to its default state.");
    for (int i = 0; i < 9; i++) {
        m_spi.write(0xFF); // Write reset byte to ADC
    }
}

/**
 * @brief Reads the status register of the AD7124 device.
 * @return The status byte read from the ADC.
 */
char AD7124::status(void) {
    INFO("Reading the status register of the AD7124 device.");
    m_spi.write(AD7124_R | AD7124_STATUS_REG);
    char status = m_spi.write(0x00);
    TRACE("ADC status = 0x%X, " BYTE_TO_BINARY_PATTERN, status, BYTE_TO_BINARY(status));
    return status;
}

/**
 * @brief Reads or writes to the channel register of the AD7124.
 * @param RW Indicates whether the operation is read (1) or write (0).
 */
void AD7124::channel_reg(char RW){
    // RW = 1 -> read, else write
    
    // If the operation is read, fetch the channel register values
    if(RW == m_read){
        INFO("Reading the channel register.");
        // Send read command to the channel 1 map register
        m_spi.write(AD7124_R | AD7124_CH1_MAP_REG);
        
        TRACE("Channel register =");
        
        // Loop to read two bytes of channel register data
        for (int i = 0; i < 2; i++){
            // Read the control register values (byte by byte)
            // Log the index and the read byte in binary format for debuggings
            TRACE(" Index %d: " BYTE_TO_BINARY_PATTERN, i, BYTE_TO_BINARY(m_spi.write(0x00)));
        }
        
        TRACE("\n");

    } else {
        // If the operation is write, set the channel configurations
        INFO("Writing to the channel register.");
        // Configure Channel 0 if flag0 is true
        if(m_flag_0 == true){
            m_spi.write(AD7124_CH0_MAP_REG); // Send command for Channel 0 register
            
            // Define the channel settings for Channel 0
            const uint16_t channel_settings = AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(0) |
                                               AD7124_CH_MAP_REG_AINP(0) | AD7124_CH_MAP_REG_AINM(1);
                                               
            // Split the 16-bit settings into two bytes for transmission
            char channel_reg_set_ch0[] = {channel_settings >> 8 & 0xFF, channel_settings & 0xFF}; 
            
            // Write the channel settings for Channel 0
            for (int i = 0; i < 2; i++){
                m_spi.write(channel_reg_set_ch0[i]);
            }
        }

        // Configure Channel 1 if flag1 is true
        if(m_flag_1 == true){
            m_spi.write(AD7124_CH1_MAP_REG); // Send command for Channel 1 register
            
            // Define the channel settings for Channel 1
            const uint16_t channel_settings1 = AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(1) |
                                               AD7124_CH_MAP_REG_AINP(2) | AD7124_CH_MAP_REG_AINM(3);
                                               
            // Split the 16-bit settings into two bytes for transmission
            char channel_reg_set_ch1[] = {channel_settings1 >> 8 & 0xFF, channel_settings1 & 0xFF}; 
            
            // Write the channel settings for Channel 1
            for (int i = 0; i < 2; i++){
                m_spi.write(channel_reg_set_ch1[i]);
            }
        }
    }
}

/**
 * @brief Configures the specified register of the AD7124.
 * @param address The address of the register to configure.
 * @param RW Indicates whether the operation is read (1) or write (0).
 */
void AD7124::config_reg(uint8_t address ,char RW){
    // RW = 1 -> read, else write
      
    if(RW == m_read){
        // Perform a read operation
        m_spi.write(AD7124_R | address); // Send read command to the specified register
        TRACE("ADC conf = ");

        for (int i = 0; i < 2; i++) {
            // Read the control register values (byte by byte)
            // Log the index and the read byte in binary format for debuggings
            TRACE(" Index %d: " BYTE_TO_BINARY_PATTERN, i, BYTE_TO_BINARY(m_spi.write(0x00)));
        }
        TRACE("\n");
    }
    else{
        // Perform a write operation
        m_spi.write(address); // Send address for the register to write to
        
        char my_config[] = {
            (AD7124_CFG_REG_BIPOLAR) >> 8, 
            AD7124_CFG_REG_AIN_BUFP | AD7124_CFG_REG_AINN_BUFM | AD7124_CFG_REG_REF_SEL(2) | AD7124_CFG_REG_PGA(2)
        };
        
        // Write the configuration data
        for (int i = 0; i < 2; i++){
            m_spi.write(my_config[i]); // Write configuration bytes
        } 
    }
}

/**
 * @brief Reads or writes to the filter register of the AD7124.
 * @param filt The address of the filter register to configure.
 * @param RW Indicates whether the operation is read (1) or write (0).
 */
void AD7124::filter_reg(uint8_t filt, char RW){
    // RW = 1 -> read, else write

    if(RW == m_read){
        // Send the read command to the specified filter register
        m_spi.write(AD7124_R | filt);
        TRACE("Filter register =");

        // Read and log the filter register values
        for (int i = 0; i < 3; i++) {
            // Read the control register values (byte by byte)
            // Log the index and the read byte in binary format for debuggings
            TRACE(" Index %d: " BYTE_TO_BINARY_PATTERN, i, BYTE_TO_BINARY(m_spi.write(0x00)));
        }

        TRACE("\n");
    }
    else {
        // Write a predefined filter setting to the filter register
        m_spi.write(filt);
        char filter_reg_set[]={0x00, 0x00, 0x00}; // Default values for filter configuration
        for (int i = 0; i < 3; i++){
            m_spi.write(filter_reg_set[i]);
        }
    }
}

/**
 * @brief Reads or writes to the control register of the AD7124.
 * @param RW Indicates whether the operation is read (1) or write (0).
 */
void AD7124::ctrl_reg(char RW) {

    // Check if the operation is to read the control register
    if (RW == m_read) {
        // Send the read command to the control register
        m_spi.write(AD7124_R | AD7124_ADC_CTRL_REG);

        // Log the read operation for debugging purposes
        TRACE("ADC contr_reg =");

        // Loop through the control register bytes and read their values
        for (int i = 0; i < 2; i++) {
            // Read the control register values (byte by byte)
            // Log the index and the read byte in binary format for debuggings
            TRACE(" Index %d: " BYTE_TO_BINARY_PATTERN, i, BYTE_TO_BINARY(m_spi.write(0x00)));
        }

        // End the logging of the register read
        TRACE("\n");

    } else {  // If the operation is to write to the control register
        // Send the control register address for writing
        m_spi.write(AD7124_ADC_CTRL_REG);
        
        // Configure the control register settings:
        // - Data Status: Enabled
        // - Reference Enable: Enabled
        // - Continuous Read: Enabled
        // - Power Mode: Set to 0 (default)
        // - ADC Mode: Set to 0 (default)
        // - Clock Selection: Set to 0 (default)
        const uint16_t contr_reg_settings = AD7124_ADC_CTRL_REG_DATA_STATUS | 
                                             AD7124_ADC_CTRL_REG_REF_EN | 
                                             AD7124_ADC_CTRL_REG_CONT_READ | 
                                             AD7124_ADC_CTRL_REG_POWER_MODE(0) | 
                                             AD7124_ADC_CTRL_REG_MODE(0) | 
                                             AD7124_ADC_CTRL_REG_CLK_SEL(0);

        // Prepare the control register values to be written (split into two bytes)
        char contr_reg_set[] = {contr_reg_settings >> 8 & 0xFF, contr_reg_settings & 0xFF};
        
        // Write the control register values byte by byte
        for (int i = 0; i < 2; i++) {
            m_spi.write(contr_reg_set[i]);  // Send each byte to the ADC
        }   
    }
}


/**
 * @brief Initializes the AD7124 device and activates specified channels.
 * @param f0 Flag to activate channel 0.
 * @param f1 Flag to activate channel 1.
 */
void AD7124::init(bool f0, bool f1){
    INFO("Initializing the AD7124 device with channel flags.");
    m_flag_0 = f0;
    m_flag_1 = f1;

    reset();
    status();

    channel_reg(m_read); //activate 2 channels
    channel_reg(m_write); //activate 2 channels
    channel_reg(m_read); //activate 2 channels

//flags for if you want to have channel 0, or 1, or both active
    if(m_flag_0){
        //config reg 0
        config_reg(AD7124_CFG0_REG, m_read);   // read  configuration register
        config_reg(AD7124_CFG0_REG, m_write);  // write configuration register
        config_reg(AD7124_CFG0_REG, m_read);   // proof writing by reading again
        //filter reg 0
        filter_reg(AD7124_FILT0_REG, m_read);  // same with filter register
        filter_reg(AD7124_FILT0_REG, m_write);
        filter_reg(AD7124_FILT0_REG, m_read);
        INFO("Channel 0 active\n");
    }

    if(m_flag_1){
        //config reg 1
        config_reg(AD7124_CFG1_REG, m_read);
        config_reg(AD7124_CFG1_REG, m_write);
        config_reg(AD7124_CFG1_REG, m_read);
        //filter reg 1
        filter_reg(AD7124_FILT1_REG, m_read);
        filter_reg(AD7124_FILT1_REG, m_write);
        filter_reg(AD7124_FILT1_REG, m_read);
        INFO("Channel 1 active\n");
    }
    //xAD7124::calibrate(1,1,0,0);

    ctrl_reg(m_read);     // same with control register
    ctrl_reg(m_write);
    ctrl_reg(m_read);
    //AD7124::calibrate(1,0,0,0);
}

/**
 * @brief Sends ADC data to the main thread for further processing.
 * @param byte_inputs_channel_0 Data from channel 0.
 * @param byte_inputs_channel_1 Data from channel 1.
 */
void AD7124::send_data_to_main_thread(
    std::vector<std::array<uint8_t,3>> byte_inputs_channel_0,
    std::vector<std::array<uint8_t,3>> byte_inputs_channel_1)
{
    // Access the shared queue
    ReadingQueue& reading_queue = ReadingQueue::getInstance();

    while (!reading_queue.mail_box.empty()) {
        // Wait until mail box is empty
        thread_sleep_for(10);
        INFO("Wait for the reading queue to become empty.\n");
    }

    // Now that we have data in the channels, let's handle mailing
    if (reading_queue.mail_box.empty()) {
        ReadingQueue::mail_t* mail = reading_queue.mail_box.try_alloc();
        
        mail->ch0 = byte_inputs_channel_0;
        byte_inputs_channel_0.clear();
        mail->ch1 = byte_inputs_channel_1;
        byte_inputs_channel_1.clear();
        reading_queue.mail_box.put(mail);

    }

}

/**
 * @brief Reads voltage data from both ADC channels with downsampling.
 * @param downsampling_rate The rate to downsample ADC readings (in ms).
 * @param vector_size The size of the resulting data vectors.
 */
void AD7124::read_voltage_from_both_channels(unsigned int downsampling_rate, unsigned int vector_size){

    while (true){
        std::vector<std::array<uint8_t,3>> byte_inputs_channel_0;
        std::vector<std::array<uint8_t,3>> byte_inputs_channel_1;
        
        // While the vector's size is less than 4, append 3-byte arrays
        while ((byte_inputs_channel_0.size() < vector_size) || (byte_inputs_channel_1.size() < vector_size)){
            
            uint8_t data[4] = {0, 0, 0, 255};
            for(int j = 0; j < 4; j++){
                // Sends 0x00 and simultaneously receives a byte from the SPI slave device.
                data[j] = m_spi.write(0x00);
            }
            
            data[3] = 0; // to mock sensor 0 reading

            if(data[3] == 0){
                // data from channel 0
                if (byte_inputs_channel_0.size() < vector_size) {
                    // Add new value
                    std::array<uint8_t, 3> new_bytes = {data[0], data[1], data[2]};
                    byte_inputs_channel_0.push_back(new_bytes);
                } else {
                    // Replace the oldest value with the new value (circular buffer approach)
                    std::array<uint8_t, 3> new_bytes = {data[0], data[1], data[2]};
                    byte_inputs_channel_0.erase(byte_inputs_channel_0.begin()); // Remove the oldest element
                    byte_inputs_channel_0.push_back(new_bytes); // Add the new value
                }
            }

            data[3] = 1; // to mock sensor 0 reading

            if(data[3] == 1){
                // data from channel 1
                if(byte_inputs_channel_1.size() < vector_size){
                    std::array<uint8_t, 3> new_bytes = {data[0], data[1], data[2]};
                    byte_inputs_channel_1.push_back(new_bytes);
                } else{
                    std::array<uint8_t, 3> new_bytes = {data[0], data[1], data[2]};
                    byte_inputs_channel_1.erase(byte_inputs_channel_1.begin()); // Remove the oldest element
                    byte_inputs_channel_1.push_back(new_bytes);
                }

            }

            thread_sleep_for(downsampling_rate); // ms
        }

        send_data_to_main_thread(byte_inputs_channel_0, byte_inputs_channel_1);

    }
}