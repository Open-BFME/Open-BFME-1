// Five more tiny ones: a pair of fields copied with one of them stepped back,
// a choice between two buffers, a scan of ten slots, and two deadlines taken
// from the clock -- one with a fixed delay, one with the caller's.

class Gen_001A0DC0
{
public:
	void bfmeRemember(void);

private:
	int m_bfmeHead[27];					// +0x00
	int m_bfmeFirst;					// +0x6C
	int m_bfmeCount;					// +0x70
	int m_bfmeGap[14];					// +0x74
	int m_bfmeSavedFirst;					// +0xAC
	int m_bfmeSavedLast;					// +0xB0
};

// ?bfmeRemember@Gen_001A0DC0@@QAEXXZ
void Gen_001A0DC0::bfmeRemember(void)
{
	m_bfmeSavedFirst = m_bfmeFirst;

	m_bfmeSavedLast = m_bfmeCount - 1;
}

class Gen_001B5240
{
public:
	void *bfmeBuffer(void);

private:
	int m_bfmeHead[14];					// +0x000
	char m_bfmeSecond[0x140];				// +0x038
	char m_bfmeFirst[14];					// +0x178
	unsigned char m_bfmeUseFirst;				// +0x186
};

// ?bfmeBuffer@Gen_001B5240@@QAEPAXXZ
void *Gen_001B5240::bfmeBuffer(void)
{
	if (m_bfmeUseFirst)
		return m_bfmeFirst;

	return m_bfmeSecond;
}

class Gen_00208330
{
public:
	unsigned char bfmeAny(void) const;

private:
	int m_bfmeSlots[10];					// +0x00
};

// ?bfmeAny@Gen_00208330@@QBEEXZ
unsigned char Gen_00208330::bfmeAny(void) const
{
	for (unsigned int index = 0; index < 10; ++index)
	{
		if (m_bfmeSlots[index])
			return 1;
	}

	return 0;
}

class BfmeClockBL
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeStamp;					// +0x3C
};

extern BfmeClockBL *g_bfmeClockBL;				// retail 0x012F0898

class Gen_001BFF50
{
public:
	void bfmeArm(void);

private:
	int m_bfmeHead[219];					// +0x000
	int m_bfmeDeadline;					// +0x36C
};

// ?bfmeArm@Gen_001BFF50@@QAEXXZ
void Gen_001BFF50::bfmeArm(void)
{
	m_bfmeDeadline = g_bfmeClockBL->m_bfmeStamp + 50;
}

class Gen_001E19F0
{
public:
	void bfmeArm(int delay);

private:
	int m_bfmeHead[20];					// +0x00
	int m_bfmeDeadline;					// +0x50
};

// ?bfmeArm@Gen_001E19F0@@QAEXH@Z
void Gen_001E19F0::bfmeArm(int delay)
{
	m_bfmeDeadline = g_bfmeClockBL->m_bfmeStamp + delay;
}
