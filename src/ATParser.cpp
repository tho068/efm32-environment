/*
 * ATParser.cpp
 *
 *  Created on: 10. apr. 2019
 *      Author: Thomas
 */

#include "ATParser.h"

#define debug_on 1

ATParser::ATParser() {
	LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;

	serial = LEUART0;

	SysTick_Init();

	CMU_ClockEnable(cmuClock_LEUART0, true);

	init.baudrate = AT_BAUD;
	init.refFreq = 0;
	init.enable = leuartDisable;

	LEUART_Init(serial, &init);

	GPIO_PinModeSet(gpioPortD, AT_RXD_PIN, gpioModeInput, false);
	GPIO_PinModeSet(gpioPortD, AT_TXD_PIN, gpioModePushPull, true);

	serial->ROUTE = LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN | LEUART_ROUTE_LOCATION_LOC0;

	LEUART_Enable(serial, leuartEnable);
}

uint8_t ATParser::getc(int *rc) {
	uint32_t start = SysTick_GetTicks();
	uint32_t current = SysTick_GetTicks();

	while (true) {
		if (serial->STATUS & LEUART_STATUS_RXDATAV) {
			*rc = AT_OK;
			return (uint8_t)serial->RXDATA;
		}

		if (AT_TIMEOUT < current - start) {
			*rc = AT_TIMEOUT_ERROR;
			return AT_ERROR;
		}

		current = SysTick_GetTicks();
	}
}

int ATParser::putc(char c) {
	LEUART_Tx(serial, c);
	return AT_OK;
}

std::vector<std::string> ATParser::split(std::string s, std::string delimiter) {
	std::vector<std::string> res;

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
	    token = s.substr(0, pos);
	    res.push_back(token);
	    s.erase(0, pos + delimiter.length());
	}

	return res;
}

int ATParser::send(std::string command) {
	for(uint32_t i = 0; i < command.length(); i++) {
		int rc = putc(command[i]);

		if (rc == AT_TIMEOUT_ERROR) {
			printf("AT Timeout \n");
			return AT_TIMEOUT_ERROR;
		}
	}

	if(debug_on) {
		printf("%s\n", command.c_str());
	}

	putc('\r');
	putc('\n');

	return AT_OK;
}

bool ATParser::recv(std::string response, ...) {
	bool 				error, timeout = false;
	int 				rc;
	std::string 		actualResponse = "";
	uint8_t 			rx;
	size_t				num_occurances;

	va_list				args;
	va_start(args, response);

	while (true) {
		rx = getc(&rc);

		if (rc == AT_TIMEOUT_ERROR) {
			timeout = true;
			break;
		}

		actualResponse += rx;

		if (strstr(actualResponse.c_str(), (char*)"OK") != NULL) {
			error = false;
			break;
		}

		if (strstr(actualResponse.c_str(), (char*)"ERROR") != NULL) {
			error = true;
			break;
		}
	}

	if (debug_on) {
		printf("%s \n", actualResponse.c_str());

		if (timeout) {
			printf("AT Timeout \n");
		}

		if (error) {
			printf("AT error \n");
		}
	}

	if (timeout || error) {
		return false;
	}

	num_occurances = std::count(response.begin(), response.end(), '%');

	if (num_occurances > 0) {
		std::vector<std::string> responses = split(actualResponse, "\r\n");

		for(uint32_t i = 0; i < responses.size(); i++) {
			size_t found = vsscanf(responses[i].c_str(), response.c_str(), args);
			if (found == num_occurances	) {
				va_end(args);
				return true;
			}
		}
	}
	else {
		if (strstr(actualResponse.c_str(), response.c_str()) != NULL) {
			va_end(args);
			return true;
		}
	}

	va_end(args);
	return false;
}
