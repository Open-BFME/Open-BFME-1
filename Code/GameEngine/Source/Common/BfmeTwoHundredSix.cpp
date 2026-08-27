// Four errands: a run of four steps taken when the first says yes, a list of
// parts each finished, two numbers built on the spot and handed over, and a
// charge taken over from another record.

class BfmeThingHG
{
public:
	virtual void bfmeSpare000HG(void) = 0;
	virtual void bfmeSpare001HG(void) = 0;
	virtual unsigned char bfmeAskHG(void *what) = 0;
	virtual void bfmeSpare003HG(void) = 0;
	virtual void bfmeSpare004HG(void) = 0;
	virtual void bfmeSpare005HG(void) = 0;
	virtual void bfmeSpare006HG(void) = 0;
	virtual void bfmeSpare007HG(void) = 0;
	virtual void bfmeFourthHG(int how) = 0;
	virtual void bfmeThirdHG(void) = 0;
	virtual void bfmeSpare010HG(void) = 0;
	virtual void bfmeFirstHG(void) = 0;
	virtual void bfmeSpare012HG(void) = 0;
	virtual void bfmeSecondHG(void) = 0;

	unsigned char bfmeGoHG(void *what);
};

unsigned char BfmeThingHG::bfmeGoHG(void *what)
{
	if (bfmeAskHG(what) != 0)
	{
		bfmeFirstHG();
		bfmeSecondHG();
		bfmeThirdHG();
		bfmeFourthHG(1);

		return 1;
	}

	return 0;
}

class BfmeItemHH
{
public:
	virtual void bfmeSpare000HH(void) = 0;
	virtual void bfmeDoHH(void) = 0;
};

struct BfmeSlotHH
{
	BfmeItemHH *m_bfmeItem;			// 0x00
	unsigned char m_bfmeBody[0x18];		// 0x04
};

class BfmeThingHH
{
public:
	void bfmeClearHH(void);

private:
	unsigned char m_bfmeHead[0x818];	// 0x000
	int m_bfmeCount;			// 0x818
	BfmeSlotHH *m_bfmeSlots;		// 0x81c
};

void BfmeThingHH::bfmeClearHH(void)
{
	for (int i = 0; i < m_bfmeCount; ++i)
		m_bfmeSlots[i].m_bfmeItem->bfmeDoHH();

	m_bfmeCount = 0;
}

struct BfmeTripleHI
{
	int m_bfmeFirst;			// 0x0
	int m_bfmeSecond;			// 0x4
	int m_bfmeThird;			// 0x8
};


class BfmeThingHI
{
public:
	virtual void bfmeSpare000HI(void) = 0;
	virtual void bfmeSpare001HI(void) = 0;
	virtual void bfmeSpare002HI(void) = 0;
	virtual void bfmeSpare003HI(void) = 0;
	virtual void bfmeSpare004HI(void) = 0;
	virtual void bfmeSpare005HI(void) = 0;
	virtual void bfmeSpare006HI(void) = 0;
	virtual void bfmeSpare007HI(void) = 0;
	virtual void bfmeSpare008HI(void) = 0;
	virtual void bfmeSpare009HI(void) = 0;
	virtual void bfmeSpare010HI(void) = 0;
	virtual void bfmeSpare011HI(void) = 0;
	virtual void bfmeSpare012HI(void) = 0;
	virtual void bfmeSpare013HI(void) = 0;
	virtual void bfmeSpare014HI(void) = 0;
	virtual void bfmeSpare015HI(void) = 0;
	virtual void bfmeSecondHI(int what) = 0;
	virtual void bfmeSpare017HI(void) = 0;
	virtual void bfmeSpare018HI(void) = 0;
	virtual void bfmeSpare019HI(void) = 0;
	virtual void bfmeSpare020HI(void) = 0;
	virtual void bfmeSpare021HI(void) = 0;
	virtual void bfmeSpare022HI(void) = 0;
	virtual void bfmeSpare023HI(void) = 0;
	virtual void bfmeSpare024HI(void) = 0;
	virtual void bfmeFirstHI(BfmeTripleHI *three) = 0;

	void bfmeGoHI(int first, int second, int what);
};

void BfmeThingHI::bfmeGoHI(int first, int second, int what)
{
	BfmeTripleHI three;

	three.m_bfmeFirst = first;
	three.m_bfmeSecond = second;
	three.m_bfmeThird = 0;

	bfmeFirstHI(&three);
	bfmeSecondHI(what);
}

class BfmeSubHJ
{
public:
	virtual void bfmeDoHJ(int how);

	int m_bfmeCount;			// 0x4
};

struct BfmeCountedHJ
{
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeSubHJ m_bfmeSub;			// 0x24
};

class BfmeThingHJ
{
public:
	BfmeThingHJ &bfmeTakeHJ(const BfmeThingHJ *from);

private:
	BfmeCountedHJ *m_bfmeItem;		// 0x0
};

BfmeThingHJ &BfmeThingHJ::bfmeTakeHJ(const BfmeThingHJ *from)
{
	if (this != from)
	{
		BfmeCountedHJ *item = from->m_bfmeItem;

		if (item != 0)
			++item->m_bfmeSub.m_bfmeCount;

		BfmeCountedHJ *mine = m_bfmeItem;

		if (mine != 0)
		{
			BfmeSubHJ *sub = &mine->m_bfmeSub;
			int left = --sub->m_bfmeCount;

			if (left <= 0)
				sub->bfmeDoHJ(1);
		}

		m_bfmeItem = from->m_bfmeItem;
	}

	return *this;
}

