// Four fills, all of them the compiler's own expansion of memset.
//
// A size computed at run time becomes the pair of repeated stores, words
// first and then the remainder. The last one is not a memset at all: the
// element loop MSVC turns into a repeated store puts the count after the
// address, where the intrinsic puts it first, and the two fields on either
// side of the array are written as themselves.

extern "C" void * __cdecl memset(void *block, int value, unsigned int bytes);

#pragma intrinsic(memset)

class Gen_007498B0
{
public:
	void bfmeClearBits(void);

private:
	int m_bfmeHead[17];					// +0x00
	char *m_bfmeStart;					// +0x44
	char *m_bfmeEnd;					// +0x48
};

// ?bfmeClearBits@Gen_007498B0@@QAEXXZ
void Gen_007498B0::bfmeClearBits(void)
{
	memset(m_bfmeStart, 0, m_bfmeEnd - m_bfmeStart);
}

class Gen_00749960
{
public:
	void bfmeSetBits(void);

private:
	int m_bfmeHead[20];					// +0x00
	char *m_bfmeStart;					// +0x50
	char *m_bfmeEnd;					// +0x54
};

// ?bfmeSetBits@Gen_00749960@@QAEXXZ
void Gen_00749960::bfmeSetBits(void)
{
	memset(m_bfmeStart, -1, m_bfmeEnd - m_bfmeStart);
}

class Gen_00683280
{
public:
	void bfmeReset(void);

private:
	int m_bfmeCount;					// +0x000
	int m_bfmeSlots[256];					// +0x004
	int m_bfmeA;						// +0x404
	int m_bfmeB;						// +0x408
	short m_bfmeC;						// +0x40C
};

// ?bfmeReset@Gen_00683280@@QAEXXZ
void Gen_00683280::bfmeReset(void)
{
	m_bfmeCount = 0;

	for (int index = 0; index < 256; ++index)
		m_bfmeSlots[index] = 0;

	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
}
