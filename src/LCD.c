#include <util/delay.h>
#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"
#include "LCD.h"

void LCD_Pulse(LCD_Config *lcd){
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 1);
	_delay_us(2);
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 0);
	_delay_us(2);	
}

void LCD_SendCommand(LCD_Config *lcd, u8 command){
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rs, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rw, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 0);
	
	DIO_SetPortValue(lcd->DataPort, command);

	LCD_Pulse(lcd);
	
}

// allow options for init later
void LCD_Init(LCD_Config *lcd){
	_delay_ms(50);
	LCD_SendCommand(lcd, 0b00111000);
	_delay_us(40);
	LCD_SendCommand(lcd, 0b00111000);
	_delay_us(40);
	LCD_SendCommand(lcd, 0b00001111);
	_delay_us(40);
	LCD_SendCommand(lcd, 0b00000001);
	_delay_ms(2);
	LCD_SendCommand(lcd, 0b00000110);
}

void LCD_Char(LCD_Config *lcd, u8 letter){
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rs, 1);
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rw, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 0);

	DIO_SetPortValue(lcd->DataPort, letter);
	
	LCD_Pulse(lcd);
}

void LCD_String(LCD_Config *lcd, const u8* letters){
	for(u8 i = 0; letters[i] != '\0'; i++){
		LCD_Char(lcd, letters[i]);
	}
}

void LCD_Clear(LCD_Config *lcd){
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rs, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->Rw, 0);
	DIO_SetPinValue(lcd->CtrlPort, lcd->E, 0);

	DIO_SetPortValue(lcd->DataPort, 0b00000001);

	LCD_Pulse(lcd);
	_delay_ms(2);
}