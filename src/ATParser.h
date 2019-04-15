/*
 * ATParser.h
 *
 *  Created on: 10. apr. 2019
 *      Author: Thomas
 */

#ifndef SRC_ATPARSER_H_
#define SRC_ATPARSER_H_

#include "em_usart.h"
#include "em_gpio.h"
#include "em_leuart.h"

#include <string>
#include <string.h>
#include <stdarg.h>
#include <algorithm>
#include <vector>

#include "timer.h"

#define AT_BAUD 9600
#define AT_RXD_PIN 5
#define AT_TXD_PIN 4
#define AT_GPIO_PORT gpioPortB
#define AT_TIMEOUT 6000

enum {
	AT_OK = 0,
	AT_TIMEOUT_ERROR = -1,
	AT_ERROR = -2
};

class ATParser {
public:
	ATParser();
	int send(std::string command);
	bool recv(std::string response, ...);

private:
	LEUART_TypeDef 	*serial;
	uint8_t getc(int *rc);
	int putc(char c);
	std::vector<std::string> split(std::string s, std::string delim);
};

#endif /* SRC_ATPARSER_H_ */
