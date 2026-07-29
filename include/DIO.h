#ifndef DIO_H
#define DIO_H

/* IO Pins */
void DIO_SetPinDirection(u8 u8PortIdCopy,u8 u8PinIdCopy,u8 u8PinDirCopy); //DDR
void DIO_SetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy,u8 u8PinValCopy);     //PORT
u8 DIO_GetPinValue(u8 u8PortIdCopy,u8 u8PinIdCopy);						  //RETURN PIN value GET_BIT
void DIO_TogglePinValue(u8 u8PortIdCopy,u8 u8PinIdCopy);				  //PORT

/* IO Ports */
void DIO_SetPortDirection(u8 u8PortIdCopy,u8 u8PortDirCopy);			//DDR
void DIO_SetPortValue(u8 u8PortIdCopy,u8 u8PortValCopy);				//PORT
void DIO_TogglePortValue(u8 u8PortIdCopy);								//PORT
u8 DIO_GetPortValue(u8 u8PortIdCopy);	
#endif