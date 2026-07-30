#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"
#include "ADC.h"
#include "Delay.h"

/* Loads on PORTC (port 3) - all pins output */
#define LEDS_Port         3
#define LivingRoomLight   0
#define BedroomLight      1
#define Fan                2

#define LDR_Channel 1

int main(void){
	DIO_SetPortDirection(LEDS_Port, OUTPUT);
	DIO_SetPortValue(LEDS_Port, 0x00);   // all loads off at start

	ADC_Init();

	while(1){
		s32 temperature = ADC_ReadTemperature();
		u16 light_level = ADC_Read(LDR_Channel);

		if(temperature > 30)
			DIO_SetPinValue(LEDS_Port, Fan, HIGH);
		else
			DIO_SetPinValue(LEDS_Port, Fan, LOW);

		if(light_level < 300)
			DIO_SetPinValue(LEDS_Port, LivingRoomLight, HIGH);
		else
			DIO_SetPinValue(LEDS_Port, LivingRoomLight, LOW);

		Delay_ms(500);
	}
}

