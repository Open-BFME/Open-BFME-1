// Two errands: six held pieces each let go of through their own table before
// all six slots are emptied and a yes is handed back, and every row of the
// record told the word unless the record is already marked.

struct BfmeItemLK;

struct BfmeOpsLK
{
	void (__stdcall *m_bfmeSpare000)(BfmeItemLK *item);
	void (__stdcall *m_bfmeSpare001)(BfmeItemLK *item);
	void (__stdcall *m_bfmeDrop)(BfmeItemLK *item);
};

struct BfmeItemLK
{
	BfmeOpsLK *m_bfmeOps;			// 0x0
};

class BfmeThingLK
{
public:
	int bfmeClearLK(void);

private:
	unsigned char m_bfmeHead[8];		// 0x00
	BfmeItemLK *m_bfmeFirst;		// 0x08
	BfmeItemLK *m_bfmeFifth;		// 0x0c
	BfmeItemLK *m_bfmeSixth;		// 0x10
	BfmeItemLK *m_bfmeFourth;		// 0x14
	BfmeItemLK *m_bfmeSecond;		// 0x18
	BfmeItemLK *m_bfmeThird;		// 0x1c
};

int BfmeThingLK::bfmeClearLK(void)
{
	if (m_bfmeFirst != 0)
		m_bfmeFirst->m_bfmeOps->m_bfmeDrop(m_bfmeFirst);

	if (m_bfmeSecond != 0)
		m_bfmeSecond->m_bfmeOps->m_bfmeDrop(m_bfmeSecond);

	if (m_bfmeThird != 0)
		m_bfmeThird->m_bfmeOps->m_bfmeDrop(m_bfmeThird);

	if (m_bfmeFourth != 0)
		m_bfmeFourth->m_bfmeOps->m_bfmeDrop(m_bfmeFourth);

	if (m_bfmeFifth != 0)
		m_bfmeFifth->m_bfmeOps->m_bfmeDrop(m_bfmeFifth);

	if (m_bfmeSixth != 0)
		m_bfmeSixth->m_bfmeOps->m_bfmeDrop(m_bfmeSixth);

	m_bfmeFirst = 0;
	m_bfmeSecond = 0;
	m_bfmeThird = 0;
	m_bfmeFourth = 0;
	m_bfmeFifth = 0;
	m_bfmeSixth = 0;

	return 1;
}


class BfmeItemLM
{
public:
	virtual void bfmeDoLM(void *one, void *two, void *three) = 0;
};

class BfmeSubLM
{
public:
	virtual void bfmeSpare000LM(void);
	virtual BfmeItemLM *bfmeFindLM(void);
};

struct BfmeRowLM
{
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeSubLM m_bfmeSub;			// 0xc
};

struct BfmeOtherLM
{
	unsigned char m_bfmeHead[0x74];		// 0x000
	int m_bfmeTag;				// 0x074
	unsigned char m_bfmeGap[0x328];		// 0x078
	int m_bfmeFlag;				// 0x3a0
};

class BfmeThingLM
{
public:
	void bfmeTellLM(BfmeOtherLM *other, void *one, void *two);

private:
	unsigned char m_bfmeHead[4];		// 0x000
	int m_bfmeSecond;			// 0x004
	unsigned char m_bfmeGap[0x18];		// 0x008
	unsigned char m_bfmeFlags;		// 0x020
	unsigned char m_bfmeGap2[0x15f];	// 0x021
	BfmeRowLM **m_bfmeRows;			// 0x180
	unsigned char m_bfmeGap3[0x1ac];	// 0x184
	int m_bfmeTag;				// 0x330
};

void BfmeThingLM::bfmeTellLM(BfmeOtherLM *other, void *one, void *two)
{
	if (m_bfmeTag == other->m_bfmeTag)
		return;

	if (other->m_bfmeFlag != 0 && m_bfmeSecond != 0)
		return;

	BfmeRowLM **row = m_bfmeRows;

	while (*row != 0)
	{
		BfmeItemLM *got = (*row)->m_bfmeSub.bfmeFindLM();

		if (got != 0)
		{
			if ((m_bfmeFlags & 0x10) != 0)
				return;

			got->bfmeDoLM(other, one, two);
		}

		++row;
	}
}

