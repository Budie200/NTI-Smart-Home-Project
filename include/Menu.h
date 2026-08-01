#ifndef MENU_H
#define MENU_H

enum Menu_State{
    LOOP, MANUAL, AUTOMATIC
} Menu_State;

void Menu_init(LCD_Config* lcd);
void Menu_Password(LCD_Config* lcd);

void Menu_Manual(LCD_Config* lcd);
void Menu_Automatic(LCD_Config* lcd);
void Menu_Status(LCD_Config* lcd);

void Menu_Loop(LCD_Config* lcd);

#define Menu_LoopString (const u8*) "M: 1, A: 2" 
#define Menu_StatusString (const u8*) "F, L, T, Ls; B:-"


#endif