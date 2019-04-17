/*
 * Sps30.h
 *
 *  Created on: 16. apr. 2019
 *      Author: Thomas
 */

#ifndef SRC_SPS30_SPS30_H_
#define SRC_SPS30_SPS30_H_

#include "em_i2c.h"
#include "em_gpio.h"
#include "em_usart.h"

#include "timer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SPS_I2C_ADDRESS 0b1101001

enum {
	SPS_OK = -1,
	SPS_ERROR = -2
};

#define CRC8_POLYNOMIAL             0x31
#define CRC8_INIT                   0xFF
#define CRC8_LEN 1

#define SPS_USART_END 0x7E
#define SPS_UART_START 0x7E
#define SPS_USART_MAX_PAYLOAD 256

#define SPS_MEASUREMENT_PAYLOAD_SIZE 59

#define SPS_CMD_START_MEASUREMENT       0x00
#define SPS_CMD_START_MEASUREMENT_ARG   0x0103
#define SPS_CMD_STOP_MEASUREMENT        0x0104
#define SPS_CMD_READ_MEASUREMENT        0x03
#define SPS_CMD_GET_DATA_READY          0x0202
#define SPS_CMD_AUTOCLEAN_INTERVAL      0x8004
#define SPS_CMD_GET_SERIAL              0xd033
#define SPS_CMD_RESET                   0xD3
#define SPS_WRITE_DELAY_US 20000

class Sps30 {
public:
	Sps30();
	USART_TypeDef *serial;
	bool readMeasurement();
	float PM1();
	float PM25();
	float PM4();
	float PM10();
	float TPS();
private:
	float pm1, pm25, pm4, pm10;
	float npm05, npm1, npm25, npm4, npm10;
	float tps;

	uint32_t byteUnstuffing(uint8_t *data, uint32_t currLength, uint8_t byte);
	uint32_t byteStuffing(uint8_t *data, uint32_t currLength, uint8_t byte);
	uint32_t write(uint8_t *data, uint16_t len);
	uint32_t read(uint8_t *buf);
	uint32_t readResponse(uint8_t *data);
	uint32_t sendCommand(uint8_t command, uint16_t arguments);
	uint32_t sendCommand(uint16_t command);
	uint16_t readRegister(uint16_t registerAddress);
	uint8_t crc(uint8_t header_sum, uint8_t data_len, const uint8_t *data);
	bool dataReady();
};

#endif /* SRC_SPS30_SPS30_H_ */
