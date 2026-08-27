// Six errands: one charge put down and the next taken up, a charge handed over
// with the record, a long list of numbers passed straight on, three numbers
// built on the spot, four readings taken in turn, and a run told four things.

class BfmeTargetEW
{
public:
	virtual void bfmeGoneEW(int how) = 0;
	virtual void bfmeSpare001EW(void) = 0;
	virtual void bfmeSpare002EW(void) = 0;
	virtual void bfmeSpare003EW(void) = 0;
	virtual void bfmeSpare004EW(void) = 0;
	virtual void bfmeSpare005EW(void) = 0;
	virtual void bfmeSpare006EW(void) = 0;
	virtual void bfmeSpare007EW(void) = 0;
	virtual void bfmeSpare008EW(void) = 0;
	virtual void bfmeSpare009EW(void) = 0;
	virtual void bfmeSpare010EW(void) = 0;
	virtual void bfmeSpare011EW(void) = 0;
	virtual void bfmeSpare012EW(void) = 0;
	virtual void bfmeSpare013EW(void) = 0;
	virtual void bfmeSpare014EW(void) = 0;
	virtual void bfmeStopEW(void) = 0;
};

class BfmeThingEW
{
public:
	void bfmeSwapEW(void);

private:
	unsigned char m_bfmeHead[0x30];		// 0x00
	BfmeTargetEW *m_bfmeCurrent;		// 0x30
	BfmeTargetEW *m_bfmeNext;		// 0x34
};

void BfmeThingEW::bfmeSwapEW(void)
{
	if (m_bfmeNext == 0)
		return;

	BfmeTargetEW *current = m_bfmeCurrent;

	if (current != 0)
	{
		current->bfmeStopEW();

		if (m_bfmeCurrent != 0)
			m_bfmeCurrent->bfmeGoneEW(1);

		m_bfmeCurrent = 0;
	}

	m_bfmeCurrent = m_bfmeNext;
	m_bfmeNext = 0;
}

class BfmeItemEX;

struct BfmeOpsEX
{
	void (__stdcall *m_bfmeSpare)(BfmeItemEX *item);
	void (__stdcall *m_bfmeAdd)(BfmeItemEX *item);
	void (__stdcall *m_bfmeDrop)(BfmeItemEX *item);
};

struct BfmeItemEX
{
	BfmeOpsEX *m_bfmeOps;			// 0x0
};

class BfmeThingEX
{
public:
	BfmeThingEX &bfmeTakeEX(const BfmeThingEX *from);

private:
	int m_bfmeFirst;			// 0x0
	BfmeItemEX *m_bfmeItem;			// 0x4
};

BfmeThingEX &BfmeThingEX::bfmeTakeEX(const BfmeThingEX *from)
{
	m_bfmeFirst = from->m_bfmeFirst;

	BfmeItemEX *item = from->m_bfmeItem;

	if (item != 0)
		item->m_bfmeOps->m_bfmeAdd(item);

	BfmeItemEX *mine = m_bfmeItem;

	if (mine != 0)
		mine->m_bfmeOps->m_bfmeDrop(mine);

	m_bfmeItem = from->m_bfmeItem;

	return *this;
}


class BfmeThingEY
{
public:
	virtual void bfmeSpare000EY(void) = 0;
	virtual void bfmeSpare001EY(void) = 0;
	virtual void bfmeSpare002EY(void) = 0;
	virtual void bfmeSpare003EY(void) = 0;
	virtual void bfmeSpare004EY(void) = 0;
	virtual void bfmeSpare005EY(void) = 0;
	virtual void bfmeSpare006EY(void) = 0;
	virtual void bfmeSpare007EY(void) = 0;
	virtual void bfmeSpare008EY(void) = 0;
	virtual void bfmeSpare009EY(void) = 0;
	virtual void bfmeDoEY(void *first, int a, int b, int c, int d, int e, int f, int g) = 0;

	void *bfmeGoEY(void *first, int a, int b, int c, int d, int e, int f, int g);
};

void *BfmeThingEY::bfmeGoEY(void *first, int a, int b, int c, int d, int e, int f, int g)
{
	bfmeDoEY(first, a, b, c, d, e, f, g);

	return first;
}

struct BfmeTripleEZ
{
	int m_bfmeFirst;			// 0x0
	int m_bfmeSecond;			// 0x4
	int m_bfmeThird;			// 0x8
};


class BfmeTargetEZ
{
public:
	virtual void bfmeSpare000EZ(void) = 0;
	virtual void bfmeSpare001EZ(void) = 0;
	virtual void bfmeSpare002EZ(void) = 0;
	virtual void bfmeSpare003EZ(void) = 0;
	virtual void bfmeSpare004EZ(void) = 0;
	virtual void bfmeSpare005EZ(void) = 0;
	virtual void bfmeDoEZ(BfmeTripleEZ *three) = 0;
};

class BfmeThingEZ
{
public:
	void bfmeGoEZ(int stop, int first, int second, int third);

private:
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeTargetEZ *m_bfmeTarget;		// 0xc
};

void BfmeThingEZ::bfmeGoEZ(int stop, int first, int second, int third)
{
	if (stop != 0)
		return;

	BfmeTripleEZ three;

	three.m_bfmeFirst = first;
	three.m_bfmeSecond = second;
	three.m_bfmeThird = third;

	m_bfmeTarget->bfmeDoEZ(&three);
}


class BfmeThingFA;

class BfmeSourceFA
{
public:
	virtual void bfmeSpare000FA(void) = 0;
	virtual void bfmeSpare001FA(void) = 0;
	virtual void bfmeSpare002FA(void) = 0;
	virtual void bfmeSpare003FA(void) = 0;
	virtual void bfmeSpare004FA(void) = 0;
	virtual void bfmeSpare005FA(void) = 0;
	virtual void bfmeSpare006FA(void) = 0;
	virtual void bfmeSpare007FA(void) = 0;
	virtual void bfmeSpare008FA(void) = 0;
	virtual void bfmeSpare009FA(void) = 0;
	virtual void bfmeSpare010FA(void) = 0;
	virtual void bfmeSpare011FA(void) = 0;
	virtual void bfmeSpare012FA(void) = 0;
	virtual void bfmeSpare013FA(void) = 0;
	virtual void bfmeSpare014FA(void) = 0;
	virtual void bfmeSpare015FA(void) = 0;
	virtual void bfmeSpare016FA(void) = 0;
	virtual void bfmeSpare017FA(void) = 0;
	virtual void bfmeSpare018FA(void) = 0;
	virtual void bfmeSpare019FA(void) = 0;
	virtual void bfmeFirstFA(BfmeThingFA *thing) = 0;
	virtual void bfmeSpare021FA(void) = 0;
	virtual void bfmeSpare022FA(void) = 0;
	virtual void bfmeSpare023FA(void) = 0;
	virtual void bfmeSpare024FA(void) = 0;
	virtual void bfmeSpare025FA(void) = 0;
	virtual void bfmeSecondFA(int *out) = 0;
	virtual void bfmeThirdFA(int *out) = 0;
};

class BfmeThingFA
{
public:
	void bfmeReadFA(BfmeSourceFA *src);

private:
	unsigned char m_bfmeHead[8];		// 0x00
	int m_bfmeFirst;			// 0x08
	int m_bfmeSecond;			// 0x0c
	int m_bfmeThird;			// 0x10
};

void BfmeThingFA::bfmeReadFA(BfmeSourceFA *src)
{
	src->bfmeFirstFA(this);
	src->bfmeSecondFA(&m_bfmeFirst);
	src->bfmeSecondFA(&m_bfmeSecond);
	src->bfmeThirdFA(&m_bfmeThird);
}


class BfmeItemFB
{
public:
	virtual void bfmeSpare000FB(void) = 0;
	virtual void bfmeSpare001FB(void) = 0;
	virtual void bfmeSpare002FB(void) = 0;
	virtual void bfmeDoFB(void *a, void *b, void *c, void *d) = 0;
};

class BfmeThingFB
{
public:
	void bfmeTellFB(void *a, void *b, void *c, void *d);

private:
	BfmeItemFB **m_bfmeBegin;		// 0x0
	BfmeItemFB **m_bfmeEnd;			// 0x4
};

void BfmeThingFB::bfmeTellFB(void *a, void *b, void *c, void *d)
{
	BfmeItemFB **at = m_bfmeBegin;

	while (at != m_bfmeEnd)
	{
		(*at)->bfmeDoFB(a, b, c, d);

		++at;
	}
}

