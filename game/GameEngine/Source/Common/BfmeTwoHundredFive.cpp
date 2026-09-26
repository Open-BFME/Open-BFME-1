// Four errands: six numbers passed on with a seventh of the record own added
// in the middle, a target let go of and the maker told twice over, and a run
// told two things.

class BfmeThingHC
{
public:
	virtual void bfmeSpare000HC(void) = 0;
	virtual void bfmeSpare001HC(void) = 0;
	virtual void bfmeSpare002HC(void) = 0;
	virtual void bfmeSpare003HC(void) = 0;
	virtual void bfmeSpare004HC(void) = 0;
	virtual void bfmeSpare005HC(void) = 0;
	virtual void bfmeSpare006HC(void) = 0;
	virtual void bfmeSpare007HC(void) = 0;
	virtual void bfmeSpare008HC(void) = 0;
	virtual void bfmeDoHC(int a, int b, int c, int d, int extra, int e, int f) = 0;

	void bfmeGoHC(int a, int b, int c, int d, int e, int f);

private:
	unsigned char m_bfmeHead[0x12a8];	// 0x0004
	int m_bfmeExtra;			// 0x12ac
};

void BfmeThingHC::bfmeGoHC(int a, int b, int c, int d, int e, int f)
{
	bfmeDoHC(a, b, c, d, m_bfmeExtra, e, f);
}


class BfmeMakerHE
{
public:
	virtual void bfmeSpare000HE(void) = 0;
	virtual void bfmeSpare001HE(void) = 0;
	virtual void bfmeSpare002HE(void) = 0;
	virtual void bfmeSpare003HE(void) = 0;
	virtual void bfmeSpare004HE(void) = 0;
	virtual void bfmeSpare005HE(void) = 0;
	virtual void bfmeSpare006HE(void) = 0;
	virtual void bfmeSpare007HE(void) = 0;
	virtual void bfmeSpare008HE(void) = 0;
	virtual void bfmeSpare009HE(void) = 0;
	virtual void bfmeSpare010HE(void) = 0;
	virtual void bfmeSpare011HE(void) = 0;
	virtual void bfmeSpare012HE(void) = 0;
	virtual void bfmeSpare013HE(void) = 0;
	virtual void bfmeSpare014HE(void) = 0;
	virtual void bfmeSpare015HE(void) = 0;
	virtual void bfmeSpare016HE(void) = 0;
	virtual void bfmeSpare017HE(void) = 0;
	virtual void bfmeSpare018HE(void) = 0;
	virtual void bfmeSpare019HE(void) = 0;
	virtual void bfmeSpare020HE(void) = 0;
	virtual void bfmeSpare021HE(void) = 0;
	virtual void bfmeSpare022HE(void) = 0;
	virtual void bfmeSpare023HE(void) = 0;
	virtual void bfmeSpare024HE(void) = 0;
	virtual void bfmeSpare025HE(void) = 0;
	virtual void bfmeSpare026HE(void) = 0;
	virtual void bfmeSpare027HE(void) = 0;
	virtual void bfmeSpare028HE(void) = 0;
	virtual void bfmeSpare029HE(void) = 0;
	virtual void bfmeSpare030HE(void) = 0;
	virtual void bfmeSpare031HE(void) = 0;
	virtual void bfmeSpare032HE(void) = 0;
	virtual void bfmeSpare033HE(void) = 0;
	virtual void bfmeSpare034HE(void) = 0;
	virtual void bfmeSpare035HE(void) = 0;
	virtual void bfmeSpare036HE(void) = 0;
	virtual void bfmeSpare037HE(void) = 0;
	virtual void bfmeSpare038HE(void) = 0;
	virtual void bfmeSpare039HE(void) = 0;
	virtual void bfmeSpare040HE(void) = 0;
	virtual void bfmeSpare041HE(void) = 0;
	virtual void bfmeSpare042HE(void) = 0;
	virtual void bfmeSpare043HE(void) = 0;
	virtual void bfmeSpare044HE(void) = 0;
	virtual void bfmeSpare045HE(void) = 0;
	virtual void bfmeSpare046HE(void) = 0;
	virtual void bfmeSpare047HE(void) = 0;
	virtual void bfmeSpare048HE(void) = 0;
	virtual void bfmeSpare049HE(void) = 0;
	virtual void bfmeSpare050HE(void) = 0;
	virtual void bfmeSpare051HE(void) = 0;
	virtual void bfmeSpare052HE(void) = 0;
	virtual void bfmeSpare053HE(void) = 0;
	virtual void bfmeSpare054HE(void) = 0;
	virtual void bfmeSpare055HE(void) = 0;
	virtual void bfmeSpare056HE(void) = 0;
	virtual void bfmeSpare057HE(void) = 0;
	virtual void bfmeSpare058HE(void) = 0;
	virtual void bfmeSpare059HE(void) = 0;
	virtual void bfmeSpare060HE(void) = 0;
	virtual void bfmeSpare061HE(void) = 0;
	virtual void bfmeSpare062HE(void) = 0;
	virtual void bfmeSpare063HE(void) = 0;
	virtual void bfmeSpare064HE(void) = 0;
	virtual void bfmeSpare065HE(void) = 0;
	virtual void bfmeSpare066HE(void) = 0;
	virtual void bfmeSpare067HE(void) = 0;
	virtual void bfmeSpare068HE(void) = 0;
	virtual void bfmeSpare069HE(void) = 0;
	virtual void bfmeSpare070HE(void) = 0;
	virtual void bfmeSpare071HE(void) = 0;
	virtual void bfmeSpare072HE(void) = 0;
	virtual void bfmeSpare073HE(void) = 0;
	virtual void bfmeSpare074HE(void) = 0;
	virtual void bfmeSpare075HE(void) = 0;
	virtual void bfmeSpare076HE(void) = 0;
	virtual void bfmeSpare077HE(void) = 0;
	virtual void bfmeSpare078HE(void) = 0;
	virtual void bfmeSpare079HE(void) = 0;
	virtual void bfmeSpare080HE(void) = 0;
	virtual void bfmeSpare081HE(void) = 0;
	virtual void bfmeSpare082HE(void) = 0;
	virtual void bfmeSpare083HE(void) = 0;
	virtual void bfmeSpare084HE(void) = 0;
	virtual void bfmeSpare085HE(void) = 0;
	virtual void bfmeSpare086HE(void) = 0;
	virtual void bfmeSpare087HE(void) = 0;
	virtual void bfmeSpare088HE(void) = 0;
	virtual void bfmeSpare089HE(void) = 0;
	virtual void bfmeSpare090HE(void) = 0;
	virtual void bfmeSpare091HE(void) = 0;
	virtual void bfmeSpare092HE(void) = 0;
	virtual void bfmeSpare093HE(void) = 0;
	virtual void bfmeSpare094HE(void) = 0;
	virtual void bfmeSpare095HE(void) = 0;
	virtual void bfmeSpare096HE(void) = 0;
	virtual void bfmeSpare097HE(void) = 0;
	virtual void bfmeSpare098HE(void) = 0;
	virtual void bfmeSpare099HE(void) = 0;
	virtual void bfmeSpare100HE(void) = 0;
	virtual void bfmeSpare101HE(void) = 0;
	virtual void bfmeSpare102HE(void) = 0;
	virtual void bfmeSpare103HE(void) = 0;
	virtual void bfmeSpare104HE(void) = 0;
	virtual void bfmeSpare105HE(void) = 0;
	virtual void bfmeSpare106HE(void) = 0;
	virtual void bfmeSpare107HE(void) = 0;
	virtual void bfmeSpare108HE(void) = 0;
	virtual void bfmeSpare109HE(void) = 0;
	virtual void bfmeTellHE(void) = 0;
};

