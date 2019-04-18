#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>

#include "retargetswo.h"

#include "Sps30.h"
#include "ATParser.h"
#include "SensironCo2.h"
#include "timer.h"
#include "nbiot.h"

static void EnableClocks() {
	CMU_ClockEnable( cmuClock_CORELE, true );
	CMU_ClockEnable( cmuClock_HF, true );
	CMU_ClockEnable( cmuClock_HFPER, true);
	CMU_ClockEnable( cmuClock_HFLE, true);;
	CMU_ClockEnable( cmuClock_LFB, true );


	// Enable Crystal Oscillators
	CMU_OscillatorEnable( cmuOsc_HFXO, true, true );
	CMU_OscillatorEnable( cmuOsc_LFXO, true, true );

	// Select HFXO and LFXO crystals for HF and LFB clock branch
	CMU_ClockSelectSet( cmuClock_HF, cmuSelect_HFXO );
	CMU_ClockSelectSet( cmuClock_HFPER, cmuSelect_HFXO );
	CMU_ClockSelectSet( cmuClock_LFB, cmuSelect_LFXO );

	// Divide HFPER clock by four
	CMU_ClockDivSet(cmuClock_HFPER, cmuClkDiv_4);

	// Enable clock for GPIO and Leuart
	CMU_ClockEnable( cmuClock_GPIO, true );
	CMU_ClockEnable( cmuClock_LEUART0, true );
}

int main(void)
 {
	CHIP_Init();
	RETARGET_SwoInit();
	EnableClocks();
	SysTick_Init();

	SensironCo2 	co2Sensor;
	Sps30			pm;
	nbiot 			nb;

	float 			ppm10, ppm25, ppco2;
	float			dpm10, dpm25, dco2;
	uint32_t		previousTime, currentTime;

	char 			payload[500];

	previousTime = SysTick_GetTicks();
	currentTime = SysTick_GetTicks();

	while (true) {
		pm.readMeasurement();
		co2Sensor.ReadMeasurements();

		dpm10 = abs(pm.PM10() - ppm10);
		dpm25 = abs(pm.PM25() - ppm25);
		dco2 = abs(co2Sensor.Co2() - ppco2);

		// Increase of 120 %
		if (((dpm10 / ppm10) * 100 > 120) || ((dpm25 / ppm25) * 100 > 120) || (dco2 / ppco2) * 100 > 120) {
			snprintf(payload, 500, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f", pm.PM1(), pm.PM25(), pm.PM4(), pm.PM10(), pm.TPS(), co2Sensor.Co2(), co2Sensor.Humidity(), co2Sensor.Temperature());

			nb.sendData(payload);

			previousTime = SysTick_GetTicks();
			currentTime = previousTime;
		}

		// Time to transmit measurement reached
		if (600000 < currentTime - previousTime) {
			snprintf(payload, 500, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f", pm.PM1(), pm.PM25(), pm.PM4(), pm.PM10(), pm.TPS(), co2Sensor.Co2(), co2Sensor.Humidity(), co2Sensor.Temperature());

			nb.sendData(payload);

			previousTime = SysTick_GetTicks();
			currentTime = previousTime;
		}

		ppm10 = pm.PM10();
		ppm25 = pm.PM25();
		ppco2 = co2Sensor.Co2();

		currentTime = SysTick_GetTicks();

		printf("PM25: %f, PM10: %f, C02: %f, RH: %f, Temp: %f \n", pm.PM25(), pm.PM10(), co2Sensor.Co2(), co2Sensor.Humidity(), co2Sensor.Temperature());

		Delay(1000);
	}
}
