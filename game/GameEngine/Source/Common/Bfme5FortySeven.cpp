// Four more: a size test, a search by key over a circular list, a reset that
// keeps its bound check inside the loop, and a two-mask kind test.

class BfmeElemDP
{
public:
	int m_bfmeData[9];					// 36 bytes
};

class Gen_003C6FA0
{
public:
	bool bfmeHasAny(void) const;

private:
	unsigned int bfmeSize(void) const
	{
		return m_bfmeFinish - m_bfmeStart;
	}

	char m_bfmeHead[0x9C];					// +0x00
	BfmeElemDP *m_bfmeStart;				// +0x9C
	BfmeElemDP *m_bfmeFinish;				// +0xA0
};

// ?bfmeHasAny@Gen_003C6FA0@@QBE_NXZ
bool Gen_003C6FA0::bfmeHasAny(void) const
{
	return bfmeSize() > 0;
}

class BfmeNodeDP
{
public:
	BfmeNodeDP *m_bfmeNext;					// +0x00
	int m_bfmeGap;						// +0x04
	int m_bfmeValue;					// +0x08
	unsigned short m_bfmeKey;				// +0x0C
};

class Gen_00430400
{
public:
	int *bfmeFind(unsigned short key) const;

private:
	char m_bfmeHead[0xF0];					// +0x00
	BfmeNodeDP *m_bfmeList;					// +0xF0
};

// ?bfmeFind@Gen_00430400@@QBEPAHG@Z
int *Gen_00430400::bfmeFind(unsigned short key) const
{
	BfmeNodeDP *head = m_bfmeList;

	for (BfmeNodeDP *node = head->m_bfmeNext; node != head; node = node->m_bfmeNext)
	{
		if (node->m_bfmeKey == key)
			return &node->m_bfmeValue;
	}

	return 0;
}

class BfmeSlotDP
{
public:
	int m_bfmeValue;					// +0x00
	bool m_bfmeArmed;					// +0x04
	char m_bfmeTail[0x0F];					// +0x05
};

class Gen_0043B460
{
public:
	void bfmeReset(int mode);

private:
	// The bound check rides inside the walk, so it is emitted once per pass.
	void bfmeClear(unsigned int index)
	{
		if (index < 25)
		{
			m_bfmeSlots[index].m_bfmeValue = 0;
			m_bfmeSlots[index].m_bfmeArmed = true;
		}
	}

	char m_bfmeHead[0x44];					// +0x00
	BfmeSlotDP m_bfmeSlots[25];				// +0x44
};

// ?bfmeReset@Gen_0043B460@@QAEXH@Z
void Gen_0043B460::bfmeReset(int mode)
{
	if (mode != 0)
		return;

	// The walk counts on a signed index while the guard inside compares it
	// unsigned, which is why both survive on the same compare.
	for (int index = 0; index < 25; ++index)
		bfmeClear(index);
}

class BfmeThingDP
{
public:
	int m_bfmeHead[3];					// +0x00
	unsigned int m_bfmeFlags;				// +0x0C
};

// ?bfmeSameKind@@YAHPBVBfmeThingDP@@0@Z
int __cdecl bfmeSameKind(const BfmeThingDP *first, const BfmeThingDP *second)
{
	unsigned int a = first->m_bfmeFlags;
	unsigned int b = second->m_bfmeFlags;

	// Written as two masked comparisons the compiler builds each xor on its
	// own; sharing one xor collapses the second test into a value.
	if ((b & 7) == (a & 7) && (b & 0xFC0) == (a & 0xFC0))
		return 1;

	return 0;
}
