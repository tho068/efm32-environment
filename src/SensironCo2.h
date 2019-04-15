/*
 * SensironCo2.h
 *
 *  Created on: 12. apr. 2019
 *      Author: Thomas
 */

#ifndef SRC_SENSIRONCO2_H_
#define SRC_SENSIRONCO2_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "em_i2c.h"
#include "em_gpio.h"

#include "timer.h"

#define COMMAND_CONTINUOUS_MEASUREMENT 0x0010
#define COMMAND_SET_MEASUREMENT_INTERVAL 0x4600
#define COMMAND_GET_DATA_READY 0x0202
#define COMMAND_READ_MEASUREMENT 0x0300
#define COMMAND_AUTOMATIC_SELF_CALIBRATION 0x5306
#define COMMAND_SET_FORCED_RECALIBRATION_FACTOR 0x5204
#define COMMAND_SET_TEMPERATURE_OFFSET 0x5403
#define COMMAND_SET_ALTITUDE_COMPENSATION 0x5102

class SensironCo2 {
private:
	I2C_TypeDef *i2c;
	float temp;
	float hum;
	float co2;
	void write(uint8_t *data, uint16_t len);
	void read(uint8_t *buf, uint16_t len);
	void sendCommand(uint16_t command, uint16_t arguments);
	void sendCommand(uint16_t command);
	uint16_t readRegister(uint16_t registerAddress);
	uint8_t crc(uint8_t data[], uint8_t len);
	bool dataReady();
public:
	SensironCo2();
	void getMeasurement();
	float Temperature();
	float Humidity();
	float Co2();
};

#endif /* SRC_SENSIRONCO2_H_ */
