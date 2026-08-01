#ifndef _EEPROM_H_
#define _EEPRON_H_

#define EECR	(*(volatile u8*)0x3c)
#define EECR_EERIE	3
#define EECR_EEMWE	2
#define EECR_EEWE	1
#define EECR_EERE	0

#define EEDR	(*(volatile u8*)0x3d)
#define EEARL	(*(volatile u8*)0x3e)
#define EEARH	(*(volatile u8*)0x3f)
#define EEAR	(*(volatile u16*)0x3e)
#define EEAR_MASK	0x3ff

void EEPROM_Write(u16 off, u16 len, const u8 *buf);
void EEPROM_Read(u16 off, u16 len, u8 *buf);

#endif
