#include "EmbVars.h"
#include "bitwise_ops.h"
#include "ADC.h"
#include "DIO.h"

void ADC_Init(void){
	DIO_SetPortDirection(1, 0); // PORTA all input - analog sensors
	DIO_SetPortValue(1, 0); // no pull-ups on analog pins

	ADMUX = bit(ADMUX_REFS0); // AVCC as voltage reference

	ADCSRA = bit(ADCSRA_ADEN) | bit(ADCSRA_ADPS1) | bit(ADCSRA_ADPS0);
}

u16 ADC_Read(u8 channel){
	ADMUX = (ADMUX & 0xE0) | (channel & 0x1F);	// select channel
	set_bit(ADCSRA, ADCSRA_ADSC);			// start conversion
	while(get_bit(ADCSRA, ADCSRA_ADSC));		// wait until done
	return ADCH;
}

s32 ADC_ReadTemperature(void){
	u16 adc_val = ADC_Read(0);                    // LM35 -> PA0
	s32 temp_mv = ((s32)adc_val * 5000) / 1024;    // convert to millivolts
	return temp_mv / 10;                           // 10mV per degree C
}
