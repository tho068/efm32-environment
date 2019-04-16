/*
 * nbiot.cpp
 *
 *  Created on: 10. apr. 2019
 *      Author: Thomas Holden
 */

#include "nbiot.h"

nbiot::nbiot() {
	// Restart modem upon startup
	modem.send("AT+NRB");
	Delay(5000);

	configuration();

	connect();

	while(!is_connected()) {
		Delay(2000);
	}

	Delay(1000);

	modem.send("AT+CGACT=1,1");
	modem.recv("OK");

	Delay(1000);

	open_socket();
}

void nbiot::configuration(){
	modem.send("AT+CFUN=1");
	modem.recv("OK");

	Delay(1000);

	modem.send("AT+CGDCONT=1,\"IP\",\"mda.ee\"");
	modem.recv("OK");

	Delay(1000);
}

void nbiot::connect() {
	modem.send("AT+COPS=1,2,\"24201\"");
	modem.recv("OK");

	Delay(1000);
}

bool nbiot::is_connected(){
	modem.send("AT+CEREG?");
	if (modem.recv("+CEREG: 0,1") == true) {
		return true;
	}

	return false;
}

void nbiot::open_socket(){
	modem.send("AT+NSOCR=\"DGRAM\",17,8888,1");
	modem.recv("%d", &fd);

	Delay(1000);
}

void nbiot::sendData(std::string payload) {
	unsigned int 		len, ufd;
	char 				data[500] = {0}, hex[500] = {0};
	const char 			*originial;

	originial = payload.c_str();
	len = payload.size();

	for (unsigned int i = 0, j = 0; i < len; ++i, j += 2){
		sprintf(hex + j, "%02x", originial[i] & 0xff);
	}

	snprintf(data, 500, "AT+NSOST=%d,\"%s\",%d,%d,\"%s\"", fd, "172.16.15.14", 1234, payload.size(), hex);

	while(true) {
		modem.send(data);
		int rc = modem.recv("%d,%d", &ufd, &len);
		if(rc){
			return;
		}
		Delay(1000);
	}

	printf("Transmitted %d bytes using socket %d \n", len, ufd);
}



