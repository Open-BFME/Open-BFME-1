// Five errands that go round a ring or along a run telling everything on it
// what to do, and one that asks a maker for something and then sets it going.

class BfmeItemDN
{
public:
	virtual void bfmeDoDN(void *what) = 0;
};

struct BfmeNodeDN
{
	BfmeNodeDN *m_bfmeNext;			// 0x0
	unsigned char m_bfmeGap[4];		// 0x4
	BfmeItemDN *m_bfmeItem;			// 0x8
};

class BfmeThingDN
{
public:
	void bfmeTellDN(void *what);

private:
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeNodeDN *m_bfmeRing;			// 0xc
};

void BfmeThingDN::bfmeTellDN(void *what)
{
	BfmeNodeDN *at = m_bfmeRing->m_bfmeNext;

	while (at != m_bfmeRing)
	{
		at->m_bfmeItem->bfmeDoDN(what);

		at = at->m_bfmeNext;
	}
}


class BfmeItemDS
{
public:
	virtual void bfmeSpare000DS(void) = 0;
	virtual void bfmeSpare001DS(void) = 0;
	virtual void bfmeSpare002DS(void) = 0;
	virtual void bfmeSpare003DS(void) = 0;
	virtual void bfmeSpare004DS(void) = 0;
	virtual void bfmeSpare005DS(void) = 0;
	virtual void bfmeSpare006DS(void) = 0;
	virtual void bfmeSpare007DS(void) = 0;
	virtual void bfmeSpare008DS(void) = 0;
	virtual void bfmeSpare009DS(void) = 0;
	virtual void bfmeSpare010DS(void) = 0;
	virtual void bfmeSpare011DS(void) = 0;
	virtual void bfmeSpare012DS(void) = 0;
	virtual void bfmeSpare013DS(void) = 0;
	virtual void bfmeSpare014DS(void) = 0;
	virtual void bfmeSpare015DS(void) = 0;
	virtual void bfmeSpare016DS(void) = 0;
	virtual void bfmeSpare017DS(void) = 0;
	virtual void bfmeSpare018DS(void) = 0;
	virtual void bfmeSpare019DS(void) = 0;
	virtual void bfmeSpare020DS(void) = 0;
	virtual void bfmeSpare021DS(void) = 0;
	virtual void bfmeSpare022DS(void) = 0;
	virtual void bfmeDoDS(void *what) = 0;
};

struct BfmeNodeDS
{
	BfmeNodeDS *m_bfmeNext;			// 0x0
	unsigned char m_bfmeGap[4];		// 0x4
	BfmeItemDS *m_bfmeItem;			// 0x8
};

class BfmeThingDS
{
public:
	void bfmeTellDS(void *what);

private:
	unsigned char m_bfmeHead[0x18];		// 0x00
	BfmeNodeDS *m_bfmeRing;			// 0x18
};

void BfmeThingDS::bfmeTellDS(void *what)
{
	BfmeNodeDS *at = m_bfmeRing->m_bfmeNext;

	while (at != m_bfmeRing)
	{
		at->m_bfmeItem->bfmeDoDS(what);

		at = at->m_bfmeNext;
	}
}


class BfmeTargetDO
{
public:
	virtual void bfmeSpare000DO(void) = 0;
	virtual void bfmeSpare001DO(void) = 0;
	virtual void bfmeSpare002DO(void) = 0;
	virtual void bfmeSpare003DO(void) = 0;
	virtual int bfmeDoDO(int from, int to) = 0;
};

class BfmeThingDO
{
public:
	unsigned char bfmeAskDO(BfmeTargetDO *target);

private:
	unsigned char m_bfmeHead[0x14];		// 0x00
	int m_bfmeAt;				// 0x14
	unsigned char m_bfmeGap[4];		// 0x18
	int m_bfmeEnd;				// 0x1c
};

unsigned char BfmeThingDO::bfmeAskDO(BfmeTargetDO *target)
{
	if (target == 0)
		return 0;

	return target->bfmeDoDO(m_bfmeAt, m_bfmeEnd) == m_bfmeEnd;
}


class BfmeMadeDP
{
public:
	virtual void bfmeDoDP(void) = 0;
};

