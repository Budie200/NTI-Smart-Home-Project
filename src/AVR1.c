#include "EmbVars.h"
#include "DIO.h"
#include "Keypad.h"
#include "LCD.h"
#include "Delay.h"
#include "Buzzer.h"

int main(void)
{
    LCD_Config lcd;

    u8 key;

    u8 password[5] = {'1', '2', '3', '4', '\0'};

    u8 enteredPassword[5];

    u8 attempts = 0;

    u8 i;


    // ================= LCD CONFIGURATION =================

    lcd.DataPort = 2;
    lcd.CtrlPort = 4;

    lcd.Rs = 0;
    lcd.Rw = 1;
    lcd.E  = 2;


    // ================= INITIALIZATION =================

    KPD_Init();

    Buzzer_Init();

    LCD_Init(&lcd);


    // ================= MAIN LOOP =================

    while(1)
    {
        LCD_Clear(&lcd);

        LCD_String(&lcd, "Enter Password");

        LCD_SendCommand(&lcd, 0b11000000);


        // ================= READ PASSWORD =================

        for(i = 0; i < 4; i++)
        {
            do
            {
                key = KPD_GetPressedKey();

            } while(key == KPD_Unpressed);


            enteredPassword[i] = key;

            LCD_Char(&lcd, '*');
        }

        enteredPassword[4] = '\0';


        // ================= CHECK PASSWORD =================

        if(enteredPassword[0] == password[0] &&
           enteredPassword[1] == password[1] &&
           enteredPassword[2] == password[2] &&
           enteredPassword[3] == password[3])
        {
            LCD_Clear(&lcd);

            LCD_String(&lcd, "ACCESS GRANTED");

            attempts = 0;

            Delay_ms(2000);
        }

        else
        {
            attempts++;

            LCD_Clear(&lcd);

            LCD_String(&lcd, "WRONG PASSWORD");

            Delay_ms(1500);


            // ================= 3 WRONG ATTEMPTS =================

            if(attempts >= 3)
            {
                LCD_Clear(&lcd);

                LCD_String(&lcd, "ACCESS DENIED");

                Buzzer_On();

                Delay_ms(5000);

                Buzzer_Off();

                attempts = 0;
            }
        }
    }
}
