// Two errands: a target stopped and let go of with the maker unmarked, and a
// pair of marks handed over before sixteen rows are taken in turn.

class BfmeTargetHK
{
public:
	virtual void bfmeGoneHK(int how) = 0;
	virtual void bfmeSpare001HK(void) = 0;
	virtual void bfmeSpare002HK(void) = 0;
	virtual void bfmeSpare003HK(void) = 0;
	virtual void bfmeSpare004HK(void) = 0;
	virtual void bfmeSpare005HK(void) = 0;
	virtual void bfmeSpare006HK(void) = 0;
	virtual void bfmeSpare007HK(void) = 0;
	virtual void bfmeSpare008HK(void) = 0;
	virtual void bfmeSpare009HK(void) = 0;
	virtual void bfmeSpare010HK(void) = 0;
	virtual void bfmeSpare011HK(void) = 0;
	virtual void bfmeSpare012HK(void) = 0;
	virtual void bfmeSpare013HK(void) = 0;
	virtual void bfmeSpare014HK(void) = 0;
	virtual void bfmeStopHK(void) = 0;
};

struct BfmeMakerHK
{
	unsigned char m_bfmeHead[0x328];	// 0x000
	unsigned char m_bfmeFlag;		// 0x328
};

struct BfmeOtherHK
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeMakerHK *m_bfmeMaker;		// 0x204
};

struct BfmeOwnerHK
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeOtherHK *m_bfmeOther;		// 0x10
};

class BfmeThingHK
{
public:
	void bfmeDropHK(int spare);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeOwnerHK *m_bfmeOwner;		// 0x1c
	unsigned char m_bfmeGap[4];		// 0x20
	BfmeTargetHK *m_bfmeTarget;		// 0x24
};

void BfmeThingHK::bfmeDropHK(int spare)
{
	BfmeTargetHK *target = m_bfmeTarget;

	if (target != 0)
	{
		target->bfmeStopHK();

		if (m_bfmeTarget != 0)
			m_bfmeTarget->bfmeGoneHK(1);

		m_bfmeTarget = 0;
	}

	BfmeMakerHK *maker = m_bfmeOwner->m_bfmeOther->m_bfmeMaker;

	if (maker != 0)
		maker->m_bfmeFlag = 0;
}

struct BfmePairHL
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};

struct BfmeRowHL
{
	unsigned char m_bfmeBytes[6];		// 0x0
};


class BfmeTargetHL
{
public:
	virtual void bfmeSpare000HL(void) = 0;
	virtual void bfmeSpare001HL(void) = 0;
	virtual void bfmeSpare002HL(void) = 0;
	virtual void bfmeSpare003HL(void) = 0;
	virtual void bfmeSpare004HL(void) = 0;
	virtual void bfmeSpare005HL(void) = 0;
	virtual void bfmeSpare006HL(void) = 0;
	virtual void bfmeSpare007HL(void) = 0;
	virtual void bfmeSpare008HL(void) = 0;
	virtual void bfmeSpare009HL(void) = 0;
	virtual void bfmeFirstHL(BfmePairHL *both) = 0;
	virtual void bfmeSpare011HL(void) = 0;
	virtual void bfmeSpare012HL(void) = 0;
	virtual void bfmeSpare013HL(void) = 0;
	virtual void bfmeSpare014HL(void) = 0;
	virtual void bfmeSpare015HL(void) = 0;
	virtual void bfmeSpare016HL(void) = 0;
	virtual void bfmeSpare017HL(void) = 0;
	virtual void bfmeSpare018HL(void) = 0;
	virtual void bfmeSpare019HL(void) = 0;
	virtual void bfmeSpare020HL(void) = 0;
	virtual void bfmeSpare021HL(void) = 0;
	virtual void bfmeSpare022HL(void) = 0;
	virtual void bfmeSpare023HL(void) = 0;
	virtual void bfmeSpare024HL(void) = 0;
	virtual void bfmeSpare025HL(void) = 0;
	virtual void bfmeSpare026HL(void) = 0;
	virtual void bfmeSpare027HL(void) = 0;
	virtual void bfmeSpare028HL(void) = 0;
	virtual void bfmeSpare029HL(void) = 0;
	virtual void bfmeSpare030HL(void) = 0;
	virtual void bfmeNextHL(BfmeRowHL *row) = 0;
};

class BfmeThingHL
{
public:
	void bfmeGoHL(BfmeTargetHL *target);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeRowHL m_bfmeRows[16];		// 0x4
};

void BfmeThingHL::bfmeGoHL(BfmeTargetHL *target)
{
	BfmePairHL both;

	both.m_bfmeFirst = 1;
	both.m_bfmeSecond = 1;

	target->bfmeFirstHL(&both);

	BfmeRowHL *at = m_bfmeRows;

	for (int left = 16; left != 0; --left)
	{
		target->bfmeNextHL(at);

		++at;
	}
}
