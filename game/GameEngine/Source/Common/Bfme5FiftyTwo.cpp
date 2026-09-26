// Five more: a search over a counted array, a two-step flag test, an index-of
// search, a pop that copies the top frame down, and another counted handle.

class BfmeSlotDV
{
public:
	int m_bfmeHead[2];					// +0x00
	void *m_bfmeKey;					// +0x08
	int m_bfmeTail[4];					// +0x0C
};

class Gen_007F7110
{
public:
	BfmeSlotDV *bfmeFind(void *key) const;

private:
	int m_bfmeHead[14];					// +0x00
	BfmeSlotDV *m_bfmeSlots;				// +0x38
	int m_bfmeCount;					// +0x3C
};

// ?bfmeFind@Gen_007F7110@@QBEPAVBfmeSlotDV@@PAX@Z
BfmeSlotDV *Gen_007F7110::bfmeFind(void *key) const
{
	BfmeSlotDV *first = m_bfmeSlots;
	BfmeSlotDV *last = m_bfmeSlots + m_bfmeCount;

	while (first < last)
	{
		if (first->m_bfmeKey == key)
			return first;

		++first;
	}

	return 0;
}

class BfmeThingDV
{
public:
	int m_bfmeHead[16];					// +0x00
	void *m_bfmeSlots[7];					// +0x40
	unsigned int m_bfmeFlags[7];				// +0x5C
};

// ?bfmeHasFlag@@YAHPBVBfmeThingDV@@H@Z
int __cdecl bfmeHasFlag(const BfmeThingDV *thing, int index)
{
	if (thing == 0)
		return 0;

	if (thing->m_bfmeSlots[index] == 0)
		return 0;

	return (thing->m_bfmeFlags[index] & 0x60) != 0;
}

class Gen_008A0690
{
public:
	int bfmeIndexOf(void *key) const;

private:
	int m_bfmeHead[3];					// +0x00
	int m_bfmeCount;					// +0x0C
	void **m_bfmeEntries;					// +0x10
};

// ?bfmeIndexOf@Gen_008A0690@@QBEHPAX@Z
int Gen_008A0690::bfmeIndexOf(void *key) const
{
	int count = m_bfmeCount;

	int index = 0;

	if (index < count)
	{
		void **entry = m_bfmeEntries;

		do
		{
			if (*entry == key)
				return index;

			++index;
			++entry;
		}
		while (index < count);
	}

	return -1;
}

class BfmeFrameDV
{
public:
	int m_bfmeData[8];					// 32 bytes
};

class Gen_008D2B80
{
public:
	void bfmePop(void);

private:
	BfmeFrameDV m_bfmeCurrent;				// +0x000
	char m_bfmeGap[0x18];					// +0x020
	BfmeFrameDV m_bfmeStack[28];				// +0x038
	int m_bfmeTop;						// +0x3B8
};

// ?bfmePop@Gen_008D2B80@@QAEXXZ
void Gen_008D2B80::bfmePop(void)
{
	--m_bfmeTop;

	m_bfmeCurrent = m_bfmeStack[m_bfmeTop];
}

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

class Gen_00929260
{
public:
	BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeHandleCX *m_bfmeSlots;				// +0x08
};

// ?bfmeGet@Gen_00929260@@QBE?AVBfmeHandleCX@@H@Z
BfmeHandleCX Gen_00929260::bfmeGet(int index) const
{
	return m_bfmeSlots[index];
}
