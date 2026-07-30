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

void LCD_Pulse(const LCD_Config *lcd);
void LCD_SendCommand(const LCD_Config *lcd , u8 command);
void LCD_Init(const LCD_Config *lcd); // allow options for init later
void LCD_Char(const LCD_Config *lcd, u8 letter);
void LCD_String(const LCD_Config *lcd, const u8* letters);
void LCD_Clear(const LCD_Config *lcd);

#endif
