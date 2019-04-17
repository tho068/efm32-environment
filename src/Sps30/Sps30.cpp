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

Sps30::Sps30() {
	USART_InitAsync_TypeDef 		init = USART_INITASYNC_DEFAULT;
	uint8_t						response[SPS_USART_MAX_PAYLOAD] = {0};

	SysTick_Init();

	serial = USART1;

	init.baudrate = 115200;
	init.refFreq = 0;
	init.enable = usartDisable;

	// Enable clock for usart 1
	CMU_ClockEnable(cmuClock_USART1, true);

	USART_InitAsync(serial, &init);

	// Configure the GPIO lines
	GPIO_PinModeSet(gpioPortD, 1, gpioModeInput, false);
	GPIO_PinModeSet(gpioPortD, 0, gpioModePushPull, true);

	serial->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC1;

	USART_Enable(serial, usartEnable);

	sendCommand(SPS_CMD_RESET);
	readResponse(response);

	Delay(200);

	sendCommand(SPS_CMD_START_MEASUREMENT, SPS_CMD_START_MEASUREMENT_ARG);
	readResponse(response);

	Delay(200);

	while(readMeasurement() != true);
}

bool Sps30::readMeasurement() {
	uint8_t		data[SPS_MEASUREMENT_PAYLOAD_SIZE] = {0};
	uint32_t	tpm1, tpm25, tpm4, tpm10;
	uint32_t	tnpm05, tnpm1, tnpm25, tnpm4, tnpm10;
	uint32_t	ttps;

	uint32_t 	responseLength;

	sendCommand(SPS_CMD_READ_MEASUREMENT);
	responseLength = readResponse(data);

	if(responseLength <= 10) {
		return false;
	}

	tpm1 = (data[5] << 24 | data[6] << 16 | data[7] << 8 | data[8]);
	tpm25 = (data[9] << 24 | data[10] << 16 | data[11] << 8 | data[12]);
	tpm4 = (data[13] << 24 | data[14] << 16 | data[15] << 8 | data[16]);
	tpm10 = (data[17] << 24 | data[18] << 16 | data[19] << 8 | data[20]);

	tnpm05 = (data[21] << 24 | data[22] << 16 | data[23] << 8 | data[24]);
	tnpm1 = (data[25] << 24 | data[26] << 16 | data[27] << 8 | data[28]);
	tnpm25 = (data[29] << 24 | data[30] << 16 | data[31] << 8 | data[32]);
	tnpm4 = (data[33] << 24 | data[34] << 16 | data[35] << 8 | data[36]);
	tnpm10 = (data[37] << 24 | data[38] << 16 | data[39] << 8 | data[40]);

	ttps = (data[41] << 24 | data[42] << 16 | data[43] << 8 | data[44]);

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

uint32_t Sps30::byteStuffing(uint8_t *data, uint32_t currLength, uint8_t byte) {
	switch(byte) {
		case 0x7E:
			data[currLength] = 0x7D;
			data[++currLength] = 0x5E;
			return 2;
		case 0x7D:
			data[currLength] = 0x7D;
			data[++currLength] = 0x5D;
			return 2;
		case 0x11:
			data[currLength] = 0x7D;
			data[++currLength] = 0x31;
			return 2;
		case 0x13:
			data[currLength] = 0x7D;
			data[++currLength] = 0x33;
			return 2;
		default:
			data[currLength] = byte;
			return 1;
	}
}

uint32_t Sps30::readResponse(uint8_t *data){
	uint32_t 	len, newlen;
	uint8_t		tmp[SPS_USART_MAX_PAYLOAD];
	uint32_t	count = 0;

	len = read(data);
	newlen = 0;

	// Unshift bytes
	for(count = 0; count < len; count++) {
		if(data[count] == 0x7D) {
			switch(data[count + 1]){
			case 0x5E:
				tmp[newlen] = 0x7E;
				break;
			case 0x5D:
				tmp[newlen] = 0x7D;
				break;
			case 0x31:
				tmp[newlen] = 0x11;
				break;
			case 0x33:
				tmp[newlen] = 0x13;
				break;
			}
			count++;
		} else {
			tmp[newlen] = data[count];
		}

		newlen++;
	}

	// Write data back to response
	for(uint32_t i = 0; i < newlen; i++) {
		data[i] = tmp[i];
	}

	return newlen;
}

uint32_t Sps30::sendCommand(uint8_t command, uint16_t arguments) {
	uint8_t 		data[2], checksum;
	uint8_t 		cmd[SPS_USART_MAX_PAYLOAD] = {0};
	uint32_t 		len = 0;

	data[0] = arguments >> 8;
	data[1] = arguments & 0xFF;

	checksum = crc(0x0 + command, 2, data);

	// Start indication
	cmd[len++] = SPS_UART_START;

	// Address
	cmd[len++] = 0x00;

	// Command
	len += byteStuffing(cmd, len, command);

	// length
	cmd[len++] = 0x02;

	// Data
	len += byteStuffing(cmd, len, arguments >> 8);
	len += byteStuffing(cmd, len, arguments & 0xFF);

	// Checksum
	len += byteStuffing(cmd, len, checksum);

	// Stop
	cmd[len] = SPS_USART_END;

	write(cmd, len);

	return SPS_OK;
}

uint32_t Sps30::sendCommand(uint16_t command) {

	uint8_t 		checksum;
	uint8_t 		cmd[SPS_USART_MAX_PAYLOAD] = {0};
	uint32_t 		len = 0;

	checksum = crc(0x0 + command, 0, NULL);

	// Start indication
	cmd[len++] = SPS_UART_START;

	// Address
	cmd[len++] = 0x00;

	// Command
	len += byteStuffing(cmd, len, command);

	// length
	cmd[len++] = 0x00;

	// Checksum
	len += byteStuffing(cmd, len, checksum);

	// Stop
	cmd[len] = SPS_USART_END;

	write(cmd, len);

	return SPS_OK;

}

uint32_t Sps30::write(uint8_t *data, uint16_t len) {
	for(uint32_t i = 0; i <= len; i++) {
		USART_Tx(serial, data[i]);
	}

	return 1;
}

uint32_t Sps30::read(uint8_t *buf) {
	bool start = false;
	uint32_t length;

	for(length = 0; length < SPS_USART_MAX_PAYLOAD; length++) {
		buf[length] = USART_Rx(serial);

		if(start && buf[length] == SPS_USART_END) {
			break;
		}

		if(buf[length] == SPS_UART_START) {
			start = true;
		}
	}

	return ++length;
}

uint8_t Sps30::crc(uint8_t header_sum, uint8_t data_len, const uint8_t *data) {
    header_sum += data_len;

    while (data_len--)
        header_sum += *(data++);

    return ~header_sum;
}
