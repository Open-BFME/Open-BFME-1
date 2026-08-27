// Three errands: five readings taken in turn twice over, and three charges let
// go of together.

class BfmeThingFC;

class BfmeSourceFC
{
public:
	virtual void bfmeSpare000FC(void) = 0;
	virtual void bfmeSpare001FC(void) = 0;
	virtual void bfmeSpare002FC(void) = 0;
	virtual void bfmeSpare003FC(void) = 0;
	virtual void bfmeSpare004FC(void) = 0;
	virtual void bfmeSpare005FC(void) = 0;
	virtual void bfmeSpare006FC(void) = 0;
	virtual void bfmeSpare007FC(void) = 0;
	virtual void bfmeSpare008FC(void) = 0;
	virtual void bfmeSpare009FC(void) = 0;
	virtual void bfmeSpare010FC(void) = 0;
	virtual void bfmeSpare011FC(void) = 0;
	virtual void bfmeSpare012FC(void) = 0;
	virtual void bfmeSpare013FC(void) = 0;
	virtual void bfmeSpare014FC(void) = 0;
	virtual void bfmeSpare015FC(void) = 0;
	virtual void bfmeSpare016FC(void) = 0;
	virtual void bfmeSpare017FC(void) = 0;
	virtual void bfmeSpare018FC(void) = 0;
	virtual void bfmeSpare019FC(void) = 0;
	virtual void bfmeSpare020FC(void) = 0;
	virtual void bfmeSpare021FC(void) = 0;
	virtual void bfmeSpare022FC(void) = 0;
	virtual void bfmeSpare023FC(void) = 0;
	virtual void bfmeFirstFC(BfmeThingFC *thing) = 0;
	virtual void bfmeSpare025FC(void) = 0;
	virtual void bfmeSpare026FC(void) = 0;
	virtual void bfmeNextFC(int *out) = 0;
	virtual void bfmeSpare028FC(void) = 0;
	virtual void bfmeLastFC(int *out) = 0;
};

class BfmeThingFC
{
public:
	void bfmeReadFC(BfmeSourceFC *src);

	unsigned char m_bfmeHead[0xc];		// 0x00
	int m_bfmeFirst;			// 0x0c
	int m_bfmeSecond;			// 0x10
	int m_bfmeThird;			// 0x14
	int m_bfmeFourth;			// 0x18
};

void BfmeThingFC::bfmeReadFC(BfmeSourceFC *src)
{
	src->bfmeFirstFC(this);
	src->bfmeNextFC(&m_bfmeFirst);
	src->bfmeNextFC(&m_bfmeSecond);
	src->bfmeNextFC(&m_bfmeThird);
	src->bfmeLastFC(&m_bfmeFourth);
}

BfmeSourceFC *bfmeReadFF(BfmeSourceFC *src, BfmeThingFC *thing)
{
	src->bfmeFirstFC(thing);
	src->bfmeNextFC(&thing->m_bfmeFirst);
	src->bfmeNextFC(&thing->m_bfmeSecond);
	src->bfmeNextFC(&thing->m_bfmeThird);
	src->bfmeLastFC(&thing->m_bfmeFourth);

	return src;
}

class BfmeItemFD;

struct BfmeOpsFD
{
	void (__stdcall *m_bfmeSpare)(BfmeItemFD *item);
	void (__stdcall *m_bfmeAlso)(BfmeItemFD *item);
	void (__stdcall *m_bfmeDrop)(BfmeItemFD *item);
};

struct BfmeItemFD
{
	BfmeOpsFD *m_bfmeOps;			// 0x0
};

class BfmeThingFD
{
public:
	int bfmeClearFD(void);

private:
	unsigned char m_bfmeHead[8];		// 0x00
	BfmeItemFD *m_bfmeFirst;		// 0x08
	BfmeItemFD *m_bfmeSecond;		// 0x0c
	BfmeItemFD *m_bfmeThird;		// 0x10
};

int BfmeThingFD::bfmeClearFD(void)
{
	BfmeItemFD *first = m_bfmeFirst;

	if (first != 0)
		first->m_bfmeOps->m_bfmeDrop(first);

	BfmeItemFD *second = m_bfmeSecond;

	if (second != 0)
		second->m_bfmeOps->m_bfmeDrop(second);

	BfmeItemFD *third = m_bfmeThird;

	if (third != 0)
		third->m_bfmeOps->m_bfmeDrop(third);

	m_bfmeFirst = 0;
	m_bfmeSecond = 0;
	m_bfmeThird = 0;

	return 1;
}
