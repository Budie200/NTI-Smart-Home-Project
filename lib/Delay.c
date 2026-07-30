#include "EmbVars.h"

void Delay_us(u64 t) {
	for(u32 i = 0; i < t; i++){
		asm("nop");
	}
}

void Delay_ms(u32 t) {
	Delay_us(t * 1000);
}