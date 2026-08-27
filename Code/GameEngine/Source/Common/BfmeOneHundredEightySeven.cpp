// Five errands over things that keep count of who is holding them, chains that
// are let go of link by link, and a couple of settings written down before the
// work is asked for.

class BfmeCountedDH
{
public:
	virtual void bfmeDoDH(int how) = 0;

	int m_bfmeCount;			// 0x4
};

class BfmeThingDH
{
public:
	void bfmeReleaseDH(void);

private:
	BfmeCountedDH *m_bfmeHeld;		// 0x0
};

void BfmeThingDH::bfmeReleaseDH(void)
{
	BfmeCountedDH *held = m_bfmeHeld;

	if (held == 0)
		return;

	int left = --held->m_bfmeCount;

	if (left <= 0)
		held->bfmeDoDH(1);

	m_bfmeHeld = 0;
}


struct BfmeNodeDJ
{
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeNodeDJ *m_bfmeNext;			// 0x4
};


class BfmeThingDJ
{
public:
	virtual void bfmeSpare000DJ(void) = 0;
	virtual void bfmeSpare001DJ(void) = 0;
	virtual void bfmeSpare002DJ(void) = 0;
	virtual void bfmeSpare003DJ(void) = 0;
	virtual void bfmeSpare004DJ(void) = 0;
	virtual void bfmeSpare005DJ(void) = 0;
	virtual void bfmeSpare006DJ(void) = 0;
	virtual void bfmeSpare007DJ(void) = 0;
	virtual void bfmeSpare008DJ(void) = 0;
	virtual void bfmeDoDJ(BfmeNodeDJ *node) = 0;

	void bfmeWalkDJ(BfmeNodeDJ *node);
};

void BfmeThingDJ::bfmeWalkDJ(BfmeNodeDJ *node)
{
	while (node != 0)
	{
		BfmeNodeDJ *next = node->m_bfmeNext;

		bfmeDoDJ(node);

		node = next;
	}
}


class BfmeThingDK
{
public:
	virtual void bfmeSpare000DK(void) = 0;
	virtual void bfmeSpare001DK(void) = 0;
	virtual void bfmeSpare002DK(void) = 0;
	virtual void bfmeDoDK(void) = 0;

	void bfmeSetDK(int what, int how);

private:
	unsigned char m_bfmeHead[0x20];		// 0x04
	int m_bfmeFirst;			// 0x24
	unsigned char m_bfmeGap[4];		// 0x28
	int m_bfmeWhat;				// 0x2c
	int m_bfmeNone;				// 0x30
	unsigned char m_bfmeSpare[0x10];	// 0x34
	int m_bfmeSecond;			// 0x44
	int m_bfmeHow;				// 0x48
};

void BfmeThingDK::bfmeSetDK(int what, int how)
{
	m_bfmeFirst = 2;
	m_bfmeSecond = 2;
	m_bfmeHow = how;
	m_bfmeWhat = what;
	m_bfmeNone = 0;

	bfmeDoDK();
}

class BfmeNodeDL
{
public:
	virtual void bfmeDoDL(int how) = 0;

	BfmeNodeDL *m_bfmeNext;			// 0x4
};

class BfmeThingDL
{
public:
	void bfmeClearDL(void);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	BfmeNodeDL *m_bfmeFirst;		// 0x8
	BfmeNodeDL *m_bfmeLast;			// 0xc
};

void BfmeThingDL::bfmeClearDL(void)
{
	BfmeNodeDL *at = m_bfmeFirst;

	while (at != 0)
	{
		BfmeNodeDL *next = at->m_bfmeNext;

		at->bfmeDoDL(1);

		at = next;
	}

	m_bfmeFirst = 0;
	m_bfmeLast = 0;
}

class BfmeItemDM
{
public:
	virtual void bfmeSpare000DM(void) = 0;
	virtual void bfmeDoDM(void) = 0;
};

class BfmeThingDM
{
public:
	void bfmeClearDM(void);

private:
	BfmeItemDM *m_bfmeOne;			// 0x0
	BfmeItemDM **m_bfmeBegin;		// 0x4
	BfmeItemDM **m_bfmeEnd;			// 0x8
};

void BfmeThingDM::bfmeClearDM(void)
{
	BfmeItemDM *one = m_bfmeOne;

	if (one != 0)
		one->bfmeDoDM();

	BfmeItemDM **at = m_bfmeBegin;

	while (at != m_bfmeEnd)
	{
		(*at)->bfmeDoDM();

		++at;
	}
}

