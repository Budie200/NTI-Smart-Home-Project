#ifndef SERVO_H
#define SERVO_H

#include "EmbVars.h"

void Servo_Lock(void);     // 0 degrees  -> door locked
void Servo_Unlock(void);   // 90 degrees -> door open

#endif
