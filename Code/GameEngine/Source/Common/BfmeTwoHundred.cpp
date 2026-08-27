// Four short errands: an item handed back only if it says yes, a charge let go
// of, two readings taken off a record, and a count wound down to nothing.

class BfmeItemGC
{
public:
	virtual void bfmeSpare000GC(void) = 0;
	virtual void bfmeSpare001GC(void) = 0;
	virtual void bfmeSpare002GC(void) = 0;
	virtual void bfmeSpare003GC(void) = 0;
	virtual void bfmeSpare004GC(void) = 0;
	virtual unsigned char bfmeAskGC(void) = 0;
};

BfmeItemGC *bfmeCheckGC(BfmeItemGC *item)
{
	if (item != 0 && item->bfmeAskGC() != 0)
		return item;

	return 0;
}

class BfmeItemGD;

struct BfmeOpsGD
{
	void (__stdcall *m_bfmeSpare)(BfmeItemGD *item);
	void (__stdcall *m_bfmeAlso)(BfmeItemGD *item);
	void (__stdcall *m_bfmeDrop)(BfmeItemGD *item);
};

struct BfmeItemGD
{
	BfmeOpsGD *m_bfmeOps;			// 0x0
};

class BfmeThingGD
{
public:
	int bfmeDropGD(void);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeItemGD *m_bfmeItem;			// 0x4
};

int BfmeThingGD::bfmeDropGD(void)
{
	BfmeItemGD *item = m_bfmeItem;

	if (item != 0)
		item->m_bfmeOps->m_bfmeDrop(item);

	m_bfmeItem = 0;

	return 1;
}


class BfmeSourceGE
{
public:
	virtual void bfmeSpare000GE(void) = 0;
	virtual void bfmeSpare001GE(void) = 0;
	virtual void bfmeSpare002GE(void) = 0;
	virtual void bfmeSpare003GE(void) = 0;
	virtual void bfmeSpare004GE(void) = 0;
	virtual void bfmeSpare005GE(void) = 0;
	virtual void bfmeSpare006GE(void) = 0;
	virtual void bfmeSpare007GE(void) = 0;
	virtual void bfmeSpare008GE(void) = 0;
	virtual void bfmeSpare009GE(void) = 0;
	virtual void bfmeSpare010GE(void) = 0;
	virtual void bfmeSpare011GE(void) = 0;
	virtual void bfmeSpare012GE(void) = 0;
	virtual void bfmeSpare013GE(void) = 0;
	virtual void bfmeSpare014GE(void) = 0;
	virtual void bfmeSpare015GE(void) = 0;
	virtual void bfmeSpare016GE(void) = 0;
	virtual void bfmeSpare017GE(void) = 0;
	virtual void bfmeSpare018GE(void) = 0;
	virtual void bfmeSpare019GE(void) = 0;
	virtual void bfmeSpare020GE(void) = 0;
	virtual void bfmeSpare021GE(void) = 0;
	virtual void bfmeSpare022GE(void) = 0;
	virtual void bfmeSpare023GE(void) = 0;
	virtual void bfmeSpare024GE(void) = 0;
	virtual void bfmeSpare025GE(void) = 0;
	virtual void bfmeSpare026GE(void) = 0;
	virtual void bfmeSpare027GE(void) = 0;
	virtual void bfmeSpare028GE(void) = 0;
	virtual void bfmeSpare029GE(void) = 0;
	virtual void bfmeDoGE(int *out) = 0;
};

class BfmeThingGE
{
public:
	void bfmeReadGE(BfmeSourceGE *src, int spare);

private:
	int m_bfmeFirst;			// 0x0
	int m_bfmeSecond;			// 0x4
};

void BfmeThingGE::bfmeReadGE(BfmeSourceGE *src, int spare)
{
	src->bfmeDoGE(&m_bfmeFirst);
	src->bfmeDoGE(&m_bfmeSecond);
}

class BfmeSubGG
{
public:
	virtual void bfmeDoGG(int *what);

	int m_bfmeValue;			// 0x4
};

class BfmeThingGG
{
public:
	int bfmeReleaseGG(void);

private:
	unsigned char m_bfmeHead[0x18];		// 0x00
	BfmeSubGG m_bfmeSub;			// 0x18
	unsigned char m_bfmeGap[0x58];		// 0x20
	int m_bfmeCount;			// 0x78
};

int BfmeThingGG::bfmeReleaseGG(void)
{
	if (m_bfmeCount > 0)
	{
		if (--m_bfmeCount == 0)
			m_bfmeSub.bfmeDoGG(&m_bfmeSub.m_bfmeValue);
	}

	return 1;
}

