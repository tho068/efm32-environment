/*
 * ModBusRTUFrame.h
 *
 *  Created on: Apr 18, 2019
 *      Author: Thomas Holden
 */

#ifndef SRC_MODBUSRTU_MODBUSRTUFRAME_H_
#define SRC_MODBUSRTU_MODBUSRTUFRAME_H_

#define MODBUS_RTU_MAX_FRAME_SIZE 500

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

class ModBusRTUFrame {
public:
	ModBusRTUFrame();
	uint32_t ModBusRTUNewFrame(uint8_t *frame, uint8_t address, uint8_t functionCode, uint8_t *data, uint32_t data_len);
	uint32_t ModBusRTUGetDataFromFrame(uint8_t *data, uint8_t *frame, uint32_t frame_length);
	uint16_t crc(uint8_t *frame, uint32_t frame_length);
};

#endif /* SRC_MODBUSRTU_MODBUSRTUFRAME_H_ */
