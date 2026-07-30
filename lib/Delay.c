#include "EmbVars.h"

void Delay_us(u32 t) {
	for(u32 i = 0; i < t; i++){
		asm("nop");
	}
}

void Delay_ms(u16 t) {
	Delay_us(t * 1000);
}