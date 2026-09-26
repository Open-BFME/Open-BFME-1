// Three more: a scan that needs every slot filled, a two-stage cap and a
// constructor that clears two arrays at once.

class BfmeThingGB
{
public:
	int m_bfmeGap[36];							// +0x00
	int m_bfmeFlags;							// +0x90
};

class Gen_002B4800
{
public:
	bool bfmeAllReady(void) const;
private:
	int m_bfmeGap[2];							// +0x00
	BfmeThingGB *m_bfmeThing;					// +0x08
	unsigned char m_bfmeGap2[0x376 - 0x0c];		// +0x0c
	unsigned char m_bfmeSlots[34];				// +0x376
	int m_bfmeCount;							// +0x398
};

bool Gen_002B4800::bfmeAllReady(void) const
{
	if ((m_bfmeThing->m_bfmeFlags & 0x400000) != 0)
	{
		int count = m_bfmeCount;
		for (int index = 0; index < count; ++index)
		{
			if (m_bfmeSlots[index] == 0)
				return false;
		}
		return true;
	}
	return false;
}

class BfmeItemGC
{
public:
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

class Gen_0029A650
{
public:
	int bfmeCap(void) const;
private:
	int m_bfmeGap[8];							// +0x00
	BfmeItemGC *m_bfmeBegin;					// +0x20
	BfmeItemGC *m_bfmeEnd;						// +0x24
	int m_bfmeGap2[12];							// +0x28
	int m_bfmeCount;							// +0x58
	bool m_bfmeFlag;							// +0x5c
};

// One is the cap as soon as there is anything in the list at all; the wide
// value is what the empty, unflagged case gets.
int Gen_0029A650::bfmeCap(void) const
{
	if (m_bfmeEnd - m_bfmeBegin != 0)
		return 1;
	if (m_bfmeFlag && m_bfmeCount > 0)
		return 1;
	return 0x3FFFFFFF;
}

class Gen_001EACF0
{
public:
	Gen_001EACF0(void);
	virtual void bfmeTick(void) = 0;
private:
	int m_bfmeA;								// +0x04
	int m_bfmeSlots[4];							// +0x08
	int m_bfmeB;								// +0x18
	int m_bfmeC;								// +0x1c
	int m_bfmeD;								// +0x20
	int m_bfmeE;								// +0x24
	int m_bfmeF;								// +0x28
	unsigned char m_bfmeG;						// +0x2c
	unsigned char m_bfmeH;						// +0x2d
	unsigned char m_bfmeFlags[4];				// +0x2e
	unsigned char m_bfmeGap[2];					// +0x32
	int m_bfmeI;								// +0x34
};

Gen_001EACF0::Gen_001EACF0(void)
{
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeA = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	m_bfmeG = 0;
	m_bfmeH = 0;

	for (int index = 0; index < 4; ++index)
	{
		m_bfmeSlots[index] = 0;
		m_bfmeFlags[index] = 0;
	}

	m_bfmeI = 0;
}
