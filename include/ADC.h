#ifndef ADC_H
#define ADC_H

#include "EmbVars.h"

void ADC_Init(void);

/* Returns a raw 10-bit reading (0-1023) from the given ADC channel (0-7) */
u16 ADC_Read(u8 channel);

/* LM35 on ADC0: 10mV per degree C, Vref = 5000mV, resolution = 1024 steps */
s32 ADC_ReadTemperature(void);

#endif
