// Two sweeps: every record still standing in the ring let go of according to
// what it holds before both ends are drawn back to the start, and every link of
// the record ring asked, then asked again, before it is told the word.

class BfmeHeldLN
{
public:
	virtual void bfmeSpare000LN(void) = 0;
	virtual void bfmeDropLN(void) = 0;
};

struct BfmeRecLN
{
	int m_bfmeKind;				// 0x00
	unsigned char m_bfmeGap[4];		// 0x04
	BfmeHeldLN *m_bfmeFirst;		// 0x08
	BfmeHeldLN *m_bfmeSecond;		// 0x0c
	BfmeHeldLN *m_bfmeThird;		// 0x10
};

class BfmeThingLN
{
public:
	void bfmeClearLN(void);

private:
	BfmeRecLN *m_bfmeRing;			// 0x0000
	BfmeRecLN *m_bfmeHead;			// 0x0004
	BfmeRecLN *m_bfmeTail;			// 0x0008
	unsigned char m_bfmeGap[0x12a4];	// 0x000c
	int m_bfmeRoom;				// 0x12b0
};

void BfmeThingLN::bfmeClearLN(void)
{
	BfmeRecLN *at = m_bfmeHead;

	while (at != m_bfmeTail)
	{
		if (at->m_bfmeKind == 0)
		{
			at->m_bfmeThird->bfmeDropLN();
		}
		else if (at->m_bfmeKind == 1)
		{
			at->m_bfmeFirst->bfmeDropLN();

			at->m_bfmeSecond->bfmeDropLN();
		}

		++at;

		if (at == m_bfmeRing + m_bfmeRoom)
			at = m_bfmeRing;
	}

	m_bfmeTail = m_bfmeRing;
	m_bfmeHead = m_bfmeRing;
}


class BfmeItemLO
{
public:
	virtual void bfmeSpare000LO(void) = 0;
	virtual unsigned char bfmeWantLO(void *one, void *two) = 0;
	virtual void bfmeSpare002LO(void) = 0;
	virtual void bfmeSpare003LO(void) = 0;
	virtual void bfmeSpare004LO(void) = 0;
	virtual void bfmeDoLO(void *one, void *two) = 0;
	virtual void bfmeSpare006LO(void) = 0;
	virtual unsigned char bfmeAskLO(void) = 0;
};

struct BfmeLinkLO
{
	BfmeLinkLO *m_bfmeNext;			// 0x0
	unsigned char m_bfmeGap[4];		// 0x4
	BfmeItemLO *m_bfmeItem;			// 0x8
};

class BfmeThingLO
{
public:
	void bfmeTellLO(void *one, void *two, void *three, void *four);

private:
	unsigned char m_bfmeHead[0x538];	// 0x000
	BfmeLinkLO *m_bfmeRing;			// 0x538
};

void BfmeThingLO::bfmeTellLO(void *one, void *two, void *three, void *four)
{
	if (two == 0)
		return;

	if (three == 0)
		return;

	BfmeLinkLO *ring = m_bfmeRing;

	for (BfmeLinkLO *at = ring->m_bfmeNext; at != m_bfmeRing; at = at->m_bfmeNext)
	{
		BfmeItemLO *item = at->m_bfmeItem;

		if (item->bfmeAskLO() != 0)
		{
			if (item->bfmeWantLO(one, three) != 0)
				item->bfmeDoLO(one, three);
		}
	}
}

