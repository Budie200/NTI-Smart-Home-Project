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
		UBRRH = val & ~bit(UBRRH_URSEL);
		break;
	case SEL_UCSRC:
		UCSRC = val | bit(UCSRC_URSEL);
		break;
	};
}

void USART_Init(u16 baud_rate, bool txen, bool rxen, bool rxintr) {
	/* Set baud rate */
	Write_URSEL(SEL_UBRRH, baud_rate >> 8);
	UBRRL = baud_rate;

	/* Set TXEN and RXEN. */
	UCSRB |= (txen ? bit(UCSRB_TXEN) : 0) | (rxen ? bit(UCSRB_RXEN) : 0) |
	    (rxintr ? bit(UCSRB_RXCIE) : 0);

	/* 8-bit character size, 1 stop bit. */
	Write_URSEL(SEL_UCSRC, bit(UCSRC_UCSZ0) | bit(UCSRC_UCSZ1));
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
