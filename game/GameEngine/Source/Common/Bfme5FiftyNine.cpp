// Three more: a fill over thirty-six byte elements, a clamped table read, and
// a walk that hands back the element after the match.

class BfmeItemEE
{
public:
	int m_bfmeData[9];					// 36 bytes
};

// ?bfmeFillNine@@YAXPAVBfmeItemEE@@0PBV1@@Z
void __cdecl bfmeFillNine(BfmeItemEE *first, BfmeItemEE *last, const BfmeItemEE *value)
{
	while (first != last)
	{
		*first = *value;

		++first;
	}
}

class BfmeStateEE
{
public:
	char m_bfmeHead[0x170C];				// +0x0000
	int m_bfmeLevel;					// +0x170C
};

extern BfmeStateEE *g_bfmeStateEE;				// retail 0x012ED5AC

class BfmeRowEE
{
public:
	float m_bfmeValue;					// +0x00
	int m_bfmeTail[4];					// +0x04
};

class Gen_00752F00
{
public:
	float bfmeValue(void) const;

private:
	char m_bfmeHead[0x168];					// +0x000
	BfmeRowEE m_bfmeRows[3];				// +0x168
};

// ?bfmeValue@Gen_00752F00@@QBEMXZ
float Gen_00752F00::bfmeValue(void) const
{
	int level = g_bfmeStateEE->m_bfmeLevel - 1;

	if (level < 0)
		level = 0;
	else if (level > 2)
		level = 2;

	return m_bfmeRows[level].m_bfmeValue;
}

class BfmeItemED
{
public:
	char m_bfmeBody[0xBC];					// 188 bytes
};

class Gen_0075F1D0
{
public:
	BfmeItemED *bfmeFindNext(BfmeItemED *item) const;

private:
	int m_bfmeHead[9];					// +0x00
	BfmeItemED *m_bfmeStart;				// +0x24
	BfmeItemED *m_bfmeFinish;				// +0x28
};

// ?bfmeFindNext@Gen_0075F1D0@@QBEPAVBfmeItemED@@PAV2@@Z
BfmeItemED *Gen_0075F1D0::bfmeFindNext(BfmeItemED *item) const
{
	BfmeItemED *entry = m_bfmeStart;
	BfmeItemED *finish = m_bfmeFinish;

	bool found = false;

	while (entry != finish)
	{
		if (found)
			return entry;

		if (entry == item)
			found = true;

		++entry;
	}

	return 0;
}
