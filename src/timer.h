/*
 * timer.h
 *
 *  Created on: 10. apr. 2019
 *      Author: Thomas
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include "em_cmu.h"

void Delay(uint32_t dlyTicks);
void SysTick_Init();
uint32_t SysTick_GetTicks();

#endif /* SRC_TIMER_H_ */
