#ifndef USART_H_
#define USART_H_

#define UBRRL	(*(volatile u8 *)0x29)
#define UCSRB	(*(volatile u8 *)0x2a)
#define UCSRB_TXEN	3
#define UCSRB_RXEN	4

#define UCSRA	(*(volatile u8 *)0x2b)
#define UCSRA_UDRE	5
#define UCSRA_RXC	7

#define UDR	(*(volatile u8 *)0x2c)
#define UBRRH	(*(volatile u8 *)0x40)
#define UBRRH_URSEL	7

#define UCSRC	UBRRH /* NB: These share the same address. */
#define UCSRC_URSEL	UBRRH_URSEL

void USART_Init(u16 baud_rate);
void USART_Write(u16 len, u8 *buf);
void USART_Read(u16 len, u8 *buf);

#endif /* USART_H_ */
