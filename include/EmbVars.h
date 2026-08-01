#ifndef EMBVARS
#define EMBVARS

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;

typedef float f32;

typedef _Bool bool;

#define true 1
#define false 0

/* Only available on gcc version >= 10.5 */
#if (__GNUC__ >= 10 && __GNUC_MINOR__ >= 5)
typedef long double f64;
#endif

_Static_assert(sizeof(u8) == 1, "sizeof(u/s8) != 1");
_Static_assert(sizeof(u16) == 2, "sizeof(u/s16) != 2");
_Static_assert(sizeof(u32) == 4, "sizeof(u/s32) != 4");
_Static_assert(sizeof(u64) == 8, "sizeof(u/s64) != 8");

_Static_assert(sizeof(f32) == 4, "sizeof(f32) != 4");
#if (__GNUC__ >= 10 && __GNUC_MINOR__ >= 5)
_Static_assert(sizeof(f64) == 8, "sizeof(f64) != 8");
#endif

#define NULL ((void*) 0)

//for port/pin direction
#define OUTPUT 1
#define INPUT 0

//for port/pin values
#define HIGH 1
#define LOW 0

// A
#define DDRA (*(volatile u8*) 0x3A)
#define PORTA (*(volatile u8*) 0x3B)
#define PINA (*(volatile u8*) 0x39)

// B
#define DDRB (*(volatile u8*) 0x37)
#define PORTB (*(volatile u8*) 0x38)
#define PINB (*(volatile u8*) 0x36)

//C
#define DDRC (*(volatile u8*) 0x34)
#define PORTC (*(volatile u8*) 0x35)
#define PINC (*(volatile u8*) 0x33)

//D
#define DDRD (*(volatile u8*) 0x31)
#define PORTD (*(volatile u8*) 0x32)
#define PIND (*(volatile u8*) 0x30)

#define MCUCR (*(volatile u8*) 0x55)
#define GICR (*(volatile u8*) 0x5b)
#define SPL (*(volatile u8*) 0x5d)
#define SPH (*(volatile u8*) 0x5e)
#define SP (*(volatile u8**) 0x5d)
#define SREG (*(volatile u8*) 0x5f)

#endif
