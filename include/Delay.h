#ifndef DELAY_H
#define DELAY_H

#define Delay_us(t)	__builtin_avr_delay_cycles(t)
#define Delay_ms(t)	Delay_us(t * 1000ul)

#endif
