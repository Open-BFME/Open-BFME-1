// Four errands: five readings taken in turn, a target stopped and started
// again on a new thing, a list of parts each asked to make something and then
// set going, and three charges let go of together a second time.

class BfmeThingFG;

class BfmeSourceFG
{
public:
	virtual void bfmeSpare000FG(void) = 0;
	virtual void bfmeSpare001FG(void) = 0;
	virtual void bfmeSpare002FG(void) = 0;
	virtual void bfmeSpare003FG(void) = 0;
	virtual void bfmeSpare004FG(void) = 0;
	virtual void bfmeSpare005FG(void) = 0;
	virtual void bfmeSpare006FG(void) = 0;
	virtual void bfmeSpare007FG(void) = 0;
	virtual void bfmeSpare008FG(void) = 0;
	virtual void bfmeSpare009FG(void) = 0;
	virtual void bfmeSpare010FG(void) = 0;
	virtual void bfmeSpare011FG(void) = 0;
	virtual void bfmeSpare012FG(void) = 0;
	virtual void bfmeSpare013FG(void) = 0;
	virtual void bfmeSpare014FG(void) = 0;
	virtual void bfmeSpare015FG(void) = 0;
	virtual void bfmeSpare016FG(void) = 0;
	virtual void bfmeSpare017FG(void) = 0;
	virtual void bfmeSpare018FG(void) = 0;
	virtual void bfmeSpare019FG(void) = 0;
	virtual void bfmeSpare020FG(void) = 0;
	virtual void bfmeSpare021FG(void) = 0;
	virtual void bfmeSpare022FG(void) = 0;
	virtual void bfmeSpare023FG(void) = 0;
	virtual void bfmeSpare024FG(void) = 0;
	virtual void bfmeSpare025FG(void) = 0;
	virtual void bfmeFirstFG(BfmeThingFG *thing) = 0;
	virtual void bfmeNextFG(int *out) = 0;
};

class BfmeThingFG
{
public:
	void bfmeReadFG(BfmeSourceFG *src);

private:
	unsigned char m_bfmeHead[4];		// 0x00
	int m_bfmeFirst;			// 0x04
	int m_bfmeSecond;			// 0x08
	int m_bfmeThird;			// 0x0c
	int m_bfmeFourth;			// 0x10
};

void BfmeThingFG::bfmeReadFG(BfmeSourceFG *src)
{
	src->bfmeFirstFG(this);
	src->bfmeNextFG(&m_bfmeFirst);
	src->bfmeNextFG(&m_bfmeSecond);
	src->bfmeNextFG(&m_bfmeThird);
	src->bfmeNextFG(&m_bfmeFourth);
}


class BfmeOwnerFH
{
public:
	virtual void bfmeSpare000FH(void) = 0;
	virtual void bfmeSpare001FH(void) = 0;
	virtual void bfmeSpare002FH(void) = 0;
	virtual void bfmeSpare003FH(void) = 0;
	virtual void bfmeSpare004FH(void) = 0;
	virtual void bfmeStopFH(void) = 0;
	virtual void bfmeSpare006FH(void) = 0;
	virtual void bfmeSpare007FH(void) = 0;
	virtual void bfmeStartFH(int kind) = 0;
	virtual void bfmeSpare009FH(void) = 0;
	virtual void bfmeSpare010FH(void) = 0;
	virtual void bfmeSpare011FH(void) = 0;
	virtual void bfmeSpare012FH(void) = 0;
	virtual void bfmeSpare013FH(void) = 0;
	virtual void bfmeSetFH(int which) = 0;
};

struct BfmeOtherFH
{
	unsigned char m_bfmeHead[0x214];	// 0x000
	int m_bfmeThing;			// 0x214
};

class BfmeThingFH
{
public:
	void bfmeGoFH(int what, int how);

private:
	unsigned char m_bfmeHead[8];		// 0x00
	BfmeOtherFH *m_bfmeOther;		// 0x08
	unsigned char m_bfmeGap[0x24];		// 0x0c
	BfmeOwnerFH *m_bfmeOwner;		// 0x30
	unsigned char m_bfmeSpare[0x14];	// 0x34
	int m_bfmeHow;				// 0x48
};

