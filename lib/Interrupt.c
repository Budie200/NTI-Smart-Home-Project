#include "EmbVars.h"
#include "Interrupt.h"

/* Just an empty ISR. The default ISR if nothing is registered. */
static INTR_FUNC(Intr_Nop) {
	return;
}

/* Needed to jump to main after __do_copy_data. */
static __attribute__((used, naked, section(".init9"))) void Intr_Start(void) {
	asm("jmp main");
}

static INTR_FUNC_TYPE(Intr_Vectbl[INTR_NVECTORS]) = {
	[0] = NULL, /* Unused. */
	[1 ... INTR_NVECTORS-1] = Intr_Nop
};

static __attribute__((naked, used, signal, noreturn, section(".vectors")))
void Intr_Vector(void) {
	u8 *sp;

	/*
	 * The vector table.
	 * This is located at phys 0.
	 *
	 * The first vector is the reset vector, it's
	 * not really worth configuring so just call __do_copy_data.
	 *
	 * The rest of the vectors just call the 0: label below,
	 * then figure out which vector it was by inspecting the
	 * stack pointer.
	 */
	asm (
		"jmp __do_copy_data\n"
		"call 0f\ncall 0f\ncall 0f\ncall 0f\ncall 0f\n"
		"call 0f\ncall 0f\ncall 0f\ncall 0f\ncall 0f\n"
		"call 0f\ncall 0f\ncall 0f\ncall 0f\ncall 0f\n"
		"call 0f\ncall 0f\ncall 0f\ncall 0f\ncall 0f\n"

		"0:\n"

		/* 0x3d is SPL */
		"in %A0, 0x3d\n"

		/*
		 * The call instruction subtracts two from SP.
		 * Undo this by subtracting -2 (0xfe).
		 * There's no add instruction for this apparently...
		 *
		 * XXX
		 * There's an edge case here where SPL is 0xff
		 * so the number would have to be carried to SPH.
		 *
		 * ...
		 *
		 * Whatever.
		 */
		"subi %A0, 0xfe\n"

		"out 0x3d, %A0\n"

		/* 0x3e is SPH */
		"in %B0, 0x3e"
		: "=d"(sp)
	);

	asm ("ijmp" :: "z"(Intr_Vectbl[(*sp - 2) / 2]));
}

void Intr_Register(enum Intr_Vec vec, INTR_FUNC_TYPE(func)) {
	Intr_Vectbl[vec] = func;
}
