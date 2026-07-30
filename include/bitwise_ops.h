#ifndef BITWISE_OPS
#define BITWISE_OPS

#define bit(pos)	(1 << (pos))

#define set_bit(val, pos) ((val) |= (1 << pos))
#define clr_bit(val, pos) ((val) &= ~(1 << pos))
#define toggle_bit(val, pos) ((val) ^= (1 << pos))
#define get_bit(val, pos) ((val >> pos) & 1)

#endif