void BfmeThingFH::bfmeGoFH(int what, int how)
{
	int which = what;

	if (which == 0)
	{
		which = m_bfmeOther->m_bfmeThing;

		if (which == 0)
			return;
	}

	m_bfmeOwner->bfmeStopFH();
	m_bfmeOwner->bfmeSetFH(which);

	m_bfmeHow = how;

	m_bfmeOwner->bfmeStartFH(0x35);
}


class BfmeMadeFI
{
public:
	virtual void bfmeSpare000FI(void) = 0;
	virtual void bfmeSpare001FI(void) = 0;
	virtual void bfmeSpare002FI(void) = 0;
	virtual void bfmeSpare003FI(void) = 0;
	virtual void bfmeSpare004FI(void) = 0;
	virtual void bfmeSpare005FI(void) = 0;
	virtual void bfmeSpare006FI(void) = 0;
	virtual void bfmeSpare007FI(void) = 0;
	virtual void bfmeDoFI(void) = 0;
};

class BfmeSubFI
{
public:
	virtual void bfmeSpare000FJ(void);
	virtual void bfmeSpare001FJ(void);
	virtual void bfmeSpare002FJ(void);
	virtual void bfmeSpare003FJ(void);
	virtual void bfmeSpare004FJ(void);
	virtual void bfmeSpare005FJ(void);
	virtual void bfmeSpare006FJ(void);
	virtual BfmeMadeFI *bfmeMakeFI(void);
};

struct BfmeItemFI
{
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeSubFI m_bfmeSub;			// 0xc
};

struct BfmeHostFI
{
	unsigned char m_bfmeHead[0x1f0];	// 0x000
	BfmeItemFI **m_bfmeList;		// 0x1f0
};


class BfmePartFI
{
public:
	virtual void bfmeSpare000FK(void);
	virtual void bfmeSpare001FK(void);
	virtual unsigned char bfmeAskFI(void);

	void bfmeGoFI(void);

	unsigned char m_bfmeFlag;		// 0x4
};

struct BfmeOwnerFI
{
	BfmeHostFI *m_bfmeHost;			// 0x0
	unsigned char m_bfmeGap[4];		// 0x4
	BfmePartFI m_bfmePart;			// 0x8
};

void BfmePartFI::bfmeGoFI(void)
{
	if (bfmeAskFI() == 0)
		return;

	m_bfmeFlag = 0;

	BfmeItemFI **at = ((const BfmeOwnerFI *)((const char *)this - 8))->m_bfmeHost->m_bfmeList;

	while (*at != 0)
	{
		BfmeMadeFI *made = (*at)->m_bfmeSub.bfmeMakeFI();

		if (made != 0)
			made->bfmeDoFI();

		++at;
	}
}

class BfmeItemFL;

struct BfmeOpsFL
{
	void (__stdcall *m_bfmeSpare)(BfmeItemFL *item);
	void (__stdcall *m_bfmeAlso)(BfmeItemFL *item);
	void (__stdcall *m_bfmeDrop)(BfmeItemFL *item);
};

struct BfmeItemFL
{
	BfmeOpsFL *m_bfmeOps;			// 0x0
};

class BfmeThingFL
{
public:
	int bfmeClearFL(void);

private:
	unsigned char m_bfmeHead[8];		// 0x00
	BfmeItemFL *m_bfmeFirst;		// 0x08
	BfmeItemFL *m_bfmeSecond;		// 0x0c
	BfmeItemFL *m_bfmeThird;		// 0x10
};

int BfmeThingFL::bfmeClearFL(void)
{
	BfmeItemFL *first = m_bfmeFirst;

	if (first != 0)
		first->m_bfmeOps->m_bfmeDrop(first);

	BfmeItemFL *second = m_bfmeSecond;

	if (second != 0)
		second->m_bfmeOps->m_bfmeDrop(second);

	BfmeItemFL *third = m_bfmeThird;

	if (third != 0)
		third->m_bfmeOps->m_bfmeDrop(third);

	m_bfmeFirst = 0;
	m_bfmeSecond = 0;
	m_bfmeThird = 0;

	return 1;
}

