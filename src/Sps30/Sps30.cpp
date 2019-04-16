/*
 * Sps30.cpp
 *
 *  Created on: 16. apr. 2019
 *      Author: Thomas
 */

#include "Sps30.h"

float Sps30::PM10(){
	return pm10;
}

float Sps30::PM25(){
	return pm25;
}

float Sps30::PM4(){
	return pm4;
}

float Sps30::PM1() {
	return pm1;
}

float Sps30::TPS(){
	return tps;
}

Sps30::Sps30(I2C_TypeDef *interface) {
	i2c = interface;

	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	CMU_ClockEnable(cmuClock_I2C1, true);

	init.enable = true;
	init.master = true;

	GPIO_PinModeSet(gpioPortC, 5, gpioModeWiredAndDrivePullUpFilter, 1);
	GPIO_PinModeSet(gpioPortC, 4, gpioModeWiredAndDrivePullUpFilter, 1);

	i2c->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN | I2C_ROUTE_LOCATION_LOC0;

	I2C_Init(i2c, &init);

	Delay(1000);

	// Reset device
	sendCommand(SPS_CMD_RESET);

	Delay(250);

	// Start sampling
	sendCommand(SPS_CMD_START_MEASUREMENT, SPS_CMD_START_MEASUREMENT_ARG);

	Delay(250);

	// Get atleast a single OK measurement
	while (readMeasurement() != true);
}

bool Sps30::readMeasurement() {
	uint8_t		data[SPS_MEASUREMENT_PAYLOAD_SIZE];
	uint32_t	tpm1, tpm25, tpm4, tpm10;
	uint32_t	tnpm05, tnpm1, tnpm25, tnpm4, tnpm10;
	uint32_t	ttps;

	if(dataReady() != true) {
		return false;
	}

	Delay(250);

	sendCommand(SPS_CMD_READ_MEASUREMENT);

	Delay(250);

	read(data, SPS_MEASUREMENT_PAYLOAD_SIZE);

	tpm1 = (data[0] << 24 | data[1] << 16 | data[3] << 8 | data[4]);
	tpm25 = (data[6] << 24 | data[7] << 16 | data[9] << 8 | data[10]);
	tpm4 = (data[12] << 24 | data[13] << 16 | data[15] << 8 | data[16]);
	tpm10 = (data[18] << 24 | data[19] << 16 | data[21] << 8 | data[22]);

	tnpm05 = (data[24] << 24 | data[25] << 16 | data[27] << 8 | data[28]);
	tnpm1 = (data[30] << 24 | data[31] << 16 | data[33] << 8 | data[34]);
	tnpm25 = (data[36] << 24 | data[37] << 16 | data[39] << 8 | data[40]);
	tnpm4 = (data[42] << 24 | data[43] << 16 | data[45] << 8 | data[46]);
	tnpm10 = (data[48] << 24 | data[49] << 16 | data[51] << 8 | data[52]);

	ttps = (data[54] << 24 | data[55] << 16 | data[57] << 8 | data[58]);

	memcpy(&pm1, &tpm1, sizeof(pm1));
	memcpy(&pm25, &tpm25, sizeof(pm25));
	memcpy(&pm4, &tpm4, sizeof(pm4));
	memcpy(&pm10, &tpm10, sizeof(pm10));

	memcpy(&npm05, &tnpm05, sizeof(npm05));
	memcpy(&npm1, &tnpm1, sizeof(npm1));
	memcpy(&npm25, &tnpm25, sizeof(npm25));
	memcpy(&npm4, &tnpm4, sizeof(npm4));
	memcpy(&npm10, &tnpm10, sizeof(npm10));

	memcpy(&tps, &ttps, sizeof(npm10));

	return true;
}

bool Sps30::dataReady() {
	uint16_t rc = readRegister(SPS_CMD_GET_DATA_READY);
	if(rc == 1) {
		return true;
	}

	return false;
}

void Sps30::sendCommand(uint16_t command, uint16_t arguments) {
	uint8_t data[2], checksum;
	uint8_t cmd[5];

	data[0] = arguments >> 8;
	data[1] = arguments & 0xFF;

	checksum = crc(data, 2);

	cmd[0] = command >> 8;
	cmd[1] = command & 0xFF;

	cmd[2] = arguments >> 8;
	cmd[3] = arguments & 0xFF;

	cmd[4] = checksum;

	write(cmd, 5);
}

void Sps30::sendCommand(uint16_t command) {

	uint8_t cmd[2];

	cmd[0] = command >> 8;
	cmd[1] = command & 0xFF;

	write(cmd, 2);

}

uint16_t Sps30::readRegister(uint16_t registerAddress) {
	sendCommand(registerAddress);

	uint8_t tmp[2] = {0};

	read(tmp, 2);

	return ((uint16_t)tmp[0] << 8 | tmp[1]);
}

void Sps30::write(uint8_t *data, uint16_t len) {
	I2C_TransferSeq_TypeDef init;
	I2C_TransferReturn_TypeDef rc;

	init.addr = 0b11010010;
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

void Sps30::read(uint8_t *buf, uint16_t len) {
	I2C_TransferSeq_TypeDef init;
	I2C_TransferReturn_TypeDef rc;

	init.addr = 0b11010011;
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

uint8_t Sps30::crc(uint8_t *data, uint16_t count) {
    uint16_t current_byte;
    uint8_t crc = CRC8_INIT;
    uint8_t crc_bit;

    /* calculates 8-Bit checksum with given polynomial */
    for (current_byte = 0; current_byte < count; ++current_byte) {
        crc ^= (data[current_byte]);
        for (crc_bit = 8; crc_bit > 0; --crc_bit) {
            if (crc & 0x80)
                crc = (crc << 1) ^ CRC8_POLYNOMIAL;
            else
                crc = (crc << 1);
        }
    }

    return crc;
}
