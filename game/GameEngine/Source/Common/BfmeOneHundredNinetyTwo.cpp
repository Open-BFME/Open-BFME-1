// Five errands: two counts let go of together, four readings taken along a
// chain, a thing forgotten wherever it was noted, a pair of marks handed over
// with an item, and a record emptied when nothing is holding it.

class BfmeCountedEK
{
public:
	virtual void bfmeGoneEK(void) = 0;

	int m_bfmeCount;			// 0x4
};

class BfmeThingEK
{
public:
	void bfmeClearEK(void);

private:
	BfmeCountedEK *m_bfmeFirst;		// 0x0
	unsigned char m_bfmeGap[4];		// 0x4
	BfmeCountedEK *m_bfmeSecond;		// 0x8
};

void BfmeThingEK::bfmeClearEK(void)
{
	BfmeCountedEK *first = m_bfmeFirst;

	if (first != 0)
	{
		if (--first->m_bfmeCount == 0)
			first->bfmeGoneEK();

		m_bfmeFirst = 0;
	}

	BfmeCountedEK *second = m_bfmeSecond;

	if (second != 0)
	{
		if (--second->m_bfmeCount == 0)
			second->bfmeGoneEK();

		m_bfmeSecond = 0;
	}
}


class BfmeChainEL
{
public:
	virtual void bfmeSpare000EL(void) = 0;
	virtual void bfmeSpare001EL(void) = 0;
	virtual void bfmeSpare002EL(void) = 0;
	virtual void bfmeSpare003EL(void) = 0;
	virtual void bfmeSpare004EL(void) = 0;
	virtual void bfmeSpare005EL(void) = 0;
	virtual void bfmeSpare006EL(void) = 0;
	virtual void bfmeSpare007EL(void) = 0;
	virtual void bfmeSpare008EL(void) = 0;
	virtual void bfmeSpare009EL(void) = 0;
	virtual void bfmeSpare010EL(void) = 0;
	virtual void bfmeSpare011EL(void) = 0;
	virtual void bfmeSpare012EL(void) = 0;
	virtual void bfmeSpare013EL(void) = 0;
	virtual void bfmeSpare014EL(void) = 0;
	virtual void bfmeSpare015EL(void) = 0;
	virtual void bfmeSpare016EL(void) = 0;
	virtual void bfmeSpare017EL(void) = 0;
	virtual void bfmeSpare018EL(void) = 0;
	virtual void bfmeSpare019EL(void) = 0;
	virtual void bfmeSpare020EL(void) = 0;
	virtual void bfmeSpare021EL(void) = 0;
	virtual void bfmeSpare022EL(void) = 0;
	virtual void bfmeSpare023EL(void) = 0;
	virtual void bfmeSpare024EL(void) = 0;
	virtual void bfmeSpare025EL(void) = 0;
	virtual void bfmeSpare026EL(void) = 0;
	virtual BfmeChainEL *bfmeStepEL(int *out) = 0;
};

void bfmeReadEL(BfmeChainEL *at, int *out)
{
	at = at->bfmeStepEL(&out[0]);
	at = at->bfmeStepEL(&out[1]);
	at = at->bfmeStepEL(&out[2]);

	at->bfmeStepEL(&out[3]);
}


class BfmeThingEM
{
public:
	virtual void bfmeSpare000EM(void) = 0;
	virtual void bfmeSpare001EM(void) = 0;
	virtual void bfmeSpare002EM(void) = 0;
	virtual void bfmeSpare003EM(void) = 0;
	virtual void bfmeSpare004EM(void) = 0;
	virtual void bfmeSpare005EM(void) = 0;
	virtual void bfmeSpare006EM(void) = 0;
	virtual void bfmeSpare007EM(void) = 0;
	virtual void bfmeSpare008EM(void) = 0;
	virtual void bfmeSpare009EM(void) = 0;
	virtual void bfmeSpare010EM(void) = 0;
	virtual void bfmeSpare011EM(void) = 0;
	virtual void bfmeSpare012EM(void) = 0;
	virtual void bfmeSpare013EM(void) = 0;
	virtual void bfmeSpare014EM(void) = 0;
	virtual void bfmeSpare015EM(void) = 0;
	virtual void bfmeSpare016EM(void) = 0;
	virtual void bfmeSpare017EM(void) = 0;
	virtual void bfmeSpare018EM(void) = 0;
	virtual void bfmeSpare019EM(void) = 0;
	virtual void bfmeSpare020EM(void) = 0;
	virtual void bfmeSpare021EM(void) = 0;
	virtual void bfmeSpare022EM(void) = 0;
	virtual void bfmeSpare023EM(void) = 0;
	virtual void bfmeSpare024EM(void) = 0;
	virtual void bfmeSpare025EM(void) = 0;
	virtual void bfmeSpare026EM(void) = 0;
	virtual void bfmeSpare027EM(void) = 0;
	virtual void bfmeSpare028EM(void) = 0;
	virtual void bfmeSpare029EM(void) = 0;
	virtual void bfmeTellEM(void *what) = 0;

