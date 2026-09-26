// Three small bodies the retail image emits twice each, both copies converted
// here under their own names: a row of slots each given the same fixed-width
// value, a maker flagged before a count is fetched through the table with
// anything positive reported as nothing, and a run of words moved along.
struct BfmeElemJN
{
	int m_bfmeWords[7];			// 0x00
};

void bfmeFillJN(BfmeElemJN *slots, unsigned int count, const BfmeElemJN *what)
{
	unsigned int left = count;
	BfmeElemJN *at = slots;
	const BfmeElemJN *from = what;

	while (left > 0)
	{
		if (at != 0)
			*at = *from;

		++at;
		--left;
	}
}

struct BfmeElemJR
{
	int m_bfmeWords[7];			// 0x00
};

void bfmeFillJR(BfmeElemJR *slots, unsigned int count, const BfmeElemJR *what)
{
	unsigned int left = count;
	BfmeElemJR *at = slots;
	const BfmeElemJR *from = what;

	while (left > 0)
	{
		if (at != 0)
			*at = *from;

		++at;
		--left;
	}
}

class BfmeItemJQ
{
public:
	virtual void bfmeSpare000JQ(void) = 0;
	virtual void bfmeSpare001JQ(void) = 0;
	virtual void bfmeSpare002JQ(void) = 0;
	virtual void bfmeSpare003JQ(void) = 0;
	virtual int bfmeDoJQ(void) = 0;
};

struct BfmeMakerJQ
{
	unsigned char m_bfmeHead[0x326];	// 0x000
	unsigned char m_bfmeOff;		// 0x326
	unsigned char m_bfmePad;		// 0x327
	unsigned char m_bfmeOn;			// 0x328
};

struct BfmeOtherJQ
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeMakerJQ *m_bfmeMaker;		// 0x204
};

struct BfmeOwnerJQ
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeOtherJQ *m_bfmeOther;		// 0x10
};

class BfmeThingJQ
{
public:
	int bfmeAskJQ(void);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeOwnerJQ *m_bfmeOwner;		// 0x1c
	unsigned char m_bfmeGap[4];		// 0x20
	BfmeItemJQ *m_bfmeItem;		// 0x24
};

int BfmeThingJQ::bfmeAskJQ(void)
{
	BfmeMakerJQ *maker = m_bfmeOwner->m_bfmeOther->m_bfmeMaker;

	if (maker != 0)
	{
		maker->m_bfmeOn = 1;
		maker->m_bfmeOff = 0;
	}

	int got = m_bfmeItem->bfmeDoJQ();

	return (got > 0) ? 0 : got;
}

class BfmeItemJT
{
public:
	virtual void bfmeSpare000JT(void) = 0;
	virtual void bfmeSpare001JT(void) = 0;
	virtual void bfmeSpare002JT(void) = 0;
	virtual void bfmeSpare003JT(void) = 0;
	virtual int bfmeDoJT(void) = 0;
};

struct BfmeMakerJT
{
	unsigned char m_bfmeHead[0x326];	// 0x000
	unsigned char m_bfmeOff;		// 0x326
	unsigned char m_bfmePad;		// 0x327
	unsigned char m_bfmeOn;			// 0x328
};

struct BfmeOtherJT
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeMakerJT *m_bfmeMaker;		// 0x204
};

struct BfmeOwnerJT
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeOtherJT *m_bfmeOther;		// 0x10
};

class BfmeThingJT
{
public:
	int bfmeAskJT(void);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeOwnerJT *m_bfmeOwner;		// 0x1c
	unsigned char m_bfmeGap[4];		// 0x20
	BfmeItemJT *m_bfmeItem;		// 0x24
};

int BfmeThingJT::bfmeAskJT(void)
{
	BfmeMakerJT *maker = m_bfmeOwner->m_bfmeOther->m_bfmeMaker;

	if (maker != 0)
	{
		maker->m_bfmeOn = 1;
		maker->m_bfmeOff = 0;
	}

	int got = m_bfmeItem->bfmeDoJT();

	return (got > 0) ? 0 : got;
}

struct BfmeThingJO
{
	void bfmeFlushJO(void);

	unsigned char m_bfmeHead[0x14];		// 0x00
	int *m_bfmeOut;				// 0x14
	int *m_bfmeEnd;				// 0x18
};

void BfmeThingJO::bfmeFlushJO(void)
{
	int *first = m_bfmeEnd;
	int *out = m_bfmeOut;

	int count = (int)(m_bfmeEnd - first);

	while (count > 0)
	{
		*out = *first;

		++first;
		++out;
		--count;
	}

	m_bfmeEnd = out;
}

struct BfmeThingJU
{
	void bfmeFlushJU(void);

	unsigned char m_bfmeHead[0x14];		// 0x00
	int *m_bfmeOut;				// 0x14
	int *m_bfmeEnd;				// 0x18
};

void BfmeThingJU::bfmeFlushJU(void)
{
	int *first = m_bfmeEnd;
	int *out = m_bfmeOut;

	int count = (int)(m_bfmeEnd - first);

	while (count > 0)
	{
		*out = *first;

		++first;
		++out;
		--count;
	}

	m_bfmeEnd = out;
}
