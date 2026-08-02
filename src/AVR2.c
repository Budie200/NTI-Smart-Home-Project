#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"
#include "ADC.h"
#include "Delay.h"
#include "USART.h"
#include "Interrupt.h"
#include "USART_Commands.h"

/* Loads on PORTC (port 3) - all pins output */
#define LEDS_Port         3
#define LivingRoomLight   0
#define BedroomLight      1
#define Fan                2

#define LDR_Channel 1

static INTR_FUNC(rx_rcv) {
	static struct {
		enum {
			CLOCKWISE,
			ANTI_CLOCKWISE
		} dir;
		bool on;
	} state;
	u8 val;

	DIO_SetPortDirection(2, OUTPUT);

	USART_Read(sizeof(u8), &val);
	switch (val) {
	case USART_CMD_FAN_ON:
		state.on = true;
		DIO_SetPinValue(2, state.dir == CLOCKWISE ? 1 : 0, HIGH);
		break;
	case USART_CMD_FAN_OFF:
		state.on = false;
		DIO_SetPinValue(2, 0, LOW);
		DIO_SetPinValue(2, 1, LOW);
		break;
	case USART_CMD_FAN_DIR_L:
		state.dir = CLOCKWISE;
		DIO_SetPinValue(2, 1, HIGH);
		DIO_SetPinValue(2, 0, LOW);
		break;
	case USART_CMD_FAN_DIR_R:
		state.dir = ANTI_CLOCKWISE;
		DIO_SetPinValue(2, 0, HIGH);
		DIO_SetPinValue(2, 1, LOW);
		break;
	}
}

int main(void){
	DIO_SetPortDirection(LEDS_Port, OUTPUT);
	DIO_SetPortValue(LEDS_Port, 0x00);   // all loads off at start

	Intr_Register(INTR_VEC_USART_RXC, rx_rcv);
	USART_Init(10, true, true, true);

	ADC_Init();

	set_bit(SREG, SREG_INTREN);
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

