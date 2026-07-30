#include "EmbVars.h"
#include "bitwise_ops.h"
#include <avr/io.h>
#include "ADC.h"

void ADC_Init(void){
	DDRA  = 0x00;    // PORTA all input - analog sensors
	PORTA = 0x00;    // no pull-ups on analog pins

	ADMUX  = (1 << REFS0);   // AVCC as voltage reference

	ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);
}

u16 ADC_Read(u8 channel){
	ADMUX = (ADMUX & 0xE0) | (channel & 0x1F);   // select channel
	ADCSRA |= (1 << ADSC);                       // start conversion
	while(ADCSRA & (1 << ADSC));                 // wait until done
	return ADC;
}

s32 ADC_ReadTemperature(void){
	u16 adc_val = ADC_Read(0);                    // LM35 -> PA0
	s32 temp_mv = ((s32)adc_val * 5000) / 1024;    // convert to millivolts
	return temp_mv / 10;                           // 10mV per degree C
}
