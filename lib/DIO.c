#include "EmbVars.h"
#include "bitwise_ops.h"
#include "DIO.h"

// IO PINS
void DIO_SetPinDirection(u8 u8PortIdCopy,u8 u8PinIdCopy,u8 u8PinDirCopy){
    if(u8PinDirCopy){
        switch(u8PortIdCopy){
            case 1: set_bit(DDRA, u8PinIdCopy); break;
            case 2: set_bit(DDRB, u8PinIdCopy); break;
            case 3: set_bit(DDRC, u8PinIdCopy); break;
            case 4: set_bit(DDRD, u8PinIdCopy); break;
        }
    }
    else{
        switch(u8PortIdCopy){
            case 1: clr_bit(DDRA, u8PinIdCopy); break;
            case 2: clr_bit(DDRB, u8PinIdCopy); break;
            case 3: clr_bit(DDRC, u8PinIdCopy); break;
            case 4: clr_bit(DDRD, u8PinIdCopy); break;
        }
    }
} 

void DIO_SetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy,u8 u8PinValCopy){
    if(u8PinValCopy){
        switch(u8PortIdCopy){
            case 1: set_bit(PORTA, u8PinIdCopy); break;
            case 2: set_bit(PORTB, u8PinIdCopy); break;
            case 3: set_bit(PORTC, u8PinIdCopy); break;
            case 4: set_bit(PORTD, u8PinIdCopy); break;
        }
    }
    else{
        switch(u8PortIdCopy){
            case 1: clr_bit(PORTA, u8PinIdCopy); break;
            case 2: clr_bit(PORTB, u8PinIdCopy); break;
            case 3: clr_bit(PORTC, u8PinIdCopy); break;
            case 4: clr_bit(PORTD, u8PinIdCopy); break;
        }
    }
}     
u8 DIO_GetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy){
    switch(u8PortIdCopy){
            case 1: return get_bit(PINA, u8PinIdCopy); 
            case 2: return get_bit(PINB, u8PinIdCopy); 
            case 3: return get_bit(PINC, u8PinIdCopy); 
            case 4: return get_bit(PIND, u8PinIdCopy); 
        }
}						  
void DIO_TogglePinValue(u8 u8PortIdCopy,u8 u8PinIdCopy){
    switch(u8PortIdCopy){
            case 1: toggle_bit(PORTA, u8PinIdCopy); break;
            case 2: toggle_bit(PORTB, u8PinIdCopy); break;
            case 3: toggle_bit(PORTC, u8PinIdCopy); break;
            case 4: toggle_bit(PORTD, u8PinIdCopy); break;
        }
}

// IO PORTS
void DIO_SetPortDirection(u8 u8PortIdCopy, u8 u8PortDirCopy){
    if(u8PortDirCopy){
        switch(u8PortIdCopy){
            case 1: DDRA = 255; break;
            case 2: DDRB = 255; break;
            case 3: DDRC = 255; break;
            case 4: DDRD = 255; break;
        }
    }
    else{
        switch(u8PortIdCopy){
            case 1: DDRA = 0; break;
            case 2: DDRB = 0; break;
            case 3: DDRC = 0; break;
            case 4: DDRD = 0; break;
        }
    }
}

void DIO_SetPortValue(u8 u8PortIdCopy,u8 u8PortValCopy){
    switch(u8PortIdCopy){
            case 1: PORTA = u8PortValCopy; break;
            case 2: PORTB = u8PortValCopy; break;
            case 3: PORTC = u8PortValCopy; break;
            case 4: PORTD = u8PortValCopy; break;
        }
}

void DIO_TogglePortValue(u8 u8PortIdCopy){
    switch(u8PortIdCopy){
        case 1:
        PORTA = ~PORTA;
        break;
        case 2:
        PORTB = ~PORTB;
        break;
        case 3:
        PORTC = ~PORTC;
        break;
        case 4:
        PORTD = ~PORTD;
        break;
    }
}

u8 DIO_GetPortValue(u8 u8PortIdCopy){
    switch(u8PortIdCopy){
        case 1: return PORTA;
        case 2: return PORTB;
        case 3: return PORTC;
        case 4: return PORTD;
    }
}