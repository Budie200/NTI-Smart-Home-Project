#include "EmbVars.h"
#include "bitwise_ops.h"
#include "EEPROM.h"

void EEPROM_Read(u16 off, u16 len, u8 *buf) {
	/* Wait for any pending writes. */
	while (get_bit(EECR, EECR_EEWE));

	for (u16 i = 0; i < len; i++) {
		u8 sreg_intr;

		EEAR = (off + i) & EEAR_MASK;

		sreg_intr = get_bit(SREG, SREG_INTREN);
		clr_bit(sreg_intr, SREG_INTREN);

		set_bit(EECR, EECR_EERE);
		buf[i] = EEDR;

		if (sreg_intr != 0)
			set_bit(SREG, SREG_INTREN);
	}
}

void EEPROM_Write(u16 off, u16 len, const u8 *buf) {
	for (u16 i = 0; i < len; i++) {
		u8 sreg_intr;

		/* Wait for any pending writes. */
		while (get_bit(EECR, EECR_EEWE));

		EEAR = (off + i) & EEAR_MASK;
		EEDR = buf[i];

		/* Disable interrupts while we're writing. */
		sreg_intr = get_bit(SREG, SREG_INTREN);
		clr_bit(SREG, SREG_INTREN);

		set_bit(EECR, EECR_EEMWE);
		set_bit(EECR, EECR_EEWE);

		if (sreg_intr != 0)
			set_bit(SREG, SREG_INTREN);
	}
}
