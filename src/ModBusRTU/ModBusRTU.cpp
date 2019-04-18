/*
 * ModBusRTU.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: Thomas Holden
 */

#include "ModBusRTU.h"

#define DEBUG 0

ModBusRTU::ModBusRTU() {
	USART_InitAsync_TypeDef init = MODBUS_USART_INIT_CONFIG;

	serial = MODBUS_USART;
	timer = MODBUS_TIMER;

	CMU_ClockEnable(MODBUS_USART_CLOCK, true);
	CMU_ClockEnable(MODBUS_TIMER_CLK, true);

	USART_InitAsync(serial, &init);

	GPIO_PinModeSet(MODBUS_USART_PORT, MODBUS_USART_RX, gpioModeInput, false);
	GPIO_PinModeSet(MODBUS_USART_PORT, MODBUS_USART_TX, gpioModePushPull, true);

	serial->ROUTE = MODBUS_USART_LOCATION;

	USART_Enable(serial, usartEnable);

	ModBusRTUTimerInit();
}

void ModBusRTU::ModBusRTUTimerInit() {
	TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;

	init.enable = false;
	init.oneShot = false;
	init.mode = timerModeUp;
	init.prescale = timerPrescale2;
	init.clkSel = timerClkSelHFPerClk;

	TIMER_Init(timer, &init);
}

int ModBusRTU::ModBusRTUTransmitFrame(uint8_t address, uint8_t function, uint8_t *data, uint32_t data_len) {
	uint8_t			frame[MODBUS_RTU_MAX_FRAME_SIZE] = {0};
	uint32_t 		frame_length;
	int 			rc;

	// Create modbus frame and append the CRC
	frame_length = modBusRTUFrame.ModBusRTUNewFrame(frame, address, function, data, data_len);

	rc = ModBusRTUSerialTX(frame, frame_length);
	if (rc != MODBUS_OK) {
		// Handle error
		return MODBUS_ERRPR;
	}

	return MODBUS_OK;
}

int ModBusRTU::ModBusRTUReceiveFrame(uint8_t *data) {
	uint8_t 		frame[MODBUS_RTU_MAX_FRAME_SIZE] = {0};
	uint32_t 		frame_length;
	uint16_t		checksumMsb, checksumLsb, checksum;
	uint16_t		calculatedChecksum;
	bool			started, success;

	frame_length = 0;
	started = false;
	success = false;

	timer->CNT = 0;

	while(true){
		if (serial->STATUS & USART_STATUS_RXDATAV) {
			if (started == false) {
				TIMER_Enable(timer, true);
				timer->CNT = 0;
				started = true;
			}
			else {
				if ((timer->CNT) < 14000) {
					timer->CNT = 0;
				}
				/*else if ((timer->CNT * 8) > 750 && (timer->CNT * 8) < 1750) {
					// RTU standard says to discard the message
					success = false;
					break;
				}*/
			}

			frame[frame_length] = serial->RXDATA;
			frame_length++;
		}
		else {
			if(started && (timer->CNT) > 14000) {
				success = true;
				break;
			}
		}
	}

	TIMER_Enable(timer, false);

	checksumMsb = frame[frame_length - 1];
	checksumLsb = frame[frame_length - 2];

	checksum = (checksumMsb << 8 | checksumLsb);
	calculatedChecksum = modBusRTUFrame.crc(frame, frame_length - 2);

	if(checksum != calculatedChecksum) {
		success = false;
		printf("Checksum not a match \n");
	}

	if(success && frame_length > 4) {
		if(DEBUG) {
			printf("Incoming: ");

			for(uint32_t i = 0; i < frame_length; i++)  {
				printf("%x ", frame[i]);
			}

			printf("\n");
		}

		for (uint32_t i = 2; i < frame_length - 2; i++) {
			data[i-2] = frame[i];
		}

		return frame_length - 4;
	}
	else {
		return MODBUS_ERRPR;
	}
}

int ModBusRTU::ModBusRTUSerialTX(uint8_t *frame, uint32_t frame_len){
	for(uint32_t i = 0; i < frame_len; i++) {
		USART_Tx(serial, frame[i]);
	}

	if (DEBUG) {
		printf("Outgoing: ");

		for(uint32_t i = 0; i < frame_len; i++) {
			printf("%x ", frame[i]);
		}

		printf("\n");
	}

	return MODBUS_OK;
}
