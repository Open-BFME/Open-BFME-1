// Four errands: a target told and then let go of, one slot of many cleared, a
// count handed out as the record is emptied, and a question passed a long way
// down.

class BfmeTargetDZ
{
public:
	virtual void bfmeGoDZ(int how) = 0;
	virtual void bfmeSpare001DZ(void) = 0;
	virtual void bfmeSpare002DZ(void) = 0;
	virtual void bfmeSpare003DZ(void) = 0;
	virtual void bfmeSpare004DZ(void) = 0;
	virtual void bfmeTellDZ(void *what) = 0;
};

class BfmeThingDZ
{
public:
	void bfmeDropDZ(void *what);

private:
	unsigned char m_bfmeHead[0x30];		// 0x00
	BfmeTargetDZ *m_bfmeTarget;		// 0x30
};

void BfmeThingDZ::bfmeDropDZ(void *what)
{
	BfmeTargetDZ *target = m_bfmeTarget;

	if (target != 0)
	{
		target->bfmeTellDZ(what);

		if (m_bfmeTarget != 0)
			m_bfmeTarget->bfmeGoDZ(1);

		m_bfmeTarget = 0;
	}
}

class BfmeTargetEA
{
public:
	virtual void bfmeDoEA(int how) = 0;
};

class BfmeThingEA
{
public:
	void bfmeDropEA(int which);

private:
	unsigned char m_bfmeHead[4];		// 0x00
	BfmeTargetEA *m_bfmeSlots[14];		// 0x04
	int m_bfmeMarks[14];			// 0x3c
};

void BfmeThingEA::bfmeDropEA(int which)
{
	BfmeTargetEA *target = m_bfmeSlots[which];

	if (target != 0)
	{
		target->bfmeDoEA(1);

		m_bfmeSlots[which] = 0;
		m_bfmeMarks[which] = 0;
	}
}


class BfmeThingEC
{
public:
	virtual void bfmeSpare000EC(void) = 0;
	virtual void bfmeSpare001EC(void) = 0;
	virtual void bfmeDoEC(void) = 0;

	int bfmeTakeEC(int *out);

private:
	unsigned char m_bfmeHead[0x10];		// 0x04
	int m_bfmeFirst;			// 0x14
	int m_bfmeCount;			// 0x18
	int m_bfmeThird;			// 0x1c
	int m_bfmeFourth;			// 0x20
};

int BfmeThingEC::bfmeTakeEC(int *out)
{
	*out = m_bfmeCount;

	int keep = m_bfmeFirst;

	m_bfmeFourth = 0;
	m_bfmeThird = 0;
	m_bfmeCount = 0;
	m_bfmeFirst = 0;

	bfmeDoEC();

	return keep;
}