class BfmeMakerDP
{
public:
	virtual void bfmeSpare000DP(void) = 0;
	virtual void bfmeSpare001DP(void) = 0;
	virtual void bfmeSpare002DP(void) = 0;
	virtual void bfmeSpare003DP(void) = 0;
	virtual void bfmeSpare004DP(void) = 0;
	virtual void bfmeSpare005DP(void) = 0;
	virtual void bfmeSpare006DP(void) = 0;
	virtual void bfmeSpare007DP(void) = 0;
	virtual void bfmeSpare008DP(void) = 0;
	virtual void bfmeSpare009DP(void) = 0;
	virtual void bfmeSpare010DP(void) = 0;
	virtual void bfmeSpare011DP(void) = 0;
	virtual void bfmeSpare012DP(void) = 0;
	virtual void bfmeSpare013DP(void) = 0;
	virtual void bfmeSpare014DP(void) = 0;
	virtual void bfmeSpare015DP(void) = 0;
	virtual void bfmeSpare016DP(void) = 0;
	virtual void bfmeSpare017DP(void) = 0;
	virtual void bfmeSpare018DP(void) = 0;
	virtual void bfmeSpare019DP(void) = 0;
	virtual void bfmeSpare020DP(void) = 0;
	virtual void bfmeSpare021DP(void) = 0;
	virtual void bfmeSpare022DP(void) = 0;
	virtual void bfmeSpare023DP(void) = 0;
	virtual void bfmeSpare024DP(void) = 0;
	virtual void bfmeSpare025DP(void) = 0;
	virtual void bfmeSpare026DP(void) = 0;
	virtual void bfmeSpare027DP(void) = 0;
	virtual void bfmeSpare028DP(void) = 0;
	virtual void bfmeSpare029DP(void) = 0;
	virtual void bfmeSpare030DP(void) = 0;
	virtual void bfmeSpare031DP(void) = 0;
	virtual void bfmeSpare032DP(void) = 0;
	virtual void bfmeSpare033DP(void) = 0;
	virtual void bfmeSpare034DP(void) = 0;
	virtual void bfmeSpare035DP(void) = 0;
	virtual void bfmeSpare036DP(void) = 0;
	virtual void bfmeSpare037DP(void) = 0;
	virtual void bfmeSpare038DP(void) = 0;
	virtual void bfmeSpare039DP(void) = 0;
	virtual void bfmeSpare040DP(void) = 0;
	virtual void bfmeSpare041DP(void) = 0;
	virtual void bfmeSpare042DP(void) = 0;
	virtual void bfmeSpare043DP(void) = 0;
	virtual void bfmeSpare044DP(void) = 0;
	virtual void bfmeSpare045DP(void) = 0;
	virtual void bfmeSpare046DP(void) = 0;
	virtual void bfmeSpare047DP(void) = 0;
	virtual void bfmeSpare048DP(void) = 0;
	virtual void bfmeSpare049DP(void) = 0;
	virtual void bfmeSpare050DP(void) = 0;
	virtual void bfmeSpare051DP(void) = 0;
	virtual void bfmeSpare052DP(void) = 0;
	virtual void bfmeSpare053DP(void) = 0;
	virtual void bfmeSpare054DP(void) = 0;
	virtual void bfmeSpare055DP(void) = 0;
	virtual void bfmeSpare056DP(void) = 0;
	virtual void bfmeSpare057DP(void) = 0;
	virtual void bfmeSpare058DP(void) = 0;
	virtual void bfmeSpare059DP(void) = 0;
	virtual void bfmeSpare060DP(void) = 0;
	virtual void bfmeSpare061DP(void) = 0;
	virtual void bfmeSpare062DP(void) = 0;
	virtual void bfmeSpare063DP(void) = 0;
	virtual void bfmeSpare064DP(void) = 0;
	virtual void bfmeSpare065DP(void) = 0;
	virtual void bfmeSpare066DP(void) = 0;
	virtual void bfmeSpare067DP(void) = 0;
	virtual void bfmeSpare068DP(void) = 0;
	virtual void bfmeSpare069DP(void) = 0;
	virtual void bfmeSpare070DP(void) = 0;
	virtual void bfmeSpare071DP(void) = 0;
	virtual void bfmeSpare072DP(void) = 0;
	virtual void bfmeSpare073DP(void) = 0;
	virtual void bfmeSpare074DP(void) = 0;
	virtual void bfmeSpare075DP(void) = 0;
	virtual void bfmeSpare076DP(void) = 0;
	virtual void bfmeSpare077DP(void) = 0;
	virtual void bfmeSpare078DP(void) = 0;
	virtual void bfmeSpare079DP(void) = 0;
	virtual void bfmeSpare080DP(void) = 0;
	virtual void bfmeSpare081DP(void) = 0;
	virtual void bfmeSpare082DP(void) = 0;
	virtual void bfmeSpare083DP(void) = 0;
	virtual void bfmeSpare084DP(void) = 0;
	virtual void bfmeSpare085DP(void) = 0;
	virtual BfmeMadeDP *bfmeMakeDP(void) = 0;
};

struct BfmeOtherDP
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeMakerDP *m_bfmeMaker;		// 0x204
};

struct BfmeOwnerDP
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeOtherDP *m_bfmeOther;		// 0x10
};

class BfmeThingDP
{
public:
	int bfmeGoDP(void);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeOwnerDP *m_bfmeOwner;		// 0x1c
};

int BfmeThingDP::bfmeGoDP(void)
{
	BfmeOtherDP *other = m_bfmeOwner->m_bfmeOther;

	if (other != 0)
	{
		BfmeMakerDP *maker = other->m_bfmeMaker;

		if (maker != 0)
		{
			BfmeMadeDP *made = maker->bfmeMakeDP();

			if (made != 0)
				made->bfmeDoDP();
		}
	}

	return 0;
}


class BfmeItemDQ
{
public:
	virtual void bfmeSpare000DQ(void) = 0;
	virtual void bfmeSpare001DQ(void) = 0;
	virtual void bfmeSpare002DQ(void) = 0;
	virtual void bfmeSpare003DQ(void) = 0;
	virtual void bfmeSpare004DQ(void) = 0;
	virtual void bfmeSpare005DQ(void) = 0;
	virtual void bfmeSpare006DQ(void) = 0;
	virtual void bfmeSpare007DQ(void) = 0;
	virtual void bfmeSpare008DQ(void) = 0;
	virtual void bfmeSpare009DQ(void) = 0;
	virtual void bfmeSpare010DQ(void) = 0;
	virtual void bfmeSpare011DQ(void) = 0;
	virtual void bfmeDoDQ(void) = 0;
};

class BfmeThingDQ
{
public:
	void bfmeTellDQ(void);

private:
	unsigned char m_bfmeHead[0x29c];	// 0x000
	BfmeItemDQ **m_bfmeBegin;		// 0x29c
	BfmeItemDQ **m_bfmeEnd;			// 0x2a0
};

void BfmeThingDQ::bfmeTellDQ(void)
{
	BfmeItemDQ **at = m_bfmeBegin;

	while (at != m_bfmeEnd)
	{
		(*at)->bfmeDoDQ();

		++at;
	}
}

