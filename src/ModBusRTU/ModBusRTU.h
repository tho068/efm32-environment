/*
 * ModBusRTU.h
 *
 *  Created on: Apr 18, 2019
 *      Author: Thomas Holden
 */

#ifndef SRC_MODBUSRTU_MODBUSRTU_H_
#define SRC_MODBUSRTU_MODBUSRTU_H_

#define MODBUS_RTU_MAX_FRAME_SIZE 500

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "em_usart.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include "ModBusRTUFrame.h"

/* USART settings */
#define MODBUS_USART UART0
#define MODBUS_USART_RX 1
#define MODBUS_USART_TX 0
#define MODBUS_USART_PORT gpioPortE
#define MODBUS_USART_LOCATION (UART_ROUTE_RXPEN | UART_ROUTE_TXPEN | UART_ROUTE_LOCATION_LOC1)
#define MODBUS_USART_CLOCK cmuClock_UART0

#define MODBUS_USART_INIT_CONFIG                                                                   \
  {                                                                                                \
    usartDisable,          /* Enable RX/TX when initialization is complete. */                     \
    0,                     /* Use current configured reference clock for configuring baud rate. */ \
    19200,                 /* 115200 bits/s. */                                                    \
    usartOVS16,            /* 16x oversampling. */                                                 \
    usartDatabits8,        /* 8 data bits. */                                                      \
    usartNoParity,         /* No parity. */                                                        \
    usartStopbits1,        /* 1 stop bit. */                                                       \
    false,                 /* Do not disable majority vote. */                                     \
    false,                 /* Not USART PRS input mode. */                                         \
	usartPrsRxCh0,         /* PRS channel 0. */                                                    \
    false,                 /* Auto CS functionality enable/disable switch */                       \
  }

/* Timer settings */
#define MODBUS_TIMER TIMER0
#define MODBUS_TIMER_CLK cmuClock_TIMER0

enum {
	MODBUS_OK = -1,
	MODBUS_ERRPR = -2
};

class ModBusRTU {
public:
	ModBusRTU();
	void ModBusRTUTimerInit();
	int ModBusRTUTransmitFrame(uint8_t address, uint8_t function, uint8_t *data, uint32_t data_len);
	int ModBusRTUReceiveFrame(uint8_t *data);

private:
	USART_TypeDef *serial;
	TIMER_TypeDef *timer;

	ModBusRTUFrame modBusRTUFrame;
	int ModBusRTUSerialTX(uint8_t *frame, uint32_t frame_len);
};

#endif /* SRC_MODBUSRTU_MODBUSRTU_H_ */
