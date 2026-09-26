// Six setup stubs.
//
// Each reads a global into a callee-saved register, calls a no-argument member
// of its argument, stamps a four-character tag into +0x1C, and finishes with a
// two-argument member call carrying a fixed string and that global.
//
// The global is read BEFORE the first call, so the source loads it into a
// local first -- left as a direct global read it would have to be re-read
// afterwards, since the call could have changed it. The tag 0x61636374 is
// 'tcca' little-endian, so the field is a FourCC and not a number.
//
// Only the global's address differs across the six, and it is a relocation, so
// they all compile from one shape.

struct BfmeSetupTarget
{
	void bfmeBegin(void);					// retail 0x007E8AC0
	void bfmeWrite(const char *text, int value);		// retail 0x007E8A10

	char m_bfmeHead[0x1C];
	unsigned int m_bfmeTag;					// +0x1C
};

extern const char TheBfmeSetupText[];				// 0x011298AC


extern int TheBfmeSetupValue_007E95A0;			// 0x0130A578

extern int TheBfmeSetupValue_007E95D0;			// 0x0130A494

extern int TheBfmeSetupValue_007E98A0;			// 0x0130A4C4

extern int TheBfmeSetupValue_007E98D0;			// 0x0130A53C

extern int TheBfmeSetupValue_007E9990;			// 0x0130A4D0

extern int TheBfmeSetupValue_007E99C0;			// 0x0130A56C

// ?bfmeSetup_007E95A0@@YGXPAUBfmeSetupTarget@@@Z
void __stdcall bfmeSetup_007E95A0(BfmeSetupTarget *thing)
{
	int value = TheBfmeSetupValue_007E95A0;

	thing->bfmeBegin();

	thing->m_bfmeTag = 0x61636374;

	thing->bfmeWrite(TheBfmeSetupText, value);
}

// ?bfmeSetup_007E95D0@@YGXPAUBfmeSetupTarget@@@Z
void __stdcall bfmeSetup_007E95D0(BfmeSetupTarget *thing)
{
	int value = TheBfmeSetupValue_007E95D0;

	thing->bfmeBegin();

	thing->m_bfmeTag = 0x61636374;

	thing->bfmeWrite(TheBfmeSetupText, value);
}

// ?bfmeSetup_007E98A0@@YGXPAUBfmeSetupTarget@@@Z
void __stdcall bfmeSetup_007E98A0(BfmeSetupTarget *thing)
{
	int value = TheBfmeSetupValue_007E98A0;

	thing->bfmeBegin();

	thing->m_bfmeTag = 0x61636374;

	thing->bfmeWrite(TheBfmeSetupText, value);
}

// ?bfmeSetup_007E98D0@@YGXPAUBfmeSetupTarget@@@Z
void __stdcall bfmeSetup_007E98D0(BfmeSetupTarget *thing)
{
	int value = TheBfmeSetupValue_007E98D0;

	thing->bfmeBegin();

	thing->m_bfmeTag = 0x61636374;

	thing->bfmeWrite(TheBfmeSetupText, value);
}

// ?bfmeSetup_007E9990@@YGXPAUBfmeSetupTarget@@@Z
void __stdcall bfmeSetup_007E9990(BfmeSetupTarget *thing)
{
	int value = TheBfmeSetupValue_007E9990;

	thing->bfmeBegin();

	thing->m_bfmeTag = 0x61636374;

	thing->bfmeWrite(TheBfmeSetupText, value);
}

// ?bfmeSetup_007E99C0@@YGXPAUBfmeSetupTarget@@@Z
void __stdcall bfmeSetup_007E99C0(BfmeSetupTarget *thing)
{
	int value = TheBfmeSetupValue_007E99C0;

	thing->bfmeBegin();

	thing->m_bfmeTag = 0x61636374;

	thing->bfmeWrite(TheBfmeSetupText, value);
}
