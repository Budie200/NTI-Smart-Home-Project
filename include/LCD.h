#ifndef LCD_H
#define LCD_H
#include "EmbVars.h"

typedef struct{
    u8 DataPort;
    u8 CtrlPort;
    u8 Rs;
    u8 Rw;
    u8 E;
} LCD_Config;

void LCD_Pulse(LCD_Config *lcd);
void LCD_SendCommand(LCD_Config *lcd , u8 command);
void LCD_Init(LCD_Config *lcd); // allow options for init later
void LCD_Char(LCD_Config *lcd, u8 letter);
void LCD_String(LCD_Config *lcd, const u8* letters);
void LCD_Clear(LCD_Config *lcd);

#endif