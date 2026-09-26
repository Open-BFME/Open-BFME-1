// Five more tiny ones: a pair of floats accumulated from a caller's pair, a
// search for the first free slot of twelve, an unsigned count turned into a
// float and subtracted, a countdown that reloads itself, and a pair written
// into an indexed object.

class BfmePointCH
{
public:
	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
};

class Gen_0045B540
{
public:
	int bfmeAdd(BfmePointCH *delta);

private:
	int m_bfmeHead[3];					// +0x00
	float m_bfmeX;						// +0x0C
	float m_bfmeY;						// +0x10
};

// ?bfmeAdd@Gen_0045B540@@QAEHPAVBfmePointCH@@@Z
int Gen_0045B540::bfmeAdd(BfmePointCH *delta)
{
	m_bfmeX = delta->m_bfmeX + m_bfmeX;
	m_bfmeY = delta->m_bfmeY + m_bfmeY;

	return 0;
}

class BfmeSlotCH
{
public:
	int m_bfmeId;						// +0x00
	int m_bfmeRest[4];					// +0x04
};

class Gen_00465C90
{
public:
	int bfmeFindFree(void) const;

private:
	int m_bfmeHead[45];					// +0x00
	BfmeSlotCH m_bfmeSlots[12];				// +0xB4
};

// ?bfmeFindFree@Gen_00465C90@@QBEHXZ
int Gen_00465C90::bfmeFindFree(void) const
{
	for (int index = 0; index < 12; ++index)
	{
		if (m_bfmeSlots[index].m_bfmeId == -1)
			return index;
	}

	return -1;
}

class BfmeCountCH
{
public:
	int m_bfmeTag;						// +0x00
	unsigned int m_bfmeCount;				// +0x04
};

class Gen_004224A0
{
public:
	float bfmeDelta(BfmeCountCH *other) const;

private:
	int m_bfmeTag;						// +0x00
	float m_bfmeValue;					// +0x04
};

// ?bfmeDelta@Gen_004224A0@@QBEMPAVBfmeCountCH@@@Z
float Gen_004224A0::bfmeDelta(BfmeCountCH *other) const
{
	return other->m_bfmeCount - m_bfmeValue;
}

class BfmeOwnerCH
{
public:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeReload;					// +0x08
};

class Gen_00291BB0
{
public:
	unsigned char bfmeTick(void);

private:
	int m_bfmeTag;						// +0x00
	BfmeOwnerCH *m_bfmeOwner;				// +0x04
	int m_bfmeGap[6];					// +0x08
	int m_bfmeCount;					// +0x20
};

// ?bfmeTick@Gen_00291BB0@@QAEEXZ
unsigned char Gen_00291BB0::bfmeTick(void)
{
	int count = m_bfmeCount;

	if (count == 0)
	{
		m_bfmeCount = m_bfmeOwner->m_bfmeReload;

		return 1;
	}

	m_bfmeCount = count - 1;

	return 0;
}

class BfmeTargetCH
{
public:
	char m_bfmeHead[0x58];					// +0x00
	int m_bfmeFirst;					// +0x58
	int m_bfmeSecond;					// +0x5C
};

class Gen_00299800
{
public:
	void bfmeSetPair(int index, int first, int second);

private:
	int m_bfmeHead[22];					// +0x00
	BfmeTargetCH *m_bfmeSlots[8];				// +0x58
};

// ?bfmeSetPair@Gen_00299800@@QAEXHHH@Z
void Gen_00299800::bfmeSetPair(int index, int first, int second)
{
	BfmeTargetCH *target = m_bfmeSlots[index];

	target->m_bfmeFirst = first;
	target->m_bfmeSecond = second;
}
