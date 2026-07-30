#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"
#include "LCD.h"
#include "Delay.h"

void LCD_Pulse(const LCD_Config *lcd){
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 1);
	Delay_us(2);
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 0);
	Delay_us(2);
}

void LCD_SendCommand(const LCD_Config *lcd, u8 command){
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rs, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rw, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 0);
	
	DIO_SetPortValue(lcd->DataPort, command);

	LCD_Pulse(lcd);
	
}

// allow options for init later
void LCD_Init(const LCD_Config *lcd){
	Delay_ms(50);
	LCD_SendCommand(lcd, 0b00111000);
	Delay_us(40);
	LCD_SendCommand(lcd, 0b00111000);
	Delay_us(40);
	LCD_SendCommand(lcd, 0b00001111);
	Delay_us(40);
	LCD_SendCommand(lcd, 0b00000001);
	Delay_ms(2);
	LCD_SendCommand(lcd, 0b00000110);
}

void LCD_Char(const LCD_Config *lcd, u8 letter){
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rs, 1);
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rw, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 0);

	DIO_SetPortValue(lcd->DataPort, letter);
	
	LCD_Pulse(lcd);
}

void LCD_String(const LCD_Config *lcd, const u8* letters){
	for(u8 i = 0; letters[i] != '\0'; i++){
		LCD_Char(lcd, letters[i]);
	}
}

void LCD_Clear(const LCD_Config *lcd){
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rs, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rw, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 0);

	DIO_SetPortValue(lcd->DataPort, 0b00000001);

	LCD_Pulse(lcd);
	Delay_ms(2);
}
