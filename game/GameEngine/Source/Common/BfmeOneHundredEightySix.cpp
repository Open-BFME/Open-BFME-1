// A record made around an item it then wakes, four numbers passed to a kept
// address, an item let go of, and the same question asked twice over.

class BfmeItemDC;

struct BfmeOpsDC
{
	void (__stdcall *m_bfmeSpare)(BfmeItemDC *item);
	void (__stdcall *m_bfmeDo)(BfmeItemDC *item);
};

struct BfmeItemDC
{
	BfmeOpsDC *m_bfmeOps;			// 0x0
};

class BfmeThingDC
{
public:
	BfmeThingDC(BfmeItemDC *item);

private:
	BfmeItemDC *m_bfmeItem;			// 0x0
};

BfmeThingDC::BfmeThingDC(BfmeItemDC *item)
{
	m_bfmeItem = item;

	if (item != 0)
		item->m_bfmeOps->m_bfmeDo(item);
}

class BfmeThingDD
{
public:
	void bfmeGoDD(int first, int second, int third, int fourth);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	void (__cdecl *m_bfmeCall)(int, int, int, int);	// 0x8
};

void BfmeThingDD::bfmeGoDD(int first, int second, int third, int fourth)
{
	m_bfmeCall(first, second, third, fourth);
}

class BfmeItemDF;

struct BfmeOpsDF
{
	void (__stdcall *m_bfmeFirst)(BfmeItemDF *item);
	void (__stdcall *m_bfmeSecond)(BfmeItemDF *item);
	void (__stdcall *m_bfmeDo)(BfmeItemDF *item);
};

struct BfmeItemDF
{
	BfmeOpsDF *m_bfmeOps;			// 0x0
};

class BfmeThingDF
{
public:
	int bfmeDropDF(void);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeItemDF *m_bfmeItem;			// 0x4
};

int BfmeThingDF::bfmeDropDF(void)
{
	BfmeItemDF *item = m_bfmeItem;

	if (item != 0)
		item->m_bfmeOps->m_bfmeDo(item);

	m_bfmeItem = 0;

	return 1;
}


class BfmeTargetDG
{
public:
	virtual void bfmeSpare000DG(void) = 0;
	virtual void bfmeSpare001DG(void) = 0;
	virtual void bfmeSpare002DG(void) = 0;
	virtual void bfmeSpare003DG(void) = 0;
	virtual void bfmeSpare004DG(void) = 0;
	virtual void bfmeSpare005DG(void) = 0;
	virtual void bfmeSpare006DG(void) = 0;
	virtual void bfmeSpare007DG(void) = 0;
	virtual void bfmeSpare008DG(void) = 0;
	virtual void bfmeSpare009DG(void) = 0;
	virtual void bfmeSpare010DG(void) = 0;
	virtual void bfmeSpare011DG(void) = 0;
	virtual void bfmeSpare012DG(void) = 0;
	virtual void bfmeSpare013DG(void) = 0;
	virtual void bfmeSpare014DG(void) = 0;
	virtual void bfmeSpare015DG(void) = 0;
	virtual void bfmeSpare016DG(void) = 0;
	virtual void bfmeSpare017DG(void) = 0;
	virtual void bfmeSpare018DG(void) = 0;
	virtual void bfmeSpare019DG(void) = 0;
	virtual void bfmeSpare020DG(void) = 0;
	virtual void bfmeSpare021DG(void) = 0;
	virtual void bfmeSpare022DG(void) = 0;
	virtual void bfmeSpare023DG(void) = 0;
	virtual void bfmeSpare024DG(void) = 0;
	virtual void bfmeSpare025DG(void) = 0;
	virtual int bfmeDoDG(void) = 0;
};

struct BfmeThingDG
{
	unsigned char m_bfmeHead[0x1fc];	// 0x000
	BfmeTargetDG *m_bfmeTarget;		// 0x1fc
};

int __stdcall bfmeAskDG(BfmeThingDG *thing)
{
	if (thing == 0)
		return 0;

	BfmeTargetDG *target = thing->m_bfmeTarget;

	if (target == 0)
		return 0;

	return target->bfmeDoDG();
}

int __stdcall bfmeAlsoDG(BfmeThingDG *thing)
{
	if (thing == 0)
		return 0;

	BfmeTargetDG *target = thing->m_bfmeTarget;

	if (target == 0)
		return 0;

	return target->bfmeDoDG();
}

