#ifndef BUZZER_H
#define BUZZER_H

#include "EmbVars.h"

#define BUZZER_Port 3
#define BUZZER_Pin  0

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);

#endif
