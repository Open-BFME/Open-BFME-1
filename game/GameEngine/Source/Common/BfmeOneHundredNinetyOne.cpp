// Five walks and askings: a reading taken after a fix, a ring told what to do,
// a list searched by key, a run told two things, and a list asked until one
// answers.

class BfmeOtherEF;

class BfmeItemEF
{
public:
	virtual void bfmeSpare000EF(void) = 0;
	virtual void bfmeSpare001EF(void) = 0;
	virtual void bfmeSpare002EF(void) = 0;
	virtual void bfmeSpare003EF(void) = 0;
	virtual void bfmeSpare004EF(void) = 0;
	virtual void bfmeSpare005EF(void) = 0;
	virtual void bfmeSpare006EF(void) = 0;
	virtual void bfmeSpare007EF(void) = 0;
	virtual void bfmeSpare008EF(void) = 0;
	virtual void bfmeSpare009EF(void) = 0;
	virtual unsigned char bfmeAskEF(void) = 0;
	virtual void bfmeFixEF(void) = 0;

	unsigned char m_bfmeHead[0x10];		// 0x04
	BfmeOtherEF *m_bfmeOther;		// 0x14
};

struct BfmeOtherEF
{
	unsigned char m_bfmeHead[0x24];		// 0x00
	int m_bfmeValue;			// 0x24
};

class BfmeThingEF
{
public:
	int bfmeAskEF(void);

private:
	BfmeItemEF *m_bfmeItem;			// 0x0
};

int BfmeThingEF::bfmeAskEF(void)
{
	BfmeItemEF *item = m_bfmeItem;

	if (item == 0)
		return 0;

	if (item->bfmeAskEF() == 0)
		item->bfmeFixEF();

	BfmeOtherEF *other = item->m_bfmeOther;

	if (other != 0)
		return other->m_bfmeValue;

	return 1;
}


class BfmeTargetEG
{
public:
	virtual void bfmeSpare000EG(void) = 0;
	virtual void bfmeSpare001EG(void) = 0;
	virtual void bfmeSpare002EG(void) = 0;
	virtual void bfmeSpare003EG(void) = 0;
	virtual void bfmeSpare004EG(void) = 0;
	virtual void bfmeSpare005EG(void) = 0;
	virtual void bfmeSpare006EG(void) = 0;
	virtual void bfmeSpare007EG(void) = 0;
	virtual void bfmeSpare008EG(void) = 0;
	virtual void bfmeSpare009EG(void) = 0;
	virtual void bfmeSpare010EG(void) = 0;
	virtual void bfmeSpare011EG(void) = 0;
	virtual void bfmeSpare012EG(void) = 0;
	virtual void bfmeSpare013EG(void) = 0;
	virtual void bfmeSpare014EG(void) = 0;
	virtual void bfmeSpare015EG(void) = 0;
	virtual void bfmeSpare016EG(void) = 0;
	virtual void bfmeSpare017EG(void) = 0;
	virtual void bfmeSpare018EG(void) = 0;
	virtual void bfmeSpare019EG(void) = 0;
	virtual void bfmeSpare020EG(void) = 0;
	virtual void bfmeSpare021EG(void) = 0;
	virtual void bfmeSpare022EG(void) = 0;
	virtual void bfmeSpare023EG(void) = 0;
	virtual void bfmeSpare024EG(void) = 0;
	virtual void bfmeSpare025EG(void) = 0;
	virtual void bfmeSpare026EG(void) = 0;
	virtual void bfmeSpare027EG(void) = 0;
	virtual void bfmeSpare028EG(void) = 0;
	virtual void bfmeDoEG(void *what) = 0;
};

struct BfmeHolderEG
{
	unsigned char m_bfmeHead[0x1fc];	// 0x000
	BfmeTargetEG *m_bfmeTarget;		// 0x1fc
};

struct BfmeNodeEG
{
	BfmeNodeEG *m_bfmeNext;			// 0x0
	unsigned char m_bfmeGap[4];		// 0x4
	BfmeHolderEG *m_bfmeHolder;		// 0x8
};

class BfmeThingEG
{
public:
	void bfmeTellEG(void *what);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeNodeEG *m_bfmeRing;			// 0x4
};

void BfmeThingEG::bfmeTellEG(void *what)
{
	BfmeNodeEG *at = m_bfmeRing->m_bfmeNext;

	while (at != m_bfmeRing)
	{
		BfmeTargetEG *target = at->m_bfmeHolder->m_bfmeTarget;

		if (target != 0)
			target->bfmeDoEG(what);

		at = at->m_bfmeNext;
	}
}


class BfmeItemEH
{
public:
	virtual void bfmeSpare000EH(void) = 0;
	virtual void bfmeSpare001EH(void) = 0;
	virtual void bfmeSpare002EH(void) = 0;
	virtual void bfmeSpare003EH(void) = 0;
	virtual int bfmeKeyEH(void) = 0;
};

class BfmeThingEH
{
public:
	BfmeItemEH *bfmeFindEH(int key);

private:
	unsigned char m_bfmeHead[0x154];	// 0x000
	BfmeItemEH **m_bfmeList;		// 0x154
};

BfmeItemEH *BfmeThingEH::bfmeFindEH(int key)
{
	BfmeItemEH **at = m_bfmeList;

	if (at != 0)
	{
		BfmeItemEH *item = *at;

		while (item != 0)
		{
			if (item->bfmeKeyEH() == key)
				return *at;

			item = at[1];
			++at;
		}
	}

	return 0;
}


class BfmeItemEI
{
public:
	virtual void bfmeSpare000EI(void) = 0;
	virtual void bfmeSpare001EI(void) = 0;
	virtual void bfmeSpare002EI(void) = 0;
	virtual void bfmeDoEI(void *first, void *second) = 0;
};

class BfmeThingEI
{
public:
	void bfmeTellEI(void *first, void *second);

private:
	BfmeItemEI **m_bfmeBegin;		// 0x0
	BfmeItemEI **m_bfmeEnd;			// 0x4
};

void BfmeThingEI::bfmeTellEI(void *first, void *second)
{
	BfmeItemEI **at = m_bfmeBegin;

	while (at != m_bfmeEnd)
	{
		(*at)->bfmeDoEI(first, second);

		++at;
	}
}


class BfmeSubEJ
{
public:
	virtual void bfmeSpare000EJ(void);
	virtual void bfmeSpare001EJ(void);
	virtual void bfmeSpare002EJ(void);
	virtual void bfmeSpare003EJ(void);
	virtual void bfmeSpare004EJ(void);
	virtual void bfmeSpare005EJ(void);
	virtual void bfmeSpare006EJ(void);
	virtual void bfmeSpare007EJ(void);
	virtual void bfmeSpare008EJ(void);
	virtual void bfmeSpare009EJ(void);
	virtual void bfmeSpare010EJ(void);
	virtual void bfmeSpare011EJ(void);
	virtual void bfmeSpare012EJ(void);
	virtual void bfmeSpare013EJ(void);
	virtual void bfmeSpare014EJ(void);
	virtual void bfmeSpare015EJ(void);
	virtual void bfmeSpare016EJ(void);
	virtual void bfmeSpare017EJ(void);
	virtual void bfmeSpare018EJ(void);
	virtual void bfmeSpare019EJ(void);
	virtual void bfmeSpare020EJ(void);
	virtual void bfmeSpare021EJ(void);
	virtual void bfmeSpare022EJ(void);
	virtual void bfmeSpare023EJ(void);
	virtual void bfmeSpare024EJ(void);
	virtual void bfmeSpare025EJ(void);
	virtual void bfmeSpare026EJ(void);
	virtual int bfmeAskEJ(void);
};

struct BfmeItemEJ
{
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeSubEJ m_bfmeSub;			// 0xc
};

struct BfmeThingEJ
{
	unsigned char m_bfmeHead[0x1f0];	// 0x000
	BfmeItemEJ **m_bfmeList;		// 0x1f0
};

int bfmeFindEJ(BfmeThingEJ *thing)
{
	if (thing == 0)
		return 0;

	BfmeItemEJ **at = thing->m_bfmeList;

	while (*at != 0)
	{
		int answer = (*at)->m_bfmeSub.bfmeAskEJ();

		if (answer != 0)
			return answer;

		++at;
	}

	return 0;
}

