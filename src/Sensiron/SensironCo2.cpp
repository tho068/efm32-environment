/*
 * SensironCo2.cpp
 *
 *  Created on: 12. apr. 2019
 *      Author: Thomas
 */

#include "SensironCo2.h"

float SensironCo2::Temperature() {
	return temp;
}
float SensironCo2::Humidity() {
	return hum;
}
float SensironCo2::Co2(){
	return co2;
}

int SensironCo2::StartMeasurement(){
	uint8_t			data[4];
	uint8_t			response[MODBUS_RTU_MAX_FRAME_SIZE];

	data[0] = SCD_CMD_CONTINUOUS_MEASUREMENT_ADDRESS_MSB;
	data[1] = SCD_CMD_CONTINUOUS_MEASUREMENT_ADDRESS_LSB;
	data[2] = SCD_CMD_CONTINUOUS_MEASUREMENT_DATA_MSB;
	data[3] = SCD_CMD_CONTINUOUS_MEASUREMENT_DATA_LSB;

	modBusRTU.ModBusRTUTransmitFrame(SCD30_MODBUS_ADDRESS, 0x06, data, 4);
	modBusRTU.ModBusRTUReceiveFrame(response);

	return 1;
}

uint16_t SensironCo2::DataReady() {
	uint8_t payload[4];
	uint8_t response[MODBUS_RTU_MAX_FRAME_SIZE];

	payload[0] = SCD_CMD_DATA_READY_ADDRESS_MSB;
	payload[1] = SCD_CMD_DATA_READY_ADDRESS_LSB;
	payload[2] = SCD_CMD_DATA_READY_DATA_MSB;
	payload[3] = SCD_CMD_DATA_READY_DATA_LSB;

	modBusRTU.ModBusRTUTransmitFrame(SCD30_MODBUS_ADDRESS, 0x03, payload, 4);
	modBusRTU.ModBusRTUReceiveFrame(response);

	return ((uint16_t)response[1] << 8 | response[2]);
}

int SensironCo2::ReadMeasurements() {
	uint8_t			data[4];
	uint8_t			response[MODBUS_RTU_MAX_FRAME_SIZE] = {0};

	uint32_t 		tempCO2 = 0;
	uint32_t 		tempHumidity = 0;
	uint32_t 		tempTemperature = 0;

	if(DataReady() != 1) {
		// Handle error
		return 0;
	}

	data[0] = SCD_CMD_GET_MEASUREMENT_ADDRESS_MSB;
	data[1] = SCD_CMD_GET_MEASUREMENT_ADDRESS_LSB;
	data[2] = SCD_CMD_GET_MEASUREMENT_DATA_MSB;
	data[3] = SCD_CMD_GET_MEASUREMENT_DATA_LSB;

	modBusRTU.ModBusRTUTransmitFrame(SCD30_MODBUS_ADDRESS, 0x03, data, 4);
	int res_len = modBusRTU.ModBusRTUReceiveFrame(response);

	tempCO2 = (response[1] << 24 | response[2] << 16 | response[3] << 8 | response[4]);
	tempTemperature = (response[5] << 24 | response[6] << 16 | response[7] << 8 | response[8]);
    tempHumidity = (response[9] << 24 | response[10] << 16 | response[11] << 8 | response[12]);

	memcpy(&co2, &tempCO2, sizeof(co2));
	memcpy(&temp, &tempTemperature, sizeof(temp));
	memcpy(&hum, &tempHumidity, sizeof(hum));

	return 1;
}

SensironCo2::SensironCo2() {
	StartMeasurement();
	while(ReadMeasurements() != 1);
}