	void bfmeDropEM(void *what);

private:
	unsigned char m_bfmeHead[0x1708c];	// 0x00004
	void *m_bfmeSecond;			// 0x17090
	unsigned char m_bfmeGap[4];		// 0x17094
	void *m_bfmeFirst;			// 0x17098
};

void BfmeThingEM::bfmeDropEM(void *what)
{
	bfmeTellEM(what);

	if (m_bfmeFirst == what)
		m_bfmeFirst = 0;

	if (m_bfmeSecond == what)
		m_bfmeSecond = 0;
}

struct BfmePairEN
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};


class BfmeItemEN
{
public:
	virtual void bfmeSpare000EN(void) = 0;
	virtual void bfmeSpare001EN(void) = 0;
	virtual void bfmeSpare002EN(void) = 0;
	virtual void bfmeSpare003EN(void) = 0;
	virtual void bfmeSpare004EN(void) = 0;
	virtual void bfmeSpare005EN(void) = 0;
	virtual void bfmeSpare006EN(void) = 0;
	virtual void bfmeSpare007EN(void) = 0;
	virtual void bfmeSpare008EN(void) = 0;
	virtual void bfmeSpare009EN(void) = 0;
	virtual void bfmeDoEN(BfmePairEN *both) = 0;
};

class BfmeSubEN
{
public:
	virtual void bfmeSpare000EP(void);
	virtual void bfmeSpare001EP(void);
	virtual void bfmeSpare002EP(void);
	virtual void bfmeAlsoEN(BfmeItemEN *item);
};

class BfmeThingEN
{
public:
	void bfmeGoEN(BfmeItemEN *item);

private:
	unsigned char m_bfmeHead[0x170];	// 0x000
	BfmeSubEN m_bfmeSub;			// 0x170
};

void BfmeThingEN::bfmeGoEN(BfmeItemEN *item)
{
	BfmePairEN both;

	both.m_bfmeFirst = 1;
	both.m_bfmeSecond = 1;

	item->bfmeDoEN(&both);

	m_bfmeSub.bfmeAlsoEN(item);
}


class BfmeTargetEO
{
public:
	virtual void bfmeSpare000EO(void) = 0;
	virtual void bfmeSpare001EO(void) = 0;
	virtual void bfmeSpare002EO(void) = 0;
	virtual void bfmeSpare003EO(void) = 0;
	virtual void bfmeSpare004EO(void) = 0;
	virtual void bfmeDoEO(int how) = 0;
};

class BfmeThingEO
{
public:
	void bfmeClearEO(void);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeTargetEO *m_bfmeTarget;		// 0x1c
	int m_bfmeWords[8];			// 0x20
	unsigned char m_bfmeLocked;		// 0x40
};

void BfmeThingEO::bfmeClearEO(void)
{
	if (m_bfmeLocked != 0)
		return;

	BfmeTargetEO *target = m_bfmeTarget;

	if (target != 0)
		target->bfmeDoEO(1);

	m_bfmeTarget = 0;

	m_bfmeWords[0] = 0;
	m_bfmeWords[1] = 0;
	m_bfmeWords[2] = 0;
	m_bfmeWords[3] = 0;
	m_bfmeWords[4] = 0;
	m_bfmeWords[5] = 0;
	m_bfmeWords[6] = 0;
	m_bfmeWords[7] = 0;
}

