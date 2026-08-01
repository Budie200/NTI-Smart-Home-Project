#ifndef MENU_H
#define MENU_H

void Menu_init(LCD_Config* lcd);
void Menu_Password(LCD_Config* lcd);

void Menu_Status(LCD_Config* lcd);

void Menu_Loop(LCD_Config* lcd);

#define Menu_LoopString (const u8*) "M: 1, A: 2" 
#define Menu_StatusString (const u8*) "F, L, T, Ls; B:-"


#endif
