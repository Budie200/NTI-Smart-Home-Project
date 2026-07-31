#include "EmbVars.h"
#include "DIO.h"
#include "bitwise_ops.h"
#include "Timer.h"
#include "Interrupt.h"

static u32 seconds_passed = 0;

INTR_FUNC(func){
    static u8 Timer_OverflowCount = 0; 

    Timer_OverflowCount++;
    if(Timer_OverflowCount >= 4){
        Timer_OverflowCount = 0;
        seconds_passed++;
    }
    TCNT0 = 11;
}

void Timer_init(void){
    TCCR0 = bit(TCCR0_CS00) | bit(TCCR0_CS02);
    TIMSK = bit(TIFR_T0VO);
    TCNT0 = 11;
    Intr_Register(INTR_VEC_TIMER0_OVF, func);
}

u32 Timer_GetSeconds(void){
    return seconds_passed;
}