// Two errands: a newcomer marked when it is not already known, and a chain let
// go of link by link.

struct BfmePairIA
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};


class BfmeItemIA
{
public:
	virtual void bfmeSpare000IA(void) = 0;
	virtual void bfmeSpare001IA(void) = 0;
	virtual void bfmeSpare002IA(void) = 0;
	virtual void bfmeSpare003IA(void) = 0;
	virtual unsigned char bfmeIsIA(void) = 0;
	virtual void bfmeSpare005IA(void) = 0;
	virtual void bfmeSpare006IA(void) = 0;
	virtual void bfmeSpare007IA(void) = 0;
	virtual void bfmeSpare008IA(void) = 0;
	virtual void bfmeSpare009IA(void) = 0;
	virtual void bfmeMarkIA(BfmePairIA *both) = 0;
};

class BfmeThingIA
{
public:
	void bfmeTakeIA(BfmeItemIA *item);
};

void BfmeThingIA::bfmeTakeIA(BfmeItemIA *item)
{
	if (item->bfmeIsIA() == 0)
	{
		BfmePairIA both;

		both.m_bfmeFirst = 1;
		both.m_bfmeSecond = 1;

		item->bfmeMarkIA(&both);
	}
}

class BfmeNodeIB
{
public:
	virtual void bfmeGoneIB(int how) = 0;

	BfmeNodeIB *m_bfmeNext;			// 0x4
};

class BfmeThingIB
{
public:
	void bfmeClearIB(void);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	BfmeNodeIB *m_bfmeFirst;		// 0x8
	BfmeNodeIB *m_bfmeLast;			// 0xc
};

void BfmeThingIB::bfmeClearIB(void)
{
	BfmeNodeIB *at = m_bfmeFirst;

	while (at != 0)
	{
		BfmeNodeIB *next = at->m_bfmeNext;

		at->bfmeGoneIB(1);

		at = next;
	}

	m_bfmeFirst = 0;
	m_bfmeLast = 0;
}
