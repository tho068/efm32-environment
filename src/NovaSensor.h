/*
 * NovaSensor.h
 *
 *  Created on: 10. apr. 2019
 *      Author: Thomas
 */

#ifndef SRC_NOVASENSOR_H_
#define SRC_NOVASENSOR_H_

#include "em_usart.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include <stdlib.h>
#include <stdio.h>

enum {
	NOVA_SENSOR_OK,
	NOVA_SENSOR_ERROR
};

class NovaSensor {
public:
	USART_TypeDef *usart;

	NovaSensor();
	int Read(float *pm10, float *pm25);
};

#endif /* SRC_NOVASENSOR_H_ */
