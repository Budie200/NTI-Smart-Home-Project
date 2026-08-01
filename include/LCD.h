#ifndef LCD_H
#define LCD_H

#define LCD_CMD_CLEARSCREEN			0b00000001
#define LCD_CMD_RETURNHOME			0b00000010
/* direction (d) and shift (s) */
#define LCD_CMD_ENTRYMODE(d, s)			(0b00000100 | (((d) ? 1 : 0) << 1) | ((s) ? 1 : 0))
/* display (d), cursor (c), and blinking of cursor (b) */
#define LCD_CMD_DISPLAYCTRL(d, c, b)		(0b00001000 | (((d) ? 1 : 0) << 2) | (((c) ? 1 : 0) << 1) | ((b) ? 1 : 0))
/* interface data length (l), display rows (n), and font type (f) */
#define LCD_CMD_FUNCSET(l, n, f)		(0b00100000 | (((l) ? 1 : 0) << 4) | (((n) ? 1 : 0) << 3) | (((f) ? 1 : 0) << 2))
/* set CGRAM address in counter */
#define LCD_CMD_SETCGRAMADDR(a)			(0b01000000 | ((a) & 0x3f))
/* set DDRAM address in counter */
#define LCD_CMD_SETDDRAMADDR(a)			(0b10000000 | ((a) & 0x7f))

#define LCD_WIDTH 16

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
const u8 *LCD_s64_to_str(s64 val);

#endif
