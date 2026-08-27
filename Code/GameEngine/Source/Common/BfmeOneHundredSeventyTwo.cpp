// A search through a run of entries for one carrying a given key, and a
// countdown that either runs out and starts again or steps down by one.

struct BfmeEntryBB
{
	int m_bfmeKey;				// 0x00
	unsigned char m_bfmeBody[0x18];		// 0x04
};

class BfmeTableBB
{
public:
	BfmeEntryBB *bfmeFindBB(int key) const;

private:
	unsigned char m_bfmeHead[0xa4];		// 0x00
	BfmeEntryBB *m_bfmeBegin;		// 0xa4
	BfmeEntryBB *m_bfmeEnd;			// 0xa8
};

BfmeEntryBB *BfmeTableBB::bfmeFindBB(int key) const
{
	BfmeEntryBB *at = m_bfmeBegin;
	BfmeEntryBB *end = m_bfmeEnd;

	while (at != end)
	{
		if (at->m_bfmeKey == key)
			return at;

		++at;
	}

	return 0;
}

struct BfmeKindBA
{
	unsigned char m_bfmeHead[8];		// 0x00
	int m_bfmeEvery;			// 0x08
	unsigned char m_bfmeBody[0x31];		// 0x0c
	unsigned char m_bfmeAlways;		// 0x3d
};

class BfmeThingBA
{
public:
	unsigned char bfmeDueBA(void);

private:
	int m_bfmeFirst;			// 0x00
	BfmeKindBA *m_bfmeKind;			// 0x04
	unsigned char m_bfmeGap[0x1c];		// 0x08
	int m_bfmeLeft;				// 0x24
	unsigned char m_bfmeForced;		// 0x28
};

unsigned char BfmeThingBA::bfmeDueBA(void)
{
	BfmeKindBA *kind = m_bfmeKind;

	if (kind->m_bfmeAlways != 0)
		return m_bfmeForced;

	if (m_bfmeLeft == 0)
	{
		m_bfmeLeft = kind->m_bfmeEvery;

		return 1;
	}

	--m_bfmeLeft;

	return 0;
}
