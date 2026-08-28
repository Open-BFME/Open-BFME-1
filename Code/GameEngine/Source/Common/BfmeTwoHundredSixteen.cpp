// Two small bodies the retail image emits twice each, both copies converted
// here under their own names: a helper stopped and let go of, and a maker asked
// for a piece that is then told to go.

class BfmeItemJG
{
public:
	virtual void bfmeGoneJG(int how) = 0;
	virtual void bfmeSpare001JG(void) = 0;
	virtual void bfmeSpare002JG(void) = 0;
	virtual void bfmeSpare003JG(void) = 0;
	virtual void bfmeSpare004JG(void) = 0;
	virtual void bfmeStopJG(void *what) = 0;
};

class BfmeThingJG
{
public:
	void bfmeDropJG(void *what);

private:
	unsigned char m_bfmeHead[0x40];		// 0x00
	BfmeItemJG *m_bfmeItem;			// 0x40
};

void BfmeThingJG::bfmeDropJG(void *what)
{
	BfmeItemJG *item = m_bfmeItem;

	if (item != 0)
	{
		item->bfmeStopJG(what);

		if (m_bfmeItem != 0)
			m_bfmeItem->bfmeGoneJG(1);

		m_bfmeItem = 0;
	}
}

class BfmeItemJK
{
public:
	virtual void bfmeGoneJK(int how) = 0;
	virtual void bfmeSpare001JK(void) = 0;
	virtual void bfmeSpare002JK(void) = 0;
	virtual void bfmeSpare003JK(void) = 0;
	virtual void bfmeSpare004JK(void) = 0;
	virtual void bfmeStopJK(void *what) = 0;
};

class BfmeThingJK
{
public:
	void bfmeDropJK(void *what);

private:
	unsigned char m_bfmeHead[0x40];		// 0x00
	BfmeItemJK *m_bfmeItem;			// 0x40
};

void BfmeThingJK::bfmeDropJK(void *what)
{
	BfmeItemJK *item = m_bfmeItem;

	if (item != 0)
	{
		item->bfmeStopJK(what);

		if (m_bfmeItem != 0)
			m_bfmeItem->bfmeGoneJK(1);

		m_bfmeItem = 0;
	}
}

class BfmeItemJH
{
public:
	virtual void bfmeSpare000JH(void) = 0;
	virtual void bfmeSpare001JH(void) = 0;
	virtual void bfmeSpare002JH(void) = 0;
	virtual void bfmeSpare003JH(void) = 0;
	virtual void bfmeSpare004JH(void) = 0;
	virtual void bfmeSpare005JH(void) = 0;
	virtual void bfmeSpare006JH(void) = 0;
	virtual void bfmeSpare007JH(void) = 0;
	virtual void bfmeSpare008JH(void) = 0;
	virtual void bfmeSpare009JH(void) = 0;
	virtual void bfmeSpare010JH(void) = 0;
	virtual void bfmeDoJH(int how) = 0;
};

