// Five small bodies from the same neighbourhood, grouped by shape.
//
// TWO BITFIELD READS at 0x007F8DC0 and 0x007F8EE0. Both take one stack
// argument and clean it themselves (ret 4) while never touching ecx, so they
// are __stdcall rather than members, and both read the same word at +0x20 --
// one masks the low 24 bits, the other tests bit 29 with shr/and 1.
//
// A DEFAULT-STRING GETTER at 0x007EA670: the address of the buffer at +0xE1,
// swapped for the literal "PC" when the buffer is empty. The literal is still
// in the image at 0x0112 9B30.
//
// TWO EMPTY-STRING GUARDS at 0x007F52D0 and 0x007FBE70. neg cl / sbb ecx,ecx
// turns "first byte non-zero" into a mask of all ones or all zeroes, and the
// and applies it to the address -- which is the branchless spelling of
// returning the buffer or null.

// ---- the two bitfield reads -------------------------------------------------

struct Gen_007f8dc0Bits
{
	char m_bfmeHead[0x20];
	unsigned int m_bfmeFlags;					// +0x20
};

// ?Gen_007f8dc0@@YGHPAUGen_007f8dc0Bits@@@Z
int __stdcall Gen_007f8dc0(Gen_007f8dc0Bits *bits)
{
	return bits->m_bfmeFlags & 0xFFFFFF;
}

// ?Gen_007f8ee0@@YGHPAUGen_007f8dc0Bits@@@Z
int __stdcall Gen_007f8ee0(Gen_007f8dc0Bits *bits)
{
	return (bits->m_bfmeFlags >> 29) & 1;
}

// ---- the default-string getter ----------------------------------------------

class Gen_007ea670
{
public:
	char *bfmePlatform(void);

	char m_bfmeHead[0xE1];
	char m_bfmeBuffer[1];						// +0xE1
};

// ?bfmePlatform@Gen_007ea670@@QAEPADXZ
char *Gen_007ea670::bfmePlatform(void)
{
	char *text = m_bfmeBuffer;

	if (*text == 0)
		text = "PC";

	return text;
}

// ---- the two empty-string guards --------------------------------------------

class Gen_007f52d0
{
public:
	char *bfmeText(void);

	char m_bfmeHead[0x1B0];
	char m_bfmeBuffer[1];						// +0x1B0
};

// ?bfmeText@Gen_007f52d0@@QAEPADXZ
char *Gen_007f52d0::bfmeText(void)
{
	char *text = m_bfmeBuffer;

	return *text ? text : 0;
}

class Gen_007fbe70
{
public:
	char *bfmeText(void);

	char m_bfmeHead[0x190];
	char m_bfmeBuffer[1];						// +0x190
};

// ?bfmeText@Gen_007fbe70@@QAEPADXZ
char *Gen_007fbe70::bfmeText(void)
{
	char *text = m_bfmeBuffer;

	return *text ? text : 0;
}
