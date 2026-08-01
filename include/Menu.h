#ifndef MENU_H
#define MENU_H

typedef enum{
    INIT, PASSWORD, MODE, STATUS
} Menu_State;

void Menu_init(LCD_Config* lcd);
void Menu_Password(LCD_Config* lcd);
void Menu_Loop(LCD_Config* lcd);

#endif