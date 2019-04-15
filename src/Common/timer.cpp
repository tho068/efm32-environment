/*
 * timer.cpp
 *
 *  Created on: 10. apr. 2019
 *      Author: Thomas
 */

#include "timer.h"

#define DEBUG_BREAK           __asm__("BKPT #0");

/* Counts 1ms timeTicks */
volatile uint32_t msTicks = 0;

void Delay(uint32_t dlyTicks)
{
      uint32_t curTicks;

      curTicks = msTicks;
      while ((msTicks - curTicks) < dlyTicks) ;
}

void SysTick_Handler(void)
{
      msTicks++;
}

void SysTick_Init()
{
    if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000))
    {
          DEBUG_BREAK;
    }
}

uint32_t SysTick_GetTicks()
{
	return msTicks;
}
