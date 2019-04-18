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
#include "ModBusRTU.h"

#define SCD30_MODBUS_ADDRESS 0x61

// Trigger measurements
#define SCD_CMD_CONTINUOUS_MEASUREMENT_ADDRESS_MSB 0x00
#define SCD_CMD_CONTINUOUS_MEASUREMENT_ADDRESS_LSB 0x36

#define SCD_CMD_CONTINUOUS_MEASUREMENT_DATA_MSB 0x00
#define SCD_CMD_CONTINUOUS_MEASUREMENT_DATA_LSB 0x00

// Data ready
#define SCD_CMD_DATA_READY_ADDRESS_MSB 0x00
#define SCD_CMD_DATA_READY_ADDRESS_LSB 0x27
#define SCD_CMD_DATA_READY_DATA_MSB 0x00
#define SCD_CMD_DATA_READY_DATA_LSB 0x01

// Get measurement
#define SCD_CMD_GET_MEASUREMENT_ADDRESS_MSB 0x00
#define SCD_CMD_GET_MEASUREMENT_ADDRESS_LSB 0x28
#define SCD_CMD_GET_MEASUREMENT_DATA_MSB 0x00
#define SCD_CMD_GET_MEASUREMENT_DATA_LSB 0x06

class SensironCo2 {
private:
	float temp;
	float hum;
	float co2;

	ModBusRTU modBusRTU;

	uint16_t DataReady();
	int StartMeasurement();

public:
	SensironCo2();
	int ReadMeasurements();
	float Temperature();
	float Humidity();
	float Co2();
};

#endif /* SRC_SENSIRONCO2_H_ */
