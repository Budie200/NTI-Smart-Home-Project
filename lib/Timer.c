#include "EmbVars.h"
#include "DIO.h"
#include "bitwise_ops.h"
#include "Timer.h"
#include "Interrupt.h"

ISR(TIMER0_OVF_vect){
    Timer_OverflowCount++;
}

void Timer_init(void){
    TCCR0 = bit(TCCR0_CS00) | bit(TCCR0_CS02);
    TIMSK = bit(TIFR_T0VO);
    TCNT0 = 11;
}
