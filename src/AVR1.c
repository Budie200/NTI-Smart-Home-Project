#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"
#include "Keypad.h"
#include "LCD.h"
#include "Buzzer.h"
#include "Delay.h"
#include "Interrupt.h"

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
/*EXTERNAL INTERRUPT& DOORBELL ALERT*/
static void Doorbell_ISR(void) {
    LCD_Clear(&lcd);
    LCD_String(&lcd, (const u8*)"DOORBELL RANG!");// Display Doorbell alert message on LCD
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

/* KPD_GetPressedKey only does ONE scan pass, so we poll it
   until an actual key comes back (not KPD_Unpressed) */
u8 GetKey_Blocking(void){
	u8 key;
	do{
		key = KPD_GetPressedKey();
	} while(key == KPD_Unpressed);
	return key;
}

/* Reads 4 digits from the keypad, shows '*' on the LCD for each one,
   returns 1 if it matches the password, 0 otherwise */
u8 Check_Password(void){
	u8 i = 0;
	u8 key;

	LCD_Clear(&lcd);
	LCD_String(&lcd, (const u8*)"Enter Password:");
	LCD_SendCommand(&lcd, 0xC0);   // jump to line 2

	while(i < 4){
		key = GetKey_Blocking();

		/* only accept digit keys 0-9, ignore + - * / = C */
		if(key >= '0' && key <= '9'){
			entered_password[i] = key;
			LCD_Char(&lcd, '*');
			i++;
		}
	}
	entered_password[4] = '\0';

	for(i = 0; i < 4; i++){
		if(entered_password[i] != correct_password[i])
			return 0;
	}
	return 1;
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

	Doorbell_Interrupt_Init();

	LCD_String(&lcd, (const u8*)"Smart Home Sys");

	Delay_ms(1500);

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



