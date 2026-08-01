#include "EmbVars.h"
#include "Keypad.h"
#include "LCD.h"
#include "Menu.h"
#include "Timer.h"
#include "USART.h"

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
    const u8 correct_password[5] = "1234";
    u8 entered_password[5];

	u8 i = 0;
	u8 key;

	LCD_Clear(lcd);
	LCD_String(lcd, (const u8*)"Enter Password:");
	LCD_SendCommand(lcd, LCD_CMD_SETDDRAMADDR(0x40)); // jump to line 2

	while(i < 4){
		key = GetKey_Blocking();

		/* only accept digit keys 0-9, ignore + - * / = C */
		if(key >= '0' && key <= '9'){
			entered_password[i] = key;
			LCD_Char(lcd, '*');
			i++;
		}
	}

	for(i = 0; i < 4; i++){
		if(entered_password[i] != correct_password[i])
			return 0;
	}
	return 1;
}


void Menu_Password(LCD_Config* lcd){
u8 attemps = 0;
for(; attemps < 4; attemps++){
    if(Check_Password()){
        LCD_Clear(lcd);
		LCD_String(lcd, (const u8*)"ACCESS GRANTED");
        break;
    }
    else{
		LCD_Clear(lcd);
		LCD_String(lcd, (const u8*)"Wrong Password");
		LCD_SendCommand(lcd, LCD_CMD_SETDDRAMADDR(0x40));
		LCD_String(lcd, (const u8*)"Try Again");   
    }
}
if(attemps >= 3){
    LCD_Clear(lcd);
	LCD_String(lcd, (const u8*)"ACCESS DENIED");

	Buzzer_On();
    Delay_ms(200);
    Buzzer_Off();
    
    u32 initial_time = Timer_GetSeconds();
    while(Timer_GetSeconds() < initial_time + 30){
        u8 timer = 30 - (Timer_GetSeconds() - initial_time);

        LCD_Clear();
        LCD_String(lcd, (const u8*) "Wait: ")
        LCD_String(lcd, LCD_s64_to_str(timer));
        Delay_ms(100);
        
    }
    Menu_Password(lcd);
}
}

void Menu_Loop(LCD_Config* lcd){
    LCD_Clear();
    LCD_String(lcd, Menu_LoopString);
    Delay_ms(100);

    u8 pressed = KPD_GetPressedKey();
    switch (pressed)
    {
    case '1':
        Menu_State = MANUAL;
        break;
    case '2':
        Menu_State = AUTOMATIC;
        break;
    default:
        Menu_State = LOOP;
        break;

    }

    switch(Menu_State){
        case MANUAL: Menu_Manual(lcd); break;
        case AUTOMATIC: Menu_Automatic(lcd); break;
    }
}
