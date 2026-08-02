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

#define LDR_Channel 1

static bool mode_auto;

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
	case USART_CMD_MODE_AUTO:
		mode_auto = true;
		break;
	case USART_CMD_MODE_MANU:
		/* Turn everything off. */
		DIO_SetPortValue(LEDS_Port, LOW);
		DIO_SetPinValue(2, 0, LOW);
		DIO_SetPinValue(2, 1, LOW);
		mode_auto = false;
		break;
	case USART_CMD_LIVING_ON:
		DIO_SetPinValue(LEDS_Port, LivingRoomLight, HIGH);
		break;
	case USART_CMD_LIVING_OFF:
		DIO_SetPinValue(LEDS_Port, LivingRoomLight, LOW);
		break;
	case USART_CMD_BED_ON:
		DIO_SetPinValue(LEDS_Port, BedroomLight, HIGH);
		break;
	case USART_CMD_BED_OFF:
		DIO_SetPinValue(LEDS_Port, BedroomLight, LOW);
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
		s32 temperature;
		u16 light_level;

		if (!mode_auto) {
			Delay_ms(500);
			continue;
		}

		temperature = ADC_ReadTemperature();
		if(temperature > 30) {
			DIO_SetPinValue(2, 1, HIGH);
			DIO_SetPinValue(2, 0, LOW);
		} else {
			DIO_SetPinValue(2, 1, LOW);
			DIO_SetPinValue(2, 0, LOW);
		}

		light_level = ADC_Read(LDR_Channel);
		if(light_level < 100) {
			DIO_SetPinValue(LEDS_Port, LivingRoomLight, HIGH);
			DIO_SetPinValue(LEDS_Port, BedroomLight, HIGH);
		} else {
			DIO_SetPinValue(LEDS_Port, LivingRoomLight, LOW);
			DIO_SetPinValue(LEDS_Port, BedroomLight, LOW);
		}

		Delay_ms(500);
	}
}

