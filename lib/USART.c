#include "bitwise_ops.h"
#include "EmbVars.h"
#include "DIO.h"
#include "USART.h"

enum URSEL {
	SEL_UBRRH,
	SEL_UCSRC
};

static void Write_URSEL(enum URSEL sel, u8 val) {
	switch (sel) {
	case SEL_UBRRH:
		clr_bit(UBRRH, UBRRH_URSEL);
		break;
	case SEL_UCSRC:
		set_bit(UCSRC, UCSRC_URSEL);
		break;
	};

	UCSRC = val;
}

void USART_Init(u16 baud_rate) {
	/* Set baud rate */
	Write_URSEL(SEL_UBRRH, baud_rate >> 8);
	UBRRL = baud_rate;

	/* Set TXEN and RXEN. */
	UCSRB |= bit(UCSRB_TXEN) | bit(UCSRB_RXEN);

	/* 8-bit character size, 2 stop bits. */
	Write_URSEL(SEL_UCSRC, 0b0111);
}

void USART_Write(u16 len, u8 *buf) {
	for (u16 i = 0; i < len; i++) {
		/* Wait for the transmit buffer to empty. */
		while (get_bit(UCSRA, UCSRA_UDRE) == 0);

		UDR = buf[i];
	}
}

void USART_Read(u16 len, u8 *buf) {
	for (u16 i = 0; i < len; i++) {
		/* Wait for data. */
		while (get_bit(UCSRA, UCSRA_RXC) == 0);

		buf[i] = UDR;
	}
}
