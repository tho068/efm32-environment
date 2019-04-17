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

SensironCo2::SensironCo2() {
	i2c = I2C0;

	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	CMU_ClockEnable(cmuClock_I2C0, true);

	init.enable = true;
	init.master = true;

	GPIO_PinModeSet(gpioPortD, 6, gpioModeWiredAndPullUpFilter, 1);
	GPIO_PinModeSet(gpioPortD, 7, gpioModeWiredAndPullUpFilter, 1);

	i2c->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN | I2C_ROUTE_LOCATION_LOC1;

	I2C_Init(i2c, &init);

	hum = 0;
	temp = 0;
	co2 = 0;

	// Set sensor measurement interval 2 second
	sendCommand(COMMAND_SET_MEASUREMENT_INTERVAL, 2);

	Delay(200);

	// Start measurements
	sendCommand(COMMAND_CONTINUOUS_MEASUREMENT, 0);

	Delay(4000);

	getMeasurement();
}

void SensironCo2::getMeasurement() {
	uint8_t		incoming[18];
	uint32_t 	tempCO2 = 0;
	uint32_t 	tempHumidity = 0;
	uint32_t 	tempTemperature = 0;
	uint8_t		payload[2];

	if(dataReady() == false) {
		return;
	}

	payload[0] = COMMAND_READ_MEASUREMENT >> 8;
	payload[1] = COMMAND_READ_MEASUREMENT & 0xFF;

	write(payload, 2);
	Delay(200);
	read(incoming, 18);

	tempCO2 = (incoming[0] << 24 | incoming[1] << 16 | incoming[3] << 8 | incoming[4]);
	tempHumidity = (incoming[12] << 24 | incoming[13] << 16 | incoming[15] << 8 | incoming[16]);
	tempTemperature = (incoming[6] << 24 | incoming[7] << 16 | incoming[9] << 8 | incoming[10]);

	memcpy(&co2, &tempCO2, sizeof(co2));
	memcpy(&temp, &tempTemperature, sizeof(temp));
	memcpy(&hum, &tempHumidity, sizeof(hum));
}

bool SensironCo2::dataReady() {
	uint16_t rc = readRegister(COMMAND_GET_DATA_READY);
	if(rc == 1) {
		return true;
	}

	return false;
}

void SensironCo2::sendCommand(uint16_t command, uint16_t arguments) {
	uint8_t data[2], checksum;
	uint8_t cmd[5];

	checksum = crc(data, 2);

	cmd[0] = command >> 8;
	cmd[1] = command & 0xFF;

	cmd[2] = arguments >> 8;
	cmd[3] = arguments & 0xFF;

	cmd[4] = checksum;

	write(cmd, 5);

	Delay(200);
}

void SensironCo2::sendCommand(uint16_t command) {

	uint8_t cmd[2];

	cmd[0] = command >> 8;
	cmd[1] = command & 0xFF;

	write(cmd, 2);

	Delay(200);
}

uint16_t SensironCo2::readRegister(uint16_t registerAddress) {
	sendCommand(registerAddress);

	uint8_t tmp[2] = {0};

	read(tmp, 2);

	Delay(200);

	return ((uint16_t)tmp[0] << 8 | tmp[1]);
}

void SensironCo2::write(uint8_t *data, uint16_t len) {
	I2C_TransferSeq_TypeDef init;
	I2C_TransferReturn_TypeDef rc;

	init.addr = 0b11000010;
	init.flags = I2C_FLAG_WRITE;
	init.buf[0].data = data;
	init.buf[0].len = len;

	// Start the transfer
	rc = I2C_TransferInit(i2c, &init);

	while(rc == i2cTransferInProgress){
		rc = I2C_Transfer(i2c);
		switch(rc) {
		case i2cTransferArbLost: {
			printf("arb lost \n");
			break;
		}
		case i2cTransferBusErr: {
			printf("bus err \n");
			break;
		}
		case i2cTransferDone: {
			break;
		}
		case i2cTransferInProgress: {
			break;
		}
		case i2cTransferNack: {
			printf("nack \n");
			break;
		}
		case i2cTransferSwFault: {
			printf("sw fault \n");
			break;
		}
		case i2cTransferUsageFault: {
			printf("usage fault \n");
			break;
		}
		}
	}
}

void SensironCo2::read(uint8_t *buf, uint16_t len) {
	I2C_TransferSeq_TypeDef init;
	I2C_TransferReturn_TypeDef rc;

	init.addr = 0b11000011;
	init.flags = I2C_FLAG_READ;
	init.buf[0].data = buf;
	init.buf[0].len = len;

	rc = I2C_TransferInit(i2c, &init);

	while(rc == i2cTransferInProgress){
		rc = I2C_Transfer(i2c);
		switch(rc) {
			case i2cTransferArbLost: {
				printf("arb lost \n");
				break;
			}
			case i2cTransferBusErr: {
				printf("bus err \n");
				break;
			}
			case i2cTransferDone: {
				break;
			}
			case i2cTransferInProgress: {
				break;
			}
			case i2cTransferNack: {
				printf("nack \n");
				break;
			}
			case i2cTransferSwFault: {
				printf("sw fault \n");
				break;
			}
			case i2cTransferUsageFault: {
				printf("usage fault \n");
				break;
			}
		}
	}
}

uint8_t SensironCo2::crc(uint8_t data[], uint8_t len) {
  uint8_t crc = 0xFF; //Init with 0xFF

  for (uint8_t x = 0 ; x < len ; x++)
  {
    crc ^= data[x]; // XOR-in the next input byte

    for (uint8_t i = 0 ; i < 8 ; i++)
    {
      if ((crc & 0x80) != 0)
        crc = (uint8_t)((crc << 1) ^ 0x31);
      else
        crc <<= 1;
    }
  }

  return crc; //No output reflection
}
