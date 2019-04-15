/*
 * NovaSensor.cpp
 *
 *  Created on: 10. apr. 2019
 *      Author: Thomas
 */

#include "NovaSensor.h"

NovaSensor::NovaSensor() {
	USART_InitAsync_TypeDef init;
	this->usart = USART1;

	CMU_ClockEnable(cmuClock_USART1, true);

	usart = USART1;
	init = USART_INITASYNC_DEFAULT;

	init.baudrate = 9600;
	init.refFreq = 0;
	init.enable = usartDisable;

	USART_InitAsync(this->usart, &init);

	this->usart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC1;

	GPIO_PinModeSet(gpioPortD, 0, gpioModePushPull, 1);
	GPIO_PinModeSet(gpioPortD, 1, gpioModeInput, 0);

	USART_Enable(this->usart, usartEnable);
}

int NovaSensor::Read(float *pm10, float *pm25) {
	uint8_t buffer;
	int value;
	int len = 0;
	int pm10_serial = 0;
	int pm25_serial = 0;
	int checksum_is;
	int checksum_ok = 0;
	while (len < 10) {
		buffer = USART_Rx(this->usart);
		value = int(buffer);

		switch (len) {
			case (0): if (value != 170) { len = -1; }; break;
			case (1): if (value != 192) { len = -1; }; break;
			case (2): pm25_serial = value; checksum_is = value; break;
			case (3): pm25_serial += (value << 8); checksum_is += value; break;
			case (4): pm10_serial = value; checksum_is += value; break;
			case (5): pm10_serial += (value << 8); checksum_is += value; break;
			case (6): checksum_is += value; break;
			case (7): checksum_is += value; break;
			case (8): if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
			case (9): if (value != 171) { len = -1; }; break;
		}

		len++;

		if (len == 10 && checksum_ok == 1) {
			*pm10 = (float)pm10_serial/10.0;
			*pm25 = (float)pm25_serial/10.0;
			return NOVA_SENSOR_OK;
		}
	}
	return NOVA_SENSOR_ERROR;
}
