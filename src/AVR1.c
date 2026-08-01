#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"
#include "Keypad.h"
#include "LCD.h"
#include "Buzzer.h"
#include "Delay.h"
#include "Menu.h"

/* ---------------------------------------------------------------
   LCD wiring:
   Data bus (8-bit)  -> PORTB (port 2)   [Keypad already owns PORTA]
   Control (RS,RW,E) -> PORTD (port 4), pins 0,1,2
   --------------------------------------------------------------- */
#define LCD_DataPort 2
#define LCD_CtrlPort 4
#define LCD_RS_Pin   0
#define LCD_RW_Pin   1
#define LCD_E_Pin    2

static const LCD_Config lcd = {
	.DataPort = LCD_DataPort,
	.CtrlPort = LCD_CtrlPort,
	.Rs = LCD_RS_Pin,
	.Rw = LCD_RW_Pin,
	.E  = LCD_E_Pin
};

static const u8 correct_password[5] = "1234";
static u8 entered_password[5];
static u8 wrong_attempts = 0;


int main(void){
	/* LCD_Init() does NOT set pin directions itself, so we must
	   configure the data port and control pins as OUTPUT first */
	DIO_SetPortDirection(LCD_DataPort, OUTPUT);
	DIO_SetPinDirection(LCD_CtrlPort, LCD_RS_Pin, OUTPUT);
	DIO_SetPinDirection(LCD_CtrlPort, LCD_RW_Pin, OUTPUT);
	DIO_SetPinDirection(LCD_CtrlPort, LCD_E_Pin,  OUTPUT);

	KPD_Init();
	Buzzer_Init();
	Timer_init(void); 
	Menu_init(&lcd);
	
	while(1){
		if(Check_Password()){
			LCD_Clear(&lcd);
			LCD_String(&lcd, (const u8*)"ACCESS GRANTED");
			wrong_attempts = 0;
			Delay_ms(2000);

			/* team can hook the appliance-control menu in here */
		}
		else{
			wrong_attempts++;

			if(wrong_attempts >= 3){
				LCD_Clear(&lcd);
				LCD_String(&lcd, (const u8*)"ACCESS DENIED");
				Buzzer_On();
				wrong_attempts = 0;
				Delay_ms(1000);
			}
			else{
				LCD_Clear(&lcd);
				LCD_String(&lcd, (const u8*)"Wrong Password");
				LCD_SendCommand(&lcd, 0xC0);
				LCD_String(&lcd, (const u8*)"Try Again");
				Delay_ms(1500);
			}
		}
	}
}



