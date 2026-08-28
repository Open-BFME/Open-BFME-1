// Two errands: a newcomer written into the next free record and told to go
// before its six words are copied in beside it, and a pair of counts stepped
// down with the sub-part let go of when the second runs out.

struct BfmeDataLI
{
	int m_bfmeWords[6];			// 0x00
};

class BfmeItemLI
{
public:
	virtual void bfmeDoLI(void) = 0;
};

struct BfmeRecLI
{
	BfmeItemLI *m_bfmeItem;			// 0x00
	BfmeDataLI m_bfmeData;			// 0x04
};

class BfmeThingLI
{
public:
	void bfmeAddLI(BfmeItemLI *item, const BfmeDataLI *data);

private:
	unsigned char m_bfmeHead[0x818];	// 0x000
	int m_bfmeCount;			// 0x818
	BfmeRecLI *m_bfmeRecs;			// 0x81c
};

void BfmeThingLI::bfmeAddLI(BfmeItemLI *item, const BfmeDataLI *data)
{
	m_bfmeRecs[m_bfmeCount].m_bfmeItem = item;

	item->bfmeDoLI();

	m_bfmeRecs[m_bfmeCount].m_bfmeData = *data;

	++m_bfmeCount;
}


class BfmeMakerLJ
{
public:
	virtual void bfmeSpare000LJ(void) = 0;
	virtual void bfmeSpare001LJ(void) = 0;
	virtual void bfmeSpare002LJ(void) = 0;
	virtual void bfmeSpare003LJ(void) = 0;
	virtual void bfmeSpare004LJ(void) = 0;
	virtual void bfmeSpare005LJ(void) = 0;
	virtual void bfmeSpare006LJ(void) = 0;
	virtual void bfmeSpare007LJ(void) = 0;
	virtual void bfmeSpare008LJ(void) = 0;
	virtual void bfmeSpare009LJ(void) = 0;
	virtual void bfmeSpare010LJ(void) = 0;
	virtual void bfmeSpare011LJ(void) = 0;
	virtual void bfmeSpare012LJ(void) = 0;
	virtual void bfmeSpare013LJ(void) = 0;
	virtual void bfmeSpare014LJ(void) = 0;
	virtual void bfmeSpare015LJ(void) = 0;
	virtual void bfmeSpare016LJ(void) = 0;
	virtual void bfmeSpare017LJ(void) = 0;
	virtual void bfmeSpare018LJ(void) = 0;
	virtual void bfmeSpare019LJ(void) = 0;
	virtual void bfmeSpare020LJ(void) = 0;
	virtual void bfmeSpare021LJ(void) = 0;
	virtual void bfmeSpare022LJ(void) = 0;
	virtual void bfmeSpare023LJ(void) = 0;
	virtual void bfmeSpare024LJ(void) = 0;
	virtual void bfmeSpare025LJ(void) = 0;
	virtual void bfmeSpare026LJ(void) = 0;
	virtual void bfmeSpare027LJ(void) = 0;
	virtual void bfmeSpare028LJ(void) = 0;
	virtual void bfmeSpare029LJ(void) = 0;
	virtual void bfmeSpare030LJ(void) = 0;
	virtual void bfmeSpare031LJ(void) = 0;
	virtual void bfmeSpare032LJ(void) = 0;
	virtual void bfmeSpare033LJ(void) = 0;
	virtual void bfmeSpare034LJ(void) = 0;
	virtual void bfmeSpare035LJ(void) = 0;
	virtual void bfmeSpare036LJ(void) = 0;
	virtual void bfmeSpare037LJ(void) = 0;
	virtual void bfmeSpare038LJ(void) = 0;
	virtual void bfmeSpare039LJ(void) = 0;
	virtual void bfmeSpare040LJ(void) = 0;
	virtual void bfmeSpare041LJ(void) = 0;
	virtual void bfmeSpare042LJ(void) = 0;
	virtual void bfmeSpare043LJ(void) = 0;
	virtual void bfmeSpare044LJ(void) = 0;
	virtual void bfmeSpare045LJ(void) = 0;
	virtual void bfmeSpare046LJ(void) = 0;
	virtual void bfmeSpare047LJ(void) = 0;
	virtual void bfmeSpare048LJ(void) = 0;
	virtual void bfmeSpare049LJ(void) = 0;
	virtual void bfmeSpare050LJ(void) = 0;
	virtual void bfmeSpare051LJ(void) = 0;
	virtual void bfmeSpare052LJ(void) = 0;
	virtual void bfmeSpare053LJ(void) = 0;
	virtual void bfmeSpare054LJ(void) = 0;
	virtual void bfmeSpare055LJ(void) = 0;
	virtual void bfmeSpare056LJ(void) = 0;
	virtual void bfmeSpare057LJ(void) = 0;
	virtual void bfmeSpare058LJ(void) = 0;
	virtual void bfmeSpare059LJ(void) = 0;
	virtual void bfmeSpare060LJ(void) = 0;
	virtual void bfmeSpare061LJ(void) = 0;
	virtual void bfmeSpare062LJ(void) = 0;
	virtual void bfmeSpare063LJ(void) = 0;
	virtual void bfmeSpare064LJ(void) = 0;
	virtual void bfmeSpare065LJ(void) = 0;
	virtual void bfmeSpare066LJ(void) = 0;
	virtual void bfmeSpare067LJ(void) = 0;
	virtual void bfmeSpare068LJ(void) = 0;
	virtual void bfmeSpare069LJ(void) = 0;
	virtual void bfmeSpare070LJ(void) = 0;
	virtual void bfmeSpare071LJ(void) = 0;
	virtual void bfmeSpare072LJ(void) = 0;
	virtual void bfmeSpare073LJ(void) = 0;
	virtual void bfmeSpare074LJ(void) = 0;
	virtual void bfmeSpare075LJ(void) = 0;
	virtual void bfmeSpare076LJ(void) = 0;
	virtual void bfmeSpare077LJ(void) = 0;
	virtual void bfmeSpare078LJ(void) = 0;
	virtual void bfmeSpare079LJ(void) = 0;
	virtual void bfmeSpare080LJ(void) = 0;
	virtual void bfmeSpare081LJ(void) = 0;
	virtual void bfmeSpare082LJ(void) = 0;
	virtual void bfmeSpare083LJ(void) = 0;
	virtual void bfmeSpare084LJ(void) = 0;
	virtual void bfmeSpare085LJ(void) = 0;
	virtual void bfmeSpare086LJ(void) = 0;
	virtual void bfmeSpare087LJ(void) = 0;
	virtual void bfmeSpare088LJ(void) = 0;
	virtual void bfmeSpare089LJ(void) = 0;
	virtual void bfmeSpare090LJ(void) = 0;
	virtual void bfmeSpare091LJ(void) = 0;
	virtual void bfmeSpare092LJ(void) = 0;
	virtual void bfmeSpare093LJ(void) = 0;
	virtual void bfmeSpare094LJ(void) = 0;
	virtual void bfmeSpare095LJ(void) = 0;
	virtual unsigned char bfmeStillLJ(void) = 0;
};

