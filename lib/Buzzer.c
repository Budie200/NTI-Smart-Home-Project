#include "EmbVars.h"
#include "DIO.h"
#include "Buzzer.h"

void Buzzer_Init(void)
{
    DIO_SetPinDirection(BUZZER_Port, BUZZER_Pin, OUTPUT);

    Buzzer_Off();
}

void Buzzer_On(void)
{
    DIO_SetPinValue(BUZZER_Port, BUZZER_Pin, HIGH);
}

void Buzzer_Off(void)
{
    DIO_SetPinValue(BUZZER_Port, BUZZER_Pin, LOW);
}
