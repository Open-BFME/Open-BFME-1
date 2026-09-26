// Five more: a one-bit store from a pointer test, another counted handle, a
// bounded lookup with a fallback, a walk of N steps, and an unlink.

class Gen_00892E90
{
public:
	void bfmeSetFlag(void *thing);

private:
	int m_bfmeHead[24];					// +0x00
	unsigned int m_bfmeLow : 17;				// +0x60
	unsigned int m_bfmeFlag : 1;				// +0x60
	unsigned int m_bfmeHigh : 14;				// +0x60
};

// ?bfmeSetFlag@Gen_00892E90@@QAEXPAX@Z
void Gen_00892E90::bfmeSetFlag(void *thing)
{
	m_bfmeFlag = (thing != 0);
}

class BfmeRefDB
{
public:
	int m_bfmeCount;					// +0x00
};

class BfmeHolderDB
{
public:
	BfmeHolderDB(void)
	{
		m_bfmeRef = 0;
	}

	BfmeHolderDB(const BfmeHolderDB &other)
	{
		BfmeRefDB *ref = other.m_bfmeRef;

		m_bfmeRef = ref;

		if (ref)
			++ref->m_bfmeCount;
	}

	~BfmeHolderDB(void)
	{
		if (m_bfmeRef)
			--m_bfmeRef->m_bfmeCount;
	}

	BfmeRefDB *m_bfmeRef;					// +0x00
};

class Gen_00895650
{
public:
	BfmeHolderDB bfmeGet(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeHolderDB m_bfmeHolder;				// +0x04
};

// ?bfmeGet@Gen_00895650@@QBE?AVBfmeHolderDB@@XZ
BfmeHolderDB Gen_00895650::bfmeGet(void) const
{
	return m_bfmeHolder;
}

extern int g_bfmeFallbackDB;					// retail 0x013379BC

class Gen_008B8E50
{
public:
	int bfmeAt(int index) const;

private:
	int m_bfmeHead[8];					// +0x00
	int *m_bfmeEntries;					// +0x20
	int m_bfmeGap;						// +0x24
	int m_bfmeCount;					// +0x28
};

// ?bfmeAt@Gen_008B8E50@@QBEHH@Z
int Gen_008B8E50::bfmeAt(int index) const
{
	if (index >= 0 && index < m_bfmeCount)
	{
		int value = m_bfmeEntries[index] & ~1;

		if (value != 0)
			return value;
	}

	return g_bfmeFallbackDB;
}

class BfmeNodeDB
{
public:
	int m_bfmeHead[22];					// +0x00
	BfmeNodeDB *m_bfmeNext;					// +0x58
};

class Gen_008BD1D0
{
public:
	BfmeNodeDB *bfmeAdvance(int count) const;

private:
	BfmeNodeDB *m_bfmeHead;					// +0x00
};

// ?bfmeAdvance@Gen_008BD1D0@@QBEPAVBfmeNodeDB@@H@Z
BfmeNodeDB *Gen_008BD1D0::bfmeAdvance(int count) const
{
	BfmeNodeDB *node = m_bfmeHead;

	while (node != 0)
	{
		if (count == 0)
			return node;

		node = node->m_bfmeNext;

		--count;
	}

	return 0;
}

class Gen_008F7AC0
{
public:
	void bfmeUnlink(void);

private:
	int m_bfmeHead[5];					// +0x00
	Gen_008F7AC0 **m_bfmePrev;				// +0x14
	Gen_008F7AC0 *m_bfmeNext;				// +0x18
};

// ?bfmeUnlink@Gen_008F7AC0@@QAEXXZ
void Gen_008F7AC0::bfmeUnlink(void)
{
	*m_bfmePrev = m_bfmeNext;

	Gen_008F7AC0 *next = m_bfmeNext;

	if (next != 0)
		next->m_bfmePrev = m_bfmePrev;

	m_bfmePrev = 0;
}
