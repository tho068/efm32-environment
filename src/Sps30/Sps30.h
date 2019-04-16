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

#include "timer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SPS_I2C_ADDRESS 0b1101001

enum {
	SPS_OK,
	SPS_ERROR
};

#define CRC8_POLYNOMIAL             0x31
#define CRC8_INIT                   0xFF
#define CRC8_LEN 1

#define SPS_MEASUREMENT_PAYLOAD_SIZE 59

#define SPS_CMD_START_MEASUREMENT       0x0010
#define SPS_CMD_START_MEASUREMENT_ARG   0x0300
#define SPS_CMD_STOP_MEASUREMENT        0x0104
#define SPS_CMD_READ_MEASUREMENT        0x0300
#define SPS_CMD_GET_DATA_READY          0x0202
#define SPS_CMD_AUTOCLEAN_INTERVAL      0x8004
#define SPS_CMD_GET_SERIAL              0xd033
#define SPS_CMD_RESET                   0xd304
#define SPS_WRITE_DELAY_US 20000

class Sps30 {
public:
	Sps30(I2C_TypeDef *i2c);
	I2C_TypeDef *i2c;
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

	void write(uint8_t *data, uint16_t len);
	void read(uint8_t *buf, uint16_t len);
	void sendCommand(uint16_t command, uint16_t arguments);
	void sendCommand(uint16_t command);
	uint16_t readRegister(uint16_t registerAddress);
	uint8_t crc(uint8_t *data, uint16_t count);
	bool dataReady();
};

#endif /* SRC_SPS30_SPS30_H_ */
