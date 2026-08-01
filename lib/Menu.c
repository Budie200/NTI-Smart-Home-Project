#include "EmbVars.h"
#include "Keypad.h"
#include "LCD.h"
#include "Menu.h"
#include "Timer.h"

void Menu_init(LCD_Config* lcd){
    LCD_String(lcd, (const u8*)"Smart Home Sys");
	while(Timer_GetSeconds(void) < 2);
    LCD_Clear(lcd);
}

/* KPD_GetPressedKey only does ONE scan pass, so we poll it
   until an actual key comes back (not KPD_Unpressed) */
static u8 GetKey_Blocking(void){
	u8 key;
	do{
		key = KPD_GetPressedKey();
	} while(key == KPD_Unpressed);
	return key;
}

/* Reads 4 digits from the keypad, shows '*' on the LCD for each one,
   returns 1 if it matches the password, 0 otherwise */
static u8 Check_Password(LCD_Config* lcd){
	u8 i = 0;
	u8 key;

	LCD_Clear(lcd);
	LCD_String(lcd, (const u8*)"Enter Password:");
	LCD_SendCommand(lcd, 0xC0);   // jump to line 2

	while(i < 4){
		key = GetKey_Blocking();

		/* only accept digit keys 0-9, ignore + - * / = C */
		if(key >= '0' && key <= '9'){
			entered_password[i] = key;
			LCD_Char(lcd, '*');
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

void Menu_Password(LCD_Config* lcd){

}
