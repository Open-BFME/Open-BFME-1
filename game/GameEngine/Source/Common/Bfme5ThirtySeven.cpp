// Six more: a complement that hands itself back, a clamped difference, a size
// test, a band search, a flag test, and a counter that reports when it fills a
// mask.

// The trim takes the word by address, which is what keeps the complement's own
// store alive ahead of the masked one.
inline void bfmeTrimDF(unsigned int *word)
{
	*word = *word & 0x3FFFFF;
}

class Gen_001C3D40
{
public:
	Gen_001C3D40 &bfmeInvert(void);

private:
	unsigned int m_bfmeFirst;				// +0x00
	unsigned int m_bfmeSecond;				// +0x04
	unsigned int m_bfmeThird;				// +0x08
};

// Handing the object back is what keeps this in eax across the whole body.
// ?bfmeInvert@Gen_001C3D40@@QAEAAV1@XZ
Gen_001C3D40 &Gen_001C3D40::bfmeInvert(void)
{
	m_bfmeFirst = ~m_bfmeFirst;
	m_bfmeSecond = ~m_bfmeSecond;
	m_bfmeThird = ~m_bfmeThird;

	bfmeTrimDF(&m_bfmeThird);

	return *this;
}

class BfmeThingDF
{
public:
	int m_bfmeHead[6];					// +0x00
	float m_bfmeValue;					// +0x18
};

extern float g_bfmeOffsetDF;					// retail 0x01098AD4
extern float g_bfmeZeroCY;					// retail 0x01075350

class Gen_001E1950
{
public:
	float bfmeValue(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeThingDF *m_bfmeThing;				// +0x04
};

// ?bfmeValue@Gen_001E1950@@QBEMXZ
float Gen_001E1950::bfmeValue(void) const
{
	float value = m_bfmeThing->m_bfmeValue - g_bfmeOffsetDF;

	if (value < g_bfmeZeroCY)
		value = g_bfmeZeroCY;

	return value;
}

class BfmeTripleDF
{
public:
	int m_bfmeData[3];					// 12 bytes
};

class Gen_001EFA70
{
public:
	bool bfmeHasAny(void) const;

private:
	unsigned int bfmeSize(void) const
	{
		return m_bfmeFinish - m_bfmeStart;
	}

	int m_bfmeHead[17];					// +0x00
	BfmeTripleDF *m_bfmeStart;				// +0x44
	BfmeTripleDF *m_bfmeFinish;				// +0x48
};

// ?bfmeHasAny@Gen_001EFA70@@QBE_NXZ
bool Gen_001EFA70::bfmeHasAny(void) const
{
	return bfmeSize() > 0;
}

extern int *g_bfmeLimitsDF;					// retail 0x012F401C

// ?bfmeBand@@YAHH@Z
int __cdecl bfmeBand(int value)
{
	int index = 1;

	while (index < 10 && value >= g_bfmeLimitsDF[index])
		++index;

	return index;
}

class BfmeStateDF
{
public:
	int m_bfmeHead[2];					// +0x00
	bool m_bfmeBusy;					// +0x08
};

extern BfmeStateDF *g_bfmeStateDF;				// retail 0x012F7048

class Gen_005896B0
{
public:
	int bfmeReady(void) const;

private:
	char m_bfmeHead[0x4B];					// +0x00
	bool m_bfmeArmed;					// +0x4B
};

// ?bfmeReady@Gen_005896B0@@QBEHXZ
int Gen_005896B0::bfmeReady(void) const
{
	if (!g_bfmeStateDF->m_bfmeBusy && m_bfmeArmed)
		return 1;

	return 0;
}

class Gen_005BD290
{
public:
	int bfmeTick(void);

private:
	int m_bfmeHead[1460];					// +0x0000
	int m_bfmeCount;					// +0x16D0
	int m_bfmeMask;						// +0x16D4
};

// ?bfmeTick@Gen_005BD290@@QAEHXZ
int Gen_005BD290::bfmeTick(void)
{
	int count = m_bfmeCount + 1;

	m_bfmeCount = count;

	int mask = m_bfmeMask;

	return (mask & count) != mask;
}
