// Four more tiny ones: a field address with a shared default, a stamp and a
// flag cleared together, an emptiness test that answers through the carry, and
// a flag written into a singleton.

class BfmeThingBP
{
public:
	char m_bfmeHead[0x54];					// +0x00
	int m_bfmeField;					// +0x54
};

extern int g_bfmeDefaultBP[2];					// retail 0x01336E50

class Gen_003C63A0
{
public:
	int *bfmeField(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeThingBP *m_bfmeThing;				// +0x04
};

// ?bfmeField@Gen_003C63A0@@QBEPAHXZ
int *Gen_003C63A0::bfmeField(void) const
{
	BfmeThingBP *thing = m_bfmeThing;

	if (thing)
		return &thing->m_bfmeField;

	return g_bfmeDefaultBP;
}

class BfmeClockBP
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeStamp;					// +0x3C
};

extern BfmeClockBP *g_bfmeClockBP;				// retail 0x012F0898

class Gen_002B6330
{
public:
	int bfmeReset(void);

private:
	int m_bfmeHead[9];					// +0x00
	int m_bfmeWhen;						// +0x24
	int m_bfmeGap;						// +0x28
	unsigned char m_bfmeFlag;				// +0x2C
};

// ?bfmeReset@Gen_002B6330@@QAEHXZ
int Gen_002B6330::bfmeReset(void)
{
	m_bfmeWhen = g_bfmeClockBP->m_bfmeStamp;

	m_bfmeFlag = 0;

	return 0;
}

class Gen_003BD6A0
{
public:
	int bfmeHasAny(void) const;

private:
	int m_bfmeHead[5];					// +0x00
	int *m_bfmeStart;					// +0x14
	int *m_bfmeFinish;					// +0x18
};

// ?bfmeHasAny@Gen_003BD6A0@@QBEHXZ
int Gen_003BD6A0::bfmeHasAny(void) const
{
	return 0 < (unsigned int)(m_bfmeFinish - m_bfmeStart);
}

class BfmeHolderBP
{
public:
	char m_bfmeHead[0xBC];					// +0x00
	unsigned char m_bfmeFlag;				// +0xBC
};

extern BfmeHolderBP *g_bfmeHolderBP;				// retail 0x012F1464

// ?bfmeSetFlag@@YGXE@Z
void __stdcall bfmeSetFlag(unsigned char value)
{
	g_bfmeHolderBP->m_bfmeFlag = value;
}