class BfmeMakerEE
{
public:
	virtual void bfmeSpare000EE(void) = 0;
	virtual void bfmeSpare001EE(void) = 0;
	virtual void bfmeSpare002EE(void) = 0;
	virtual void bfmeSpare003EE(void) = 0;
	virtual void bfmeSpare004EE(void) = 0;
	virtual void bfmeSpare005EE(void) = 0;
	virtual void bfmeSpare006EE(void) = 0;
	virtual void bfmeSpare007EE(void) = 0;
	virtual void bfmeSpare008EE(void) = 0;
	virtual void bfmeSpare009EE(void) = 0;
	virtual void bfmeSpare010EE(void) = 0;
	virtual void bfmeSpare011EE(void) = 0;
	virtual void bfmeSpare012EE(void) = 0;
	virtual void bfmeSpare013EE(void) = 0;
	virtual void bfmeSpare014EE(void) = 0;
	virtual void bfmeSpare015EE(void) = 0;
	virtual void bfmeSpare016EE(void) = 0;
	virtual void bfmeSpare017EE(void) = 0;
	virtual void bfmeSpare018EE(void) = 0;
	virtual void bfmeSpare019EE(void) = 0;
	virtual void bfmeSpare020EE(void) = 0;
	virtual void bfmeSpare021EE(void) = 0;
	virtual void bfmeSpare022EE(void) = 0;
	virtual void bfmeSpare023EE(void) = 0;
	virtual void bfmeSpare024EE(void) = 0;
	virtual void bfmeSpare025EE(void) = 0;
	virtual void bfmeSpare026EE(void) = 0;
	virtual void bfmeSpare027EE(void) = 0;
	virtual void bfmeSpare028EE(void) = 0;
	virtual void bfmeSpare029EE(void) = 0;
	virtual void bfmeSpare030EE(void) = 0;
	virtual void bfmeSpare031EE(void) = 0;
	virtual void bfmeSpare032EE(void) = 0;
	virtual void bfmeSpare033EE(void) = 0;
	virtual void bfmeSpare034EE(void) = 0;
	virtual void bfmeSpare035EE(void) = 0;
	virtual void bfmeSpare036EE(void) = 0;
	virtual void bfmeSpare037EE(void) = 0;
	virtual void bfmeSpare038EE(void) = 0;
	virtual void bfmeSpare039EE(void) = 0;
	virtual void bfmeSpare040EE(void) = 0;
	virtual void bfmeSpare041EE(void) = 0;
	virtual void bfmeSpare042EE(void) = 0;
	virtual void bfmeSpare043EE(void) = 0;
	virtual void bfmeSpare044EE(void) = 0;
	virtual void bfmeSpare045EE(void) = 0;
	virtual void bfmeSpare046EE(void) = 0;
	virtual void bfmeSpare047EE(void) = 0;
	virtual void bfmeSpare048EE(void) = 0;
	virtual void bfmeSpare049EE(void) = 0;
	virtual void bfmeSpare050EE(void) = 0;
	virtual void bfmeSpare051EE(void) = 0;
	virtual void bfmeSpare052EE(void) = 0;
	virtual void bfmeSpare053EE(void) = 0;
	virtual void bfmeSpare054EE(void) = 0;
	virtual void bfmeSpare055EE(void) = 0;
	virtual void bfmeSpare056EE(void) = 0;
	virtual void bfmeSpare057EE(void) = 0;
	virtual void bfmeSpare058EE(void) = 0;
	virtual void bfmeSpare059EE(void) = 0;
	virtual void bfmeSpare060EE(void) = 0;
	virtual void bfmeSpare061EE(void) = 0;
	virtual void bfmeSpare062EE(void) = 0;
	virtual void bfmeSpare063EE(void) = 0;
	virtual void bfmeSpare064EE(void) = 0;
	virtual void bfmeSpare065EE(void) = 0;
	virtual void bfmeSpare066EE(void) = 0;
	virtual void bfmeSpare067EE(void) = 0;
	virtual void bfmeSpare068EE(void) = 0;
	virtual void bfmeSpare069EE(void) = 0;
	virtual void bfmeSpare070EE(void) = 0;
	virtual void bfmeSpare071EE(void) = 0;
	virtual void bfmeSpare072EE(void) = 0;
	virtual void bfmeSpare073EE(void) = 0;
	virtual void bfmeSpare074EE(void) = 0;
	virtual void bfmeSpare075EE(void) = 0;
	virtual void bfmeSpare076EE(void) = 0;
	virtual void bfmeSpare077EE(void) = 0;
	virtual void bfmeSpare078EE(void) = 0;
	virtual void bfmeSpare079EE(void) = 0;
	virtual void bfmeSpare080EE(void) = 0;
	virtual void bfmeSpare081EE(void) = 0;
	virtual void bfmeSpare082EE(void) = 0;
	virtual void bfmeSpare083EE(void) = 0;
	virtual void bfmeSpare084EE(void) = 0;
	virtual void bfmeSpare085EE(void) = 0;
	virtual void bfmeSpare086EE(void) = 0;
	virtual void bfmeSpare087EE(void) = 0;
	virtual void bfmeSpare088EE(void) = 0;
	virtual void bfmeSpare089EE(void) = 0;
	virtual void bfmeSpare090EE(void) = 0;
	virtual void bfmeSpare091EE(void) = 0;
	virtual void bfmeSpare092EE(void) = 0;
	virtual void bfmeSpare093EE(void) = 0;
	virtual void bfmeSpare094EE(void) = 0;
	virtual void bfmeSpare095EE(void) = 0;
	virtual unsigned char bfmeAskEE(void) = 0;
};

struct BfmeOtherEE
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeMakerEE *m_bfmeMaker;		// 0x204
};

struct BfmeOwnerEE
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeOtherEE *m_bfmeOther;		// 0x10
};

struct BfmeThingEE
{
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeOwnerEE *m_bfmeOwner;		// 0x1c
};

unsigned char bfmeAskEE(BfmeThingEE *thing)
{
	BfmeMakerEE *maker = thing->m_bfmeOwner->m_bfmeOther->m_bfmeMaker;

	if (maker == 0)
		return 0;

	return maker->bfmeAskEE() != 0;
}

