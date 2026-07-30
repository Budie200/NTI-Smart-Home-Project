#ifndef KEYPAD_H
#define KEYPAD_H

/*
Trying a different approach with this compared to the LCD.
Instead of defining the pins as values in a struct, which uses more memory 
but allows the user to use multiple lcds I will only allow one keypad at a time
with the upside of using less memory!
*/

#define KPD_Port 1

#define KPD_C1 0
#define KPD_C2 1
#define KPD_C3 2
#define KPD_C4 3

#define KPD_R1 4
#define KPD_R2 5
#define KPD_R3 6
#define KPD_R4 7

#define KPD_Unpressed 0xFF

void KPD_Init();
u8 KPD_GetPressedKey();

#endif
