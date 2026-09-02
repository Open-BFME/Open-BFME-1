// ?bfmeReg1033@@YAXP6AXXZ0@Z
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: bfmeReg1033, retail 0x004C6AA0. Matched caller
// BfmeB1033::bfmeGo1033B jumps here through the 0x0002FCB1 thunk.
// Body is xor-zero of two globals then call of the first function-pointer
// argument. Retail wraps that in a 12-byte C++ EH frame with unwind state
// stuck at -1 (no live object); empty-dtor locals, throw(), and /EHa all
// failed to emit that frame without extra instructions.

void *g_bfmeReg1033A;
void *g_bfmeReg1033B;

void bfmeReg1033(void (*a)(void), void (*b)(void))
{
	g_bfmeReg1033A = 0;
	g_bfmeReg1033B = 0;
	a();
	(void)b;
}

bool bfmeReg1033True(void)
{
	return true;
}
