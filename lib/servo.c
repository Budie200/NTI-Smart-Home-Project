#include "EmbVars.h"
#include "bitwise_ops.h"
#include <avr/io.h>
#include "Servo.h"

#define SERVO_ICR_TOP   2499
#define SERVO_MIN_OCR   125    // 1.0 ms pulse -> 0 degrees
#define SERVO_MAX_OCR   250    // 2.0 ms pulse -> 180 degrees

void Servo_Init(void){
	DDRD |= (1 << PD5);   // OC1A pin as output

	ICR1 = SERVO_ICR_TOP;

	// Fast PWM, TOP = ICR1 (WGM13:0 = 1110), non-inverting output on OC1A
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);   // prescaler = 8

	Servo_Lock();   // door starts locked
}

void Servo_SetAngle(u8 angle){
	if(angle > 180) angle = 180;

	u16 ocr_val = SERVO_MIN_OCR +
	              ((u32)(SERVO_MAX_OCR - SERVO_MIN_OCR) * angle) / 180;

	OCR1A = ocr_val;
}

void Servo_Lock(void){
	Servo_SetAngle(0);
}

void Servo_Unlock(void){
	Servo_SetAngle(90);
}
