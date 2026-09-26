// Three more: a twin of the guarded value read, the push matching the frame
// pop, and a flag cleared across a vector.

class BfmeItemEG
{
public:
	int m_bfmeHead[4];					// +0x00
	int m_bfmeValue;					// +0x10
};

class Gen_008C4200
{
public:
	int bfmeValue(void) const;

private:
	int m_bfmeHead;						// +0x00
	unsigned int m_bfmeBits;				// +0x04
	int m_bfmeGap[18];					// +0x08
	BfmeItemEG *m_bfmeItem;					// +0x50
};

// ?bfmeValue@Gen_008C4200@@QBEHXZ
int Gen_008C4200::bfmeValue(void) const
{
	unsigned int bits = m_bfmeBits;

	if ((bits & 0x3F) == 0x13)
	{
		unsigned char flag = (unsigned char)(bits >> 15);

		flag = ~flag;

		if ((flag & 1) == 0)
			return 0;
	}

	BfmeItemEG *item = m_bfmeItem;

	if (item != 0 && item != (BfmeItemEG *)0xBAADF00D)
		return item->m_bfmeValue;

	return 0;
}

class BfmeFrameEG
{
public:
	int m_bfmeData[8];					// 32 bytes
};

class Gen_008D2B50
{
public:
	void bfmePush(void);

private:
	BfmeFrameEG m_bfmeCurrent;				// +0x000
	char m_bfmeGap[0x18];					// +0x020
	BfmeFrameEG m_bfmeStack[28];				// +0x038
	int m_bfmeTop;						// +0x3B8
};

// ?bfmePush@Gen_008D2B50@@QAEXXZ
void Gen_008D2B50::bfmePush(void)
{
	m_bfmeStack[m_bfmeTop] = m_bfmeCurrent;

	++m_bfmeTop;
}

class BfmeSlotEG
{
public:
	int m_bfmeHead[8];					// +0x00
	bool m_bfmeArmed;					// +0x20
};

class BfmeVecEG
{
public:
	int bfmeSize(void) const
	{
		return m_bfmeFinish - m_bfmeStart;
	}

	BfmeSlotEG *bfmeAt(int index) const
	{
		return m_bfmeStart[index];
	}

	BfmeSlotEG **m_bfmeStart;				// +0x00
	BfmeSlotEG **m_bfmeFinish;				// +0x04
};

class Gen_006ED570
{
public:
	void bfmeClearAll(void);

private:
	int m_bfmeHead[5];					// +0x00
	BfmeVecEG m_bfmeVector;					// +0x14
};

// The bound comes from the accessor each pass, so the size is recomputed
// inside the walk.
// ?bfmeClearAll@Gen_006ED570@@QAEXXZ
void Gen_006ED570::bfmeClearAll(void)
{
	for (int index = 0; index < m_bfmeVector.bfmeSize(); ++index)
		m_bfmeVector.bfmeAt(index)->m_bfmeArmed = false;
}