class BfmeMakerJH
{
public:
	virtual void bfmeSpare000JH(void) = 0;
	virtual void bfmeSpare001JH(void) = 0;
	virtual void bfmeSpare002JH(void) = 0;
	virtual void bfmeSpare003JH(void) = 0;
	virtual void bfmeSpare004JH(void) = 0;
	virtual void bfmeSpare005JH(void) = 0;
	virtual void bfmeSpare006JH(void) = 0;
	virtual void bfmeSpare007JH(void) = 0;
	virtual void bfmeSpare008JH(void) = 0;
	virtual void bfmeSpare009JH(void) = 0;
	virtual void bfmeSpare010JH(void) = 0;
	virtual void bfmeSpare011JH(void) = 0;
	virtual void bfmeSpare012JH(void) = 0;
	virtual void bfmeSpare013JH(void) = 0;
	virtual void bfmeSpare014JH(void) = 0;
	virtual void bfmeSpare015JH(void) = 0;
	virtual void bfmeSpare016JH(void) = 0;
	virtual void bfmeSpare017JH(void) = 0;
	virtual void bfmeSpare018JH(void) = 0;
	virtual void bfmeSpare019JH(void) = 0;
	virtual void bfmeSpare020JH(void) = 0;
	virtual void bfmeSpare021JH(void) = 0;
	virtual void bfmeSpare022JH(void) = 0;
	virtual void bfmeSpare023JH(void) = 0;
	virtual void bfmeSpare024JH(void) = 0;
	virtual void bfmeSpare025JH(void) = 0;
	virtual void bfmeSpare026JH(void) = 0;
	virtual void bfmeSpare027JH(void) = 0;
	virtual void bfmeSpare028JH(void) = 0;
	virtual void bfmeSpare029JH(void) = 0;
	virtual void bfmeSpare030JH(void) = 0;
	virtual void bfmeSpare031JH(void) = 0;
	virtual void bfmeSpare032JH(void) = 0;
	virtual void bfmeSpare033JH(void) = 0;
	virtual void bfmeSpare034JH(void) = 0;
	virtual void bfmeSpare035JH(void) = 0;
	virtual void bfmeSpare036JH(void) = 0;
	virtual void bfmeSpare037JH(void) = 0;
	virtual void bfmeSpare038JH(void) = 0;
	virtual void bfmeSpare039JH(void) = 0;
	virtual void bfmeSpare040JH(void) = 0;
	virtual void bfmeSpare041JH(void) = 0;
	virtual void bfmeSpare042JH(void) = 0;
	virtual void bfmeSpare043JH(void) = 0;
	virtual void bfmeSpare044JH(void) = 0;
	virtual void bfmeSpare045JH(void) = 0;
	virtual void bfmeSpare046JH(void) = 0;
	virtual void bfmeSpare047JH(void) = 0;
	virtual void bfmeSpare048JH(void) = 0;
	virtual void bfmeSpare049JH(void) = 0;
	virtual void bfmeSpare050JH(void) = 0;
	virtual void bfmeSpare051JH(void) = 0;
	virtual void bfmeSpare052JH(void) = 0;
	virtual void bfmeSpare053JH(void) = 0;
	virtual void bfmeSpare054JH(void) = 0;
	virtual void bfmeSpare055JH(void) = 0;
	virtual void bfmeSpare056JH(void) = 0;
	virtual void bfmeSpare057JH(void) = 0;
	virtual void bfmeSpare058JH(void) = 0;
	virtual void bfmeSpare059JH(void) = 0;
	virtual void bfmeSpare060JH(void) = 0;
	virtual void bfmeSpare061JH(void) = 0;
	virtual void bfmeSpare062JH(void) = 0;
	virtual void bfmeSpare063JH(void) = 0;
	virtual void bfmeSpare064JH(void) = 0;
	virtual void bfmeSpare065JH(void) = 0;
	virtual void bfmeSpare066JH(void) = 0;
	virtual void bfmeSpare067JH(void) = 0;
	virtual void bfmeSpare068JH(void) = 0;
	virtual void bfmeSpare069JH(void) = 0;
	virtual void bfmeSpare070JH(void) = 0;
	virtual void bfmeSpare071JH(void) = 0;
	virtual void bfmeSpare072JH(void) = 0;
	virtual void bfmeSpare073JH(void) = 0;
	virtual void bfmeSpare074JH(void) = 0;
	virtual void bfmeSpare075JH(void) = 0;
	virtual void bfmeSpare076JH(void) = 0;
	virtual void bfmeSpare077JH(void) = 0;
	virtual void bfmeSpare078JH(void) = 0;
	virtual void bfmeSpare079JH(void) = 0;
	virtual void bfmeSpare080JH(void) = 0;
	virtual BfmeItemJH *bfmeFindJH(void) = 0;
};

struct BfmeOtherJH
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeMakerJH *m_bfmeMaker;		// 0x204
};

struct BfmeOwnerJH
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeOtherJH *m_bfmeOther;		// 0x10
};

class BfmeThingJH
{
public:
	int bfmeGoJH(void);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeOwnerJH *m_bfmeOwner;		// 0x1c
};

int BfmeThingJH::bfmeGoJH(void)
{
	BfmeMakerJH *maker = m_bfmeOwner->m_bfmeOther->m_bfmeMaker;

	BfmeItemJH *got = maker->bfmeFindJH();

	if (got == 0)
		return -2;

	got->bfmeDoJH(0);

	return 0;
}

class BfmeItemJL
{
public:
	virtual void bfmeSpare000JL(void) = 0;
	virtual void bfmeSpare001JL(void) = 0;
	virtual void bfmeSpare002JL(void) = 0;
	virtual void bfmeSpare003JL(void) = 0;
	virtual void bfmeSpare004JL(void) = 0;
	virtual void bfmeSpare005JL(void) = 0;
	virtual void bfmeSpare006JL(void) = 0;
	virtual void bfmeSpare007JL(void) = 0;
	virtual void bfmeSpare008JL(void) = 0;
	virtual void bfmeSpare009JL(void) = 0;
	virtual void bfmeSpare010JL(void) = 0;
	virtual void bfmeDoJL(int how) = 0;
};

