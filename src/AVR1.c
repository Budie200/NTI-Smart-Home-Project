#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"
#include "Keypad.h"
#include "LCD.h"
#include "Buzzer.h"
#include "Delay.h"
#include "Menu.h"
#include "Timer.h"
#include "Interrupt.h"

/* ---------------------------------------------------------------
   LCD wiring:
   Data bus (8-bit)  -> PORTB (port 2)   [Keypad already owns PORTA]
   Control (RS,RW,E) -> PORTD (port 4), pins 0,1,2
   --------------------------------------------------------------- */
#define LCD_DataPort 3
#define LCD_CtrlPort 4
#define LCD_RS_Pin   5
#define LCD_RW_Pin   6
#define LCD_E_Pin    7

static const LCD_Config lcd = {
	.DataPort = LCD_DataPort,
	.CtrlPort = LCD_CtrlPort,
	.Rs = LCD_RS_Pin,
	.Rw = LCD_RW_Pin,
	.E  = LCD_E_Pin
};

/*EXTERNAL INTERRUPT& DOORBELL ALERT*/
static void Doorbell_ISR(void) {
    LCD_Clear(&lcd);
    LCD_String(&lcd, (const u8*)"DOORBELL RANG!"); // Display Doorbell alert message on LCD
    Buzzer_On();
    Delay_ms(1000);
    Buzzer_Off();
}

void Doorbell_Interrupt_Init(void) {
    DIO_SetPinDirection(4, 2, INPUT); // Port D (4), Pin 2 as input with internal Pull-Up Resistor
    DIO_SetPinValue(4, 2, HIGH); // Enable Internal Pull-Up

    set_bit(MCUCR, 1);
    clr_bit(MCUCR, 0);

    set_bit(GICR, 6);

    Intr_Register(INTR_VEC_INT0, Doorbell_ISR);

    set_bit(SREG, 7);
}

int main(void){
	/* LCD_Init() does NOT set pin directions itself, so we must
	   configure the data port and control pins as OUTPUT first */
	DIO_SetPortDirection(LCD_DataPort, OUTPUT);
	DIO_SetPinDirection(LCD_CtrlPort, LCD_RS_Pin, OUTPUT);
	DIO_SetPinDirection(LCD_CtrlPort, LCD_RW_Pin, OUTPUT);
	DIO_SetPinDirection(LCD_CtrlPort, LCD_E_Pin,  OUTPUT);

	LCD_Init(&lcd);
	KPD_Init();
	Buzzer_Init();
	Timer_Init();
	Menu_init(&lcd);

	Doorbell_Interrupt_Init();

	while(1){

	}
}