class BfmeHostLJ
{
public:
	virtual void bfmeSpare000LJ(void) = 0;
	virtual void bfmeSpare001LJ(void) = 0;
	virtual void bfmeSpare002LJ(void) = 0;
	virtual void bfmeSpare003LJ(void) = 0;
	virtual void bfmeSpare004LJ(void) = 0;
	virtual void bfmeSpare005LJ(void) = 0;
	virtual void bfmeSpare006LJ(void) = 0;
	virtual void bfmeSpare007LJ(void) = 0;
	virtual void bfmeSpare008LJ(void) = 0;
	virtual void bfmeSpare009LJ(void) = 0;
	virtual int bfmeAskLJ(void) = 0;

	unsigned char m_bfmeGap[0x200];		// 0x004
	BfmeMakerLJ *m_bfmeMaker;		// 0x204
};

class BfmeSubLJ
{
public:
	virtual void bfmeSpare000LJ(void);
	virtual void bfmeSpare001LJ(void);
	virtual void bfmeDropLJ(int how);
};

class BfmeThingLJ
{
public:
	int bfmeStepLJ(void);

private:
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeSubLJ m_bfmeSub;			// 0x10
	int m_bfmeFirst;			// 0x14
	int m_bfmeSecond;			// 0x18
};

int BfmeThingLJ::bfmeStepLJ(void)
{
	int ok = (*(BfmeHostLJ **)((char *)this - 8))->bfmeAskLJ();

	BfmeMakerLJ *maker = (*(BfmeHostLJ **)((char *)this - 8))->m_bfmeMaker;

	if (ok != 0 && maker != 0)
	{
		if (m_bfmeFirst > 0)
			--m_bfmeFirst;

		if (m_bfmeSecond > 0)
		{
			if (--m_bfmeSecond == 0 || maker->bfmeStillLJ() == 0)
			{
				m_bfmeSub.bfmeDropLJ(1);

				m_bfmeSecond = 0;
			}
		}

		return 1;
	}

	return 0x3fffffff;
}

