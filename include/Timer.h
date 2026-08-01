#ifndef TIMER_H
#define TIMER_H

#define TCCR0 *((volatile u8*) 0x53) //set prescaler
#define TCCR0_CS00 0
#define TCCR0_CS02 2

// offset = 11
#define TCNT0 *((volatile u8*) 0x50)//clk value

#define TIMSK *((volatile u8*) 0x59)
#define TIMSK_TOIE0 0

#define TIFR *((volatile u8*) 0x58)
#define TIFR_T0VO 0

void Timer_Init(void);
u32 Timer_GetSeconds(void);

#endif
