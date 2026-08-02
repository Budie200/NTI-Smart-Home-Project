#ifndef ADC_H
#define ADC_H

#define ADCL	(*(volatile u8 *)0x24)

#define ADCH	(*(volatile u8 *)0x25)

#define ADCSRA	(*(volatile u8 *)0x26)
#define ADCSRA_ADPS0	0
#define ADCSRA_ADPS1	1
#define ADCSRA_ADSC	6
#define ADCSRA_ADEN	7

#define ADMUX	(*(volatile u8 *)0x27)
#define ADMUX_ADLAR	5
#define ADMUX_REFS0	6

void ADC_Init(void);

/* Returns a raw 10-bit reading (0-1023) from the given ADC channel (0-7) */
u16 ADC_Read(u8 channel);

/* LM35 on ADC0: 10mV per degree C, Vref = 5000mV, resolution = 1024 steps */
s32 ADC_ReadTemperature(void);

#endif
