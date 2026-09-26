// Five more: the counted handle taken from a two-dimensional table in two
// classes, a global accumulator, an unlink, and a third saturating counter.

class BfmeThingCX
{
public:
	int m_bfmeHead;						// +0x00
	unsigned short m_bfmeRefs;				// +0x04
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void)
	{
		m_bfmeThing = 0;
	}

	BfmeHandleCX(const BfmeHandleCX &other)
	{
		BfmeThingCX *thing = other.m_bfmeThing;

		m_bfmeThing = thing;

		if (thing)
			++thing->m_bfmeRefs;
	}

	~BfmeHandleCX(void)
	{
		if (m_bfmeThing)
			--m_bfmeThing->m_bfmeRefs;
	}

	BfmeThingCX *m_bfmeThing;				// +0x00
};

class Gen_009292E0
{
public:
	BfmeHandleCX bfmeGet(int row, int column) const;

private:
	int m_bfmeHead[29];					// +0x00
	BfmeHandleCX m_bfmeSlots[8];				// +0x74
};

// ?bfmeGet@Gen_009292E0@@QBE?AVBfmeHandleCX@@HH@Z
BfmeHandleCX Gen_009292E0::bfmeGet(int row, int column) const
{
	return m_bfmeSlots[column + row * 2];
}

class Gen_0092C9D0
{
public:
	BfmeHandleCX bfmeGet(int row, int column) const;

private:
	int m_bfmeHead[29];					// +0x00
	BfmeHandleCX m_bfmeSlots[8];				// +0x74
};

// ?bfmeGet@Gen_0092C9D0@@QBE?AVBfmeHandleCX@@HH@Z
BfmeHandleCX Gen_0092C9D0::bfmeGet(int row, int column) const
{
	return m_bfmeSlots[column + row * 2];
}

extern int g_bfmeBytesEA;					// retail 0x01346E58
extern int g_bfmeCountEA;					// retail 0x01346E68
extern int g_bfmeBlocksEA;					// retail 0x01346E6C

// ?bfmeAccount@@YAXHH@Z
void __cdecl bfmeAccount(int bytes, int blocks)
{
	g_bfmeBytesEA = g_bfmeBytesEA + bytes;
	g_bfmeBlocksEA = g_bfmeBlocksEA + blocks;

	++g_bfmeCountEA;
}

class BfmeNodeEA
{
public:
	int m_bfmeHead[21];					// +0x00
	BfmeNodeEA *m_bfmePrev;					// +0x54
	BfmeNodeEA *m_bfmeNext;					// +0x58
};

// ?bfmeUnlink@@YAXPAVBfmeNodeEA@@@Z
void __cdecl bfmeUnlink(BfmeNodeEA *node)
{
	BfmeNodeEA *previous = node->m_bfmePrev;

	if (previous != 0)
		previous->m_bfmeNext = node->m_bfmeNext;

	BfmeNodeEA *next = node->m_bfmeNext;

	if (next != 0)
		next->m_bfmePrev = node->m_bfmePrev;

	node->m_bfmePrev = 0;
	node->m_bfmeNext = 0;
}

class Gen_008C3E90
{
public:
	void bfmeBump(void);

private:
	int m_bfmeHead;						// +0x00
	unsigned int m_bfmeBits;				// +0x04
};

// ?bfmeBump@Gen_008C3E90@@QAEXXZ
void Gen_008C3E90::bfmeBump(void)
{
	unsigned int bits = m_bfmeBits;

	unsigned int count = ((bits >> 16) & 0xFFF) + 1;

	if (count > 0xFFF)
		count = 0xFFF;

	m_bfmeBits = (bits & 0xF000FFFF) | (count << 16);
}