struct BfmeOtherHE
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeMakerHE *m_bfmeMaker;		// 0x204
};

struct BfmeOwnerHE
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeOtherHE *m_bfmeOther;		// 0x10
};

class BfmeTargetHE
{
public:
	virtual void bfmeDoHE(int how) = 0;
};

class BfmeThingHE
{
public:
	void bfmeDropHE(int spare);
	void bfmeAlsoHE(int spare);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeOwnerHE *m_bfmeOwner;		// 0x1c
	unsigned char m_bfmeGap[4];		// 0x20
	BfmeTargetHE *m_bfmeTarget;		// 0x24
};

void BfmeThingHE::bfmeDropHE(int spare)
{
	BfmeTargetHE *target = m_bfmeTarget;

	if (target != 0)
		target->bfmeDoHE(1);

	m_bfmeTarget = 0;

	m_bfmeOwner->m_bfmeOther->m_bfmeMaker->bfmeTellHE();
}

void BfmeThingHE::bfmeAlsoHE(int spare)
{
	BfmeTargetHE *target = m_bfmeTarget;

	if (target != 0)
		target->bfmeDoHE(1);

	m_bfmeTarget = 0;

	m_bfmeOwner->m_bfmeOther->m_bfmeMaker->bfmeTellHE();
}


class BfmeItemHF
{
public:
	virtual void bfmeSpare000HF(void) = 0;
	virtual void bfmeSpare001HF(void) = 0;
	virtual void bfmeSpare002HF(void) = 0;
	virtual void bfmeSpare003HF(void) = 0;
	virtual void bfmeDoHF(void *first, void *second) = 0;
};

class BfmeThingHF
{
public:
	void bfmeTellHF(void *first, void *second);

private:
	BfmeItemHF **m_bfmeBegin;		// 0x0
	BfmeItemHF **m_bfmeEnd;			// 0x4
};

void BfmeThingHF::bfmeTellHF(void *first, void *second)
{
	BfmeItemHF **at = m_bfmeBegin;

	while (at != m_bfmeEnd)
	{
		(*at)->bfmeDoHF(first, second);

		++at;
	}
}

