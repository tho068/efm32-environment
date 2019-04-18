/*
 * ModBusRTUFrame.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: Thomas Holden
 */

#include "ModBusRTUFrame.h"

ModBusRTUFrame::ModBusRTUFrame() {

}

/*
 * Returns the length of the RTU frame written to the frame pointer. Caller is responsible for allocating memory for the frame.
 *
 * RTU frame: address, function code, data, crc
 */
uint32_t ModBusRTUFrame::ModBusRTUNewFrame(uint8_t *frame, uint8_t address, uint8_t functionCode, uint8_t *data, uint32_t data_len) {
	uint32_t	frameLength;
	uint16_t 	checksum;

	frameLength = 0;

	frame[frameLength] = address;
	frameLength++;

	frame[frameLength] = functionCode;
	frameLength++;

	for (uint32_t i = 0; i < data_len; i++) {
		frame[frameLength] = data[i];
		frameLength++;
	}

	checksum = crc(frame, frameLength);

	frame[frameLength] = checksum & 0xFF;
	frameLength++;

	frame[frameLength] = checksum >> 8;
	frameLength++;

	return frameLength;
}

/*
 * Returns the length of data from the given frame. Caller is responsible for allocating memory for the data
 */
uint32_t ModBusRTUFrame::ModBusRTUGetDataFromFrame(uint8_t *data, uint8_t *frame, uint32_t frame_length) {

}

uint16_t ModBusRTUFrame::crc(uint8_t *buf, uint32_t len){
	  uint16_t crc = 0xFFFF;

	  for (uint32_t pos = 0; pos < len; pos++) {
	    crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc

	    for (int i = 8; i != 0; i--) {    // Loop over each bit
	      if ((crc & 0x0001) != 0) {      // If the LSB is set
	        crc >>= 1;                    // Shift right and XOR 0xA001
	        crc ^= 0xA001;
	      }
	      else                            // Else LSB is not set
	        crc >>= 1;                    // Just shift right
	    }
	  }
	  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
	  return crc;

}
