// Five more: a counted handle taken from a global, a bounded element read that
// falls through null, a colour built from a flag, a constructor with two
// arguments, and a bounded table lookup.

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

extern BfmeHandleCX g_bfmeCurrentCZ;				// retail 0x01307214

// ?bfmeCurrent@@YA?AVBfmeHandleCX@@XZ
BfmeHandleCX __cdecl bfmeCurrent(void)
{
	return g_bfmeCurrentCZ;
}

class BfmeSlotCZ
{
public:
	int *m_bfmePointer;					// +0x00
	int m_bfmeTag;						// +0x04
};

class BfmeVecCZ
{
public:
	BfmeSlotCZ *m_bfmeStart;				// +0x00
	int m_bfmeCount;					// +0x04
};

// The out-of-range slot stays null and is read anyway, which is what puts the
// load in both paths.
// ?bfmeAt@@YGPAHPAVBfmeVecCZ@@H@Z
int * __stdcall bfmeAt(BfmeVecCZ *vector, int index)
{
	BfmeSlotCZ *slot;

	if (index >= vector->m_bfmeCount)
		slot = 0;
	else
		slot = vector->m_bfmeStart + index;

	return slot->m_bfmePointer;
}

class BfmeThingCZ
{
public:
	int m_bfmeHead[10];					// +0x00
	int m_bfmeColor;					// +0x28
};

// ?bfmeColor@@YGHPBVBfmeThingCZ@@H_N@Z
int __stdcall bfmeColor(const BfmeThingCZ *thing, int unused, bool bright)
{
	int color = thing->m_bfmeColor & 0xFFFFFF;

	color = color | 0x80000000;

	if (bright)
		color = color | 0x30000000;

	return color;
}

extern int g_bfmeVtableCZ[];					// retail 0x0112D210

class Gen_0081E480
{
public:
	Gen_0081E480(int first, int second);

private:
	int *m_bfmeVtable;					// +0x00
	int m_bfmeCount;					// +0x04
	int m_bfmeFirst;					// +0x08
	int m_bfmeSecond;					// +0x0C
	int m_bfmeFlags;					// +0x10
};

// ??0Gen_0081E480@@QAE@HH@Z
Gen_0081E480::Gen_0081E480(int first, int second)
{
	m_bfmeVtable = g_bfmeVtableCZ;
	m_bfmeCount = 0;
	m_bfmeFirst = first;
	m_bfmeSecond = second;
	m_bfmeFlags = 0;
}

class BfmeTableCZ
{
public:
	int m_bfmeHead;						// +0x00
	int **m_bfmeEntries;					// +0x04
	unsigned int m_bfmeCount;				// +0x08
};

class Gen_008321B0
{
public:
	int *bfmeLookup(const unsigned int *key) const;

private:
	BfmeTableCZ *m_bfmeTable;				// +0x00
};

// ?bfmeLookup@Gen_008321B0@@QBEPAHPBI@Z
int *Gen_008321B0::bfmeLookup(const unsigned int *key) const
{
	BfmeTableCZ *table = m_bfmeTable;

	unsigned int index = *key;

	if (index < table->m_bfmeCount)
		return table->m_bfmeEntries[index];

	return 0;
}
