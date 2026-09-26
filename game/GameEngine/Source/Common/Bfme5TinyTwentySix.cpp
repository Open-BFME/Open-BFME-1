// Five more: another two-member swap, a chain depth, a size over a sixty-byte
// element, an all-zero test and a one-bit store.

inline void bfmeSwapIntCT(int *first, int *second)
{
	int value = *first;

	*first = *second;
	*second = value;
}

class Gen_00350E60
{
public:
	void bfmeSwap(Gen_00350E60 *other);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
};

// ?bfmeSwap@Gen_00350E60@@QAEXPAV1@@Z
void Gen_00350E60::bfmeSwap(Gen_00350E60 *other)
{
	bfmeSwapIntCT(&m_bfmeFirst, &other->m_bfmeFirst);
	bfmeSwapIntCT(&m_bfmeSecond, &other->m_bfmeSecond);
}

class BfmeLinkCT
{
public:
	int m_bfmeHead[34];					// +0x00
	BfmeLinkCT *m_bfmeParent;				// +0x88
};

class Gen_003837A0
{
public:
	int bfmeDepth(void) const;

private:
	int m_bfmeHead[42];					// +0x00
	BfmeLinkCT *m_bfmeLink;					// +0xA8
};

// ?bfmeDepth@Gen_003837A0@@QBEHXZ
int Gen_003837A0::bfmeDepth(void) const
{
	BfmeLinkCT *link = m_bfmeLink;

	int count = 0;

	while (link)
	{
		link = link->m_bfmeParent;

		++count;
	}

	return count;
}

class BfmeSlotCT
{
public:
	int m_bfmeData[15];					// 60 bytes
};

class Gen_003CD2A0
{
public:
	int bfmeSize(void) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeSlotCT *m_bfmeStart;				// +0x08
	BfmeSlotCT *m_bfmeFinish;				// +0x0C
};

// ?bfmeSize@Gen_003CD2A0@@QBEHXZ
int Gen_003CD2A0::bfmeSize(void) const
{
	return m_bfmeFinish - m_bfmeStart;
}

class Gen_003D3220
{
public:
	bool bfmeAllZero(void) const;

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
};

// ?bfmeAllZero@Gen_003D3220@@QBE_NXZ
bool Gen_003D3220::bfmeAllZero(void) const
{
	int *it = m_bfmeStart;
	int *finish = m_bfmeFinish;

	while (it != finish)
	{
		if (*it != 0)
			return false;

		++it;
	}

	return true;
}

class BfmeOwnerCT
{
public:
	int m_bfmeHead[9];					// +0x00
	unsigned int m_bfmeFlag : 1;				// +0x24
	unsigned int m_bfmeRest : 31;				// +0x24
};

class Gen_003D4A20
{
public:
	void bfmeSetFlag(unsigned char value);

private:
	BfmeOwnerCT *m_bfmeOwner;				// +0x00
};

// ?bfmeSetFlag@Gen_003D4A20@@QAEXE@Z
void Gen_003D4A20::bfmeSetFlag(unsigned char value)
{
	// The explicit "!= 0" is what renormalises the byte into the bitfield; a
	// bool argument goes straight in and saves three bytes.
	m_bfmeOwner->m_bfmeFlag = (value != 0);
}
