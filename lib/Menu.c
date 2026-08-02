#include "EmbVars.h"
#include "Keypad.h"
#include "LCD.h"
#include "Menu.h"
#include "Timer.h"
#include "USART.h"
#include "Buzzer.h"
#include "Delay.h"
#include "USART.h"
#include "USART_Commands.h"

static enum Menu_State{
    LOOP, MANUAL, AUTOMATIC
} Menu_State;

void Menu_init(LCD_Config* lcd){
    LCD_String(lcd, (const u8*)"Smart Home Sys");
    while(Timer_GetSeconds() < 2)
	    Delay_us(100); /* So GCC doesn't optimize this out. */
    LCD_Clear(lcd);
}

/* KPD_GetPressedKey only does ONE scan pass, so we poll it
   until an actual key comes back (not KPD_Unpressed) */
static u8 GetKey_Blocking(void){
	u8 key;
	do{
		key = KPD_GetPressedKey();
		Delay_ms(20);
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
    if(Check_Password(lcd)){
        LCD_Clear(lcd);
		LCD_String(lcd, (const u8*)"ACCESS GRANTED");
        break;
    }
    else{
		for (u32 c, s = Timer_GetSeconds(); (c = Timer_GetSeconds()) - s < 3;) {
			LCD_Clear(lcd);
			LCD_String(lcd, (const u8*)"Wrong Password");
			LCD_SendCommand(lcd, LCD_CMD_SETDDRAMADDR(0x40));
			LCD_String(lcd, (const u8*)"Try Again (");
			LCD_String(lcd, LCD_s64_to_str(3 - (c - s)));
			LCD_Char(lcd, ')');

			Delay_ms(1000);
		}
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

        LCD_Clear(lcd);
        LCD_String(lcd, (const u8*) "Wait: ");
        LCD_String(lcd, LCD_s64_to_str(timer));
        Delay_ms(100);
        
    }
    Menu_Password(lcd);
}
}

static void Menu_Automatic(LCD_Config *lcd) {
	USART_Write(sizeof(u8),
	    &(u8){USART_CMD_MODE_AUTO});

	/* Nothing to show, just go back. */
	Menu_State = LOOP;
}

static void Menu_Manual(LCD_Config *lcd) {
	u8 data;

	LCD_Clear(lcd);
	LCD_String(lcd, "1: pwr 2: dir");
	LCD_SendCommand(lcd, LCD_CMD_SETDDRAMADDR(0x40));
	LCD_String(lcd, "3: back 4: light");
	switch (GetKey_Blocking()) {
	case '1':
		goto fan_pwr;
	case '2':
		goto fan_dir;
	case '3':
		Menu_State = LOOP;
		return;
	case '4':
		goto lights;
	default:
		return (Menu_Manual(lcd));
	}

fan_pwr:
	LCD_Clear(lcd);
	LCD_String(lcd, "1: on");
	LCD_SendCommand(lcd, LCD_CMD_SETDDRAMADDR(0x40));
	LCD_String(lcd, "2: off");
	switch (GetKey_Blocking()) {
	case '1':
		USART_Write(sizeof(u8),
		    &(u8){USART_CMD_FAN_ON});
		break;
	case '2':
		USART_Write(sizeof(u8),
		    &(u8){USART_CMD_FAN_OFF});
		break;
	default:
		goto fan_pwr;
	}

	return;
fan_dir:
	LCD_Clear(lcd);
	LCD_String(lcd, "1: clockwise");
	LCD_SendCommand(lcd, LCD_CMD_SETDDRAMADDR(0x40));
	LCD_String(lcd, "2: anticlockwise");
	switch (GetKey_Blocking()) {
	case '1':
		USART_Write(sizeof(u8),
		    &(u8){USART_CMD_FAN_DIR_L});
		break;
	case '2':
		USART_Write(sizeof(u8),
		    &(u8){USART_CMD_FAN_DIR_R});
		break;
	default:
		goto fan_dir;
	}

	return;
lights:
	enum {
		LIVINGROOM,
		BEDROOM
	} lightselect;

	LCD_Clear(lcd);
	LCD_String(lcd, "1: living light");
	LCD_SendCommand(lcd, LCD_CMD_SETDDRAMADDR(0x40));
	LCD_String(lcd, "2: bedroom light");
	switch (GetKey_Blocking()) {
	case '1':
		lightselect = LIVINGROOM;
		break;
	case '2':
		lightselect = BEDROOM;
		break;
	default:
		goto lights;
	}

lights_onoff:
	LCD_Clear(lcd);
	LCD_String(lcd, "1: on");
	LCD_SendCommand(lcd, LCD_CMD_SETDDRAMADDR(0x40));
	LCD_String(lcd, "2: off");
	switch (GetKey_Blocking()) {
	case '1':
		USART_Write(sizeof(u8),
		    &(u8){lightselect == LIVINGROOM ?
		        USART_CMD_LIVING_ON : USART_CMD_BED_ON});
		break;
	case '2':
		USART_Write(sizeof(u8),
		    &(u8){lightselect == LIVINGROOM ?
		        USART_CMD_LIVING_OFF : USART_CMD_BED_OFF});
		break;
	default:
		goto lights_onoff;
	}
}

void Menu_Loop(LCD_Config* lcd){
    Delay_ms(100);

    u8 pressed = GetKey_Blocking();
    switch (pressed)
    {
    case '1':
	/* Tell the other AVR we want manual mode. */
	USART_Write(sizeof(u8),
	    &(u8){USART_CMD_MODE_MANU});
        Menu_State = MANUAL;
        break;
    case '2':
        Menu_State = AUTOMATIC;
        break;
    default:
        //Menu_State = LOOP;
        break;

    }

    switch(Menu_State){
        case MANUAL: Menu_Manual(lcd); break;
        case AUTOMATIC: Menu_Automatic(lcd); break;
	default:
        LCD_Clear(lcd);
        LCD_String(lcd, Menu_LoopString);
    }
}