class BfmeMakerJL
{
public:
	virtual void bfmeSpare000JL(void) = 0;
	virtual void bfmeSpare001JL(void) = 0;
	virtual void bfmeSpare002JL(void) = 0;
	virtual void bfmeSpare003JL(void) = 0;
	virtual void bfmeSpare004JL(void) = 0;
	virtual void bfmeSpare005JL(void) = 0;
	virtual void bfmeSpare006JL(void) = 0;
	virtual void bfmeSpare007JL(void) = 0;
	virtual void bfmeSpare008JL(void) = 0;
	virtual void bfmeSpare009JL(void) = 0;
	virtual void bfmeSpare010JL(void) = 0;
	virtual void bfmeSpare011JL(void) = 0;
	virtual void bfmeSpare012JL(void) = 0;
	virtual void bfmeSpare013JL(void) = 0;
	virtual void bfmeSpare014JL(void) = 0;
	virtual void bfmeSpare015JL(void) = 0;
	virtual void bfmeSpare016JL(void) = 0;
	virtual void bfmeSpare017JL(void) = 0;
	virtual void bfmeSpare018JL(void) = 0;
	virtual void bfmeSpare019JL(void) = 0;
	virtual void bfmeSpare020JL(void) = 0;
	virtual void bfmeSpare021JL(void) = 0;
	virtual void bfmeSpare022JL(void) = 0;
	virtual void bfmeSpare023JL(void) = 0;
	virtual void bfmeSpare024JL(void) = 0;
	virtual void bfmeSpare025JL(void) = 0;
	virtual void bfmeSpare026JL(void) = 0;
	virtual void bfmeSpare027JL(void) = 0;
	virtual void bfmeSpare028JL(void) = 0;
	virtual void bfmeSpare029JL(void) = 0;
	virtual void bfmeSpare030JL(void) = 0;
	virtual void bfmeSpare031JL(void) = 0;
	virtual void bfmeSpare032JL(void) = 0;
	virtual void bfmeSpare033JL(void) = 0;
	virtual void bfmeSpare034JL(void) = 0;
	virtual void bfmeSpare035JL(void) = 0;
	virtual void bfmeSpare036JL(void) = 0;
	virtual void bfmeSpare037JL(void) = 0;
	virtual void bfmeSpare038JL(void) = 0;
	virtual void bfmeSpare039JL(void) = 0;
	virtual void bfmeSpare040JL(void) = 0;
	virtual void bfmeSpare041JL(void) = 0;
	virtual void bfmeSpare042JL(void) = 0;
	virtual void bfmeSpare043JL(void) = 0;
	virtual void bfmeSpare044JL(void) = 0;
	virtual void bfmeSpare045JL(void) = 0;
	virtual void bfmeSpare046JL(void) = 0;
	virtual void bfmeSpare047JL(void) = 0;
	virtual void bfmeSpare048JL(void) = 0;
	virtual void bfmeSpare049JL(void) = 0;
	virtual void bfmeSpare050JL(void) = 0;
	virtual void bfmeSpare051JL(void) = 0;
	virtual void bfmeSpare052JL(void) = 0;
	virtual void bfmeSpare053JL(void) = 0;
	virtual void bfmeSpare054JL(void) = 0;
	virtual void bfmeSpare055JL(void) = 0;
	virtual void bfmeSpare056JL(void) = 0;
	virtual void bfmeSpare057JL(void) = 0;
	virtual void bfmeSpare058JL(void) = 0;
	virtual void bfmeSpare059JL(void) = 0;
	virtual void bfmeSpare060JL(void) = 0;
	virtual void bfmeSpare061JL(void) = 0;
	virtual void bfmeSpare062JL(void) = 0;
	virtual void bfmeSpare063JL(void) = 0;
	virtual void bfmeSpare064JL(void) = 0;
	virtual void bfmeSpare065JL(void) = 0;
	virtual void bfmeSpare066JL(void) = 0;
	virtual void bfmeSpare067JL(void) = 0;
	virtual void bfmeSpare068JL(void) = 0;
	virtual void bfmeSpare069JL(void) = 0;
	virtual void bfmeSpare070JL(void) = 0;
	virtual void bfmeSpare071JL(void) = 0;
	virtual void bfmeSpare072JL(void) = 0;
	virtual void bfmeSpare073JL(void) = 0;
	virtual void bfmeSpare074JL(void) = 0;
	virtual void bfmeSpare075JL(void) = 0;
	virtual void bfmeSpare076JL(void) = 0;
	virtual void bfmeSpare077JL(void) = 0;
	virtual void bfmeSpare078JL(void) = 0;
	virtual void bfmeSpare079JL(void) = 0;
	virtual void bfmeSpare080JL(void) = 0;
	virtual BfmeItemJL *bfmeFindJL(void) = 0;
};

struct BfmeOtherJL
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeMakerJL *m_bfmeMaker;		// 0x204
};

struct BfmeOwnerJL
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeOtherJL *m_bfmeOther;		// 0x10
};

class BfmeThingJL
{
public:
	int bfmeGoJL(void);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeOwnerJL *m_bfmeOwner;		// 0x1c
};

int BfmeThingJL::bfmeGoJL(void)
{
	BfmeMakerJL *maker = m_bfmeOwner->m_bfmeOther->m_bfmeMaker;

	BfmeItemJL *got = maker->bfmeFindJL();

	if (got == 0)
		return -2;

	got->bfmeDoJL(0);

	return 0;
}
