// Four more: another counted handle, two index-of searches over wider
// elements, and a pair built around a counted handle.

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

class Gen_0092F0A0
{
public:
	BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[9];					// +0x00
	BfmeHandleCX *m_bfmeSlots;				// +0x24
};

// ?bfmeGet@Gen_0092F0A0@@QBE?AVBfmeHandleCX@@H@Z
BfmeHandleCX Gen_0092F0A0::bfmeGet(int index) const
{
	return m_bfmeSlots[index];
}

class BfmeTripleDW
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeTail[2];					// +0x04
};

class Gen_00938010
{
public:
	int bfmeIndexOf(const int *key) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeTripleDW *m_bfmeEntries;				// +0x04
	int m_bfmeGap[2];					// +0x08
	int m_bfmeCount;					// +0x10
};

// ?bfmeIndexOf@Gen_00938010@@QBEHPBH@Z
int Gen_00938010::bfmeIndexOf(const int *key) const
{
	int count = m_bfmeCount;

	int index = 0;

	if (index < count)
	{
		int value = *key;

		BfmeTripleDW *entry = m_bfmeEntries;

		do
		{
			if (entry->m_bfmeFirst == value)
				return index;

			++index;
			++entry;
		}
		while (index < count);
	}

	return -1;
}

class BfmeQuadDW
{
public:
	int m_bfmeHead[2];					// +0x00
	void *m_bfmeKey;					// +0x08
	int m_bfmeTail;						// +0x0C
};

class Gen_008A06C0
{
public:
	int bfmeIndexOf(void *key) const;

private:
	int m_bfmeHead[8];					// +0x00
	int m_bfmeCount;					// +0x20
	BfmeQuadDW *m_bfmeEntries;				// +0x24
};

// ?bfmeIndexOf@Gen_008A06C0@@QBEHPAX@Z
int Gen_008A06C0::bfmeIndexOf(void *key) const
{
	int count = m_bfmeCount;

	int index = 0;

	if (index < count)
	{
		BfmeQuadDW *entry = m_bfmeEntries;

		do
		{
			if (entry->m_bfmeKey == key)
				return index;

			++index;
			++entry;
		}
		while (index < count);
	}

	return -1;
}

class BfmePairDW
{
public:
	BfmePairDW(int tag, const BfmeHandleCX &handle)
		: m_bfmeTag(tag),
		  m_bfmeHandle(handle)
	{
	}

	int m_bfmeTag;						// +0x00
	BfmeHandleCX m_bfmeHandle;				// +0x04
};

// ?bfmeMakePair@@YA?AVBfmePairDW@@PBHPBVBfmeHandleCX@@@Z
BfmePairDW __cdecl bfmeMakePair(const int *tag, const BfmeHandleCX *handle)
{
	return BfmePairDW(*tag, *handle);
}
