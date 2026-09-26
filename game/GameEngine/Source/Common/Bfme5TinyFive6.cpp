// Four more tiny ones: two two-part tests, a pair written into an object that
// may not be there, and a widen-the-range helper whose two stores are merged
// into one -- both write through whichever pointer the branch left in the
// register.

class Gen_005887D0
{
public:
	int bfmeIsPlain(void) const;

private:
	int m_bfmeHead[8];					// +0x00
	unsigned char m_bfmeFlags;				// +0x20
	unsigned char m_bfmeGap[3];				// +0x21
	unsigned int m_bfmeMask;				// +0x24
};

// ?bfmeIsPlain@Gen_005887D0@@QBEHXZ
int Gen_005887D0::bfmeIsPlain(void) const
{
	if ((m_bfmeFlags & 4) && !(m_bfmeMask & 0xFF000000))
		return 1;

	return 0;
}

class Gen_005B53B0
{
public:
	void *bfmeSlot(void);

private:
	int m_bfmeTag;						// +0x000
	int m_bfmeField;					// +0x004
	int m_bfmeGap[12];					// +0x008
	unsigned char m_bfmeReady;				// +0x038
	char m_bfmeGap2[0x10F];					// +0x039
	int m_bfmeMode;						// +0x148
};

// ?bfmeSlot@Gen_005B53B0@@QAEPAXXZ
void *Gen_005B53B0::bfmeSlot(void)
{
	if (m_bfmeReady && m_bfmeMode == 1)
		return &m_bfmeField;

	return 0;
}

class BfmeTargetBV
{
public:
	char m_bfmeHead[0x58];					// +0x00
	int m_bfmeFirst;					// +0x58
	int m_bfmeSecond;					// +0x5C
};

class Gen_0075BDB0
{
public:
	void bfmeSetPair(int first, int second);

private:
	int m_bfmeHead[16];					// +0x00
	BfmeTargetBV *m_bfmeTarget;				// +0x40
};

// ?bfmeSetPair@Gen_0075BDB0@@QAEXHH@Z
void Gen_0075BDB0::bfmeSetPair(int first, int second)
{
	BfmeTargetBV *target = m_bfmeTarget;

	if (target)
	{
		target->m_bfmeFirst = first;
		target->m_bfmeSecond = second;
	}
}

// ?bfmeWiden@@YAXPAHH0@Z
void __cdecl bfmeWiden(int *low, int value, int *high)
{
	if (value < *low)
		*low = value;
	else if (value > *high)
		*high = value;
}
