// Four more: the counted handle taken from a global table and from a member
// table, a three-way kind test that keeps its frame, and a global array reset.

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

extern BfmeHandleCX g_bfmeTableDU[];				// retail 0x012F9D28

// ?bfmeGet@@YA?AVBfmeHandleCX@@H@Z
BfmeHandleCX __cdecl bfmeGet(int index)
{
	return g_bfmeTableDU[index];
}

class Gen_007A0340
{
public:
	BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[9];					// +0x00
	BfmeHandleCX *m_bfmeSlots;				// +0x24
};

// ?bfmeGet@Gen_007A0340@@QBE?AVBfmeHandleCX@@H@Z
BfmeHandleCX Gen_007A0340::bfmeGet(int index) const
{
	return m_bfmeSlots[index];
}

#pragma optimize("y", off)

// ?bfmeIsBasic@@YGHH@Z
int __stdcall bfmeIsBasic(int kind)
{
	if (kind == 0 || kind == 1 || kind == 2)
		return 1;

	return 0;
}

#pragma optimize("y", on)

class BfmeTripleDU
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

extern BfmeTripleDU g_bfmeEntriesDU[16];			// retail 0x013378E0
extern int g_bfmeCountDU;					// retail 0x013379A4

// ?bfmeResetAll@@YAXXZ
void __cdecl bfmeResetAll(void)
{
	g_bfmeCountDU = 0;

	// The walk counts on a signed index the compiler turns into an address,
	// which is why the bound compare stays signed.
	for (int index = 0; index < 16; ++index)
	{
		g_bfmeEntriesDU[index].m_bfmeThird = 0;
		g_bfmeEntriesDU[index].m_bfmeFirst = 0;
		g_bfmeEntriesDU[index].m_bfmeSecond = 0;
	}
}
