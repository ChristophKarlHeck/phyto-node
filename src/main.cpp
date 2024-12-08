/*
Change the values of the following variables in the file: mbed-os/connectivity/FEATUR_BLE/source/cordio/mbed_lib.json
- "desired-att-mtu": 250
- "rx-acl-buffer-size": 255
- PB_6 and PB_7 are reserevd for CONSOLE_TX and CNSOLE_RX. Therefore do not use PB_6 and PB_7.
*/

// Standard Library Headers
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

// Third-Party Library Headers
#include "mbed.h"

// Project-Specific Headers
#include "adc/AD7124.h"
#include "interfaces/ReadingQueue.h"
#include "serial_mail_sender/SerialMailSender.h"

// Utility Headers
#include "utils/Conversion.h"
#include "utils/logger.h"

// *** DEFINE GLOBAL CONSTANTS ***
#define DOWNSAMPLING_RATE 10 // ms

// CONVERSION
#define DATABITS 8388608
#define VREF 2.5
#define GAIN 4.0

// ADC
#define SPI_FREQUENCY 10000000 // 1MHz
#define VECTOR_SIZE 1 // Number of values to collect in each channel vector befor mail is sent

// SERIAL MAIL
#define NODE 1

// Thread for reading data from ADC
Thread reading_data_thread;

// Function called in thread "reading_data_thread"
void get_input_model_values_from_adc(void){

	AD7124& adc = AD7124::getInstance(SPI_FREQUENCY);
	adc.init(true, true); // activate both channels
	adc.read_voltage_from_both_channels(DOWNSAMPLING_RATE, VECTOR_SIZE);
}

int main()
{	
    
	//Start reading data from ADC Thread
	reading_data_thread.start(callback(get_input_model_values_from_adc));

    while (true) {
		// Access the shared ReadingQueue instance
    	ReadingQueue& reading_queue = ReadingQueue::getInstance();
		
		auto mail = reading_queue.mail_box.try_get_for(rtos::Kernel::Clock::duration_u32::max());
		if (mail) {

		    // Retrieve the message from the mail box
		    ReadingQueue::mail_t *reading_mail = mail;

			auto ch0_values = reading_mail->ch0;
			auto ch1_values = reading_mail->ch1;

			// Free the allocated mail to avoid memory leaks
			// make mail box empty
			reading_queue.mail_box.free(reading_mail); 
			
			// Access the serial mail sender
			SerialMailSender& serial_mail_sender = SerialMailSender::getInstance();

			// Send serial mail
			serial_mail_sender.sendMail(
				ch0_values,
				ch1_values,
				NODE
			);

		}
	}

	// main() is expected to loop forever.
	// If main() actually returns the processor will halt

	return 0;
}