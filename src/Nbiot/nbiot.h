/*
 * nbiot.h
 *
 *  Created on: 10. apr. 2019
 *      Author: Thomas
 */

#ifndef SRC_NBIOT_H_
#define SRC_NBIOT_H_

#include "ATParser.h"

#include <string>

class nbiot {
public:
	ATParser modem;
	int fd;

	nbiot();
	void connect();
	bool is_connected();
	void configuration();
	void open_socket();
	void sendData(std::string payload);

};

#endif /* SRC_NBIOT_H_ */
