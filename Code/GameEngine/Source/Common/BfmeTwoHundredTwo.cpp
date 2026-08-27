// Four more errands of shapes already met: a reading taken after a fix, a
// charge swapped for the next, a list searched by key, and a ring told what to
// do.

class BfmeOtherGN;

class BfmeItemGN
{
public:
	virtual void bfmeSpare000GN(void) = 0;
	virtual void bfmeSpare001GN(void) = 0;
	virtual void bfmeSpare002GN(void) = 0;
	virtual void bfmeSpare003GN(void) = 0;
	virtual void bfmeSpare004GN(void) = 0;
	virtual void bfmeSpare005GN(void) = 0;
	virtual void bfmeSpare006GN(void) = 0;
	virtual void bfmeSpare007GN(void) = 0;
	virtual void bfmeSpare008GN(void) = 0;
	virtual void bfmeSpare009GN(void) = 0;
	virtual unsigned char bfmeAskGN(void) = 0;
	virtual void bfmeFixGN(void) = 0;

	unsigned char m_bfmeHead[0x10];		// 0x04
	BfmeOtherGN *m_bfmeOther;		// 0x14
};

struct BfmeOtherGN
{
	unsigned char m_bfmeHead[0x28];		// 0x00
	int m_bfmeValue;			// 0x28
};

class BfmeThingGN
{
public:
	int bfmeAskGN(void);

private:
	BfmeItemGN *m_bfmeItem;			// 0x0
};

int BfmeThingGN::bfmeAskGN(void)
{
	BfmeItemGN *item = m_bfmeItem;

	if (item == 0)
		return 0;

	if (item->bfmeAskGN() == 0)
		item->bfmeFixGN();

	BfmeOtherGN *other = item->m_bfmeOther;

	if (other != 0)
		return other->m_bfmeValue;

	return 1;
}

class BfmeTargetGT
{
public:
	virtual void bfmeGoneGT(int how) = 0;
	virtual void bfmeSpare001GT(void) = 0;
	virtual void bfmeSpare002GT(void) = 0;
	virtual void bfmeSpare003GT(void) = 0;
	virtual void bfmeSpare004GT(void) = 0;
	virtual void bfmeSpare005GT(void) = 0;
	virtual void bfmeSpare006GT(void) = 0;
	virtual void bfmeSpare007GT(void) = 0;
	virtual void bfmeSpare008GT(void) = 0;
	virtual void bfmeSpare009GT(void) = 0;
	virtual void bfmeSpare010GT(void) = 0;
	virtual void bfmeSpare011GT(void) = 0;
	virtual void bfmeSpare012GT(void) = 0;
	virtual void bfmeSpare013GT(void) = 0;
	virtual void bfmeSpare014GT(void) = 0;
	virtual void bfmeStopGT(void) = 0;
};

class BfmeThingGT
{
public:
	void bfmeSwapGT(void);

private:
	unsigned char m_bfmeHead[0x30];		// 0x00
	BfmeTargetGT *m_bfmeCurrent;		// 0x30
	unsigned char m_bfmeGap[4];		// 0x34
	BfmeTargetGT *m_bfmeNext;		// 0x38
};

void BfmeThingGT::bfmeSwapGT(void)
{
	if (m_bfmeNext == 0)
		return;

	BfmeTargetGT *current = m_bfmeCurrent;

	if (current != 0)
	{
		current->bfmeStopGT();

		if (m_bfmeCurrent != 0)
			m_bfmeCurrent->bfmeGoneGT(1);

		m_bfmeCurrent = 0;
	}

	m_bfmeCurrent = m_bfmeNext;
	m_bfmeNext = 0;
}


class BfmeItemGU
{
public:
	virtual void bfmeSpare000GU(void) = 0;
	virtual void bfmeSpare001GU(void) = 0;
	virtual void bfmeSpare002GU(void) = 0;
	virtual void bfmeSpare003GU(void) = 0;
	virtual int bfmeKeyGU(void) = 0;
};

class BfmeThingGU
{
public:
	BfmeItemGU *bfmeFindGU(int key);

private:
	unsigned char m_bfmeHead[0x158];	// 0x000
	BfmeItemGU **m_bfmeList;		// 0x158
};

BfmeItemGU *BfmeThingGU::bfmeFindGU(int key)
{
	BfmeItemGU **at = m_bfmeList;

	if (at != 0)
	{
		BfmeItemGU *item = *at;

		while (item != 0)
		{
			if (item->bfmeKeyGU() == key)
				return *at;

			item = at[1];
			++at;
		}
	}

	return 0;
}


class BfmeTargetGV
{
public:
	virtual void bfmeSpare000GV(void) = 0;
	virtual void bfmeSpare001GV(void) = 0;
	virtual void bfmeSpare002GV(void) = 0;
	virtual void bfmeSpare003GV(void) = 0;
	virtual void bfmeSpare004GV(void) = 0;
	virtual void bfmeSpare005GV(void) = 0;
	virtual void bfmeSpare006GV(void) = 0;
	virtual void bfmeSpare007GV(void) = 0;
	virtual void bfmeSpare008GV(void) = 0;
	virtual void bfmeSpare009GV(void) = 0;
	virtual void bfmeSpare010GV(void) = 0;
	virtual void bfmeSpare011GV(void) = 0;
	virtual void bfmeSpare012GV(void) = 0;
	virtual void bfmeSpare013GV(void) = 0;
	virtual void bfmeSpare014GV(void) = 0;
	virtual void bfmeSpare015GV(void) = 0;
	virtual void bfmeSpare016GV(void) = 0;
	virtual void bfmeSpare017GV(void) = 0;
	virtual void bfmeSpare018GV(void) = 0;
	virtual void bfmeSpare019GV(void) = 0;
	virtual void bfmeSpare020GV(void) = 0;
	virtual void bfmeSpare021GV(void) = 0;
	virtual void bfmeSpare022GV(void) = 0;
	virtual void bfmeSpare023GV(void) = 0;
	virtual void bfmeSpare024GV(void) = 0;
	virtual void bfmeSpare025GV(void) = 0;
	virtual void bfmeSpare026GV(void) = 0;
	virtual void bfmeSpare027GV(void) = 0;
	virtual void bfmeSpare028GV(void) = 0;
	virtual void bfmeSpare029GV(void) = 0;
	virtual void bfmeDoGV(void *what) = 0;
};

struct BfmeHolderGV
{
	unsigned char m_bfmeHead[0x1fc];	// 0x000
	BfmeTargetGV *m_bfmeTarget;		// 0x1fc
};

struct BfmeNodeGV
{
	BfmeNodeGV *m_bfmeNext;			// 0x0
	unsigned char m_bfmeGap[4];		// 0x4
	BfmeHolderGV *m_bfmeHolder;		// 0x8
};

class BfmeThingGV
{
public:
	void bfmeTellGV(void *what);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeNodeGV *m_bfmeRing;			// 0x4
};

void BfmeThingGV::bfmeTellGV(void *what)
{
	BfmeNodeGV *at = m_bfmeRing->m_bfmeNext;

	while (at != m_bfmeRing)
	{
		BfmeTargetGV *target = at->m_bfmeHolder->m_bfmeTarget;

		if (target != 0)
			target->bfmeDoGV(what);

		at = at->m_bfmeNext;
	}
}

