// Two short errands: a word passed on only once four things are all in place,
// and a digit written down as one or nought according to a table the record
// keeps.

class BfmeSubMG
{
public:
	virtual void bfmeSpare000MG(void) = 0;
	virtual void bfmeSpare001MG(void) = 0;
	virtual void bfmeSpare002MG(void) = 0;
	virtual void bfmeSpare003MG(void) = 0;
	virtual void bfmeSpare004MG(void) = 0;
	virtual void bfmeSpare005MG(void) = 0;
	virtual void bfmeSpare006MG(void) = 0;
	virtual void bfmeSpare007MG(void) = 0;
	virtual void bfmeSpare008MG(void) = 0;
	virtual void bfmeSpare009MG(void) = 0;
	virtual void bfmeSpare010MG(void) = 0;
	virtual void bfmeSpare011MG(void) = 0;
	virtual void bfmeSpare012MG(void) = 0;
	virtual void bfmeSpare013MG(void) = 0;
	virtual void bfmeSpare014MG(void) = 0;
	virtual void bfmeSpare015MG(void) = 0;
	virtual void bfmeSpare016MG(void) = 0;
	virtual void bfmeSpare017MG(void) = 0;
	virtual void bfmeSpare018MG(void) = 0;
	virtual void bfmeSpare019MG(void) = 0;
	virtual void bfmeSpare020MG(void) = 0;
	virtual void bfmeSpare021MG(void) = 0;
	virtual void bfmeSpare022MG(void) = 0;
	virtual void bfmeSpare023MG(void) = 0;
	virtual void bfmeSpare024MG(void) = 0;
	virtual void bfmeSpare025MG(void) = 0;
	virtual void bfmeSpare026MG(void) = 0;
	virtual void bfmeSpare027MG(void) = 0;
	virtual void bfmeSpare028MG(void) = 0;
	virtual void bfmeSpare029MG(void) = 0;
	virtual void bfmeSpare030MG(void) = 0;
	virtual void bfmeSpare031MG(void) = 0;
	virtual void bfmeSpare032MG(void) = 0;
	virtual unsigned char bfmeDoMG(void *what, int how) = 0;
};

struct BfmeOtherMG
{
	unsigned char m_bfmeHead[0x1fc];	// 0x000
	BfmeSubMG *m_bfmeSub;			// 0x1fc
};

struct BfmeOwnerMG
{
	unsigned char m_bfmeHead[0x51f];	// 0x000
	unsigned char m_bfmeOn;			// 0x51f
};

class BfmeThingMG
{
public:
	unsigned char bfmeTellMG(BfmeOtherMG *other, void *what);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeOwnerMG *m_bfmeOwner;		// 0x4
};

unsigned char BfmeThingMG::bfmeTellMG(BfmeOtherMG *other, void *what)
{
	if (m_bfmeOwner->m_bfmeOn != 0 && what != 0 && other != 0)
	{
		BfmeSubMG *sub = other->m_bfmeSub;

		if (sub != 0)
			return sub->bfmeDoMG(what, 1);
	}

	return 0;
}

class BfmeThingMH
{
public:
	void bfmeMarkMH(int at, unsigned short *out, unsigned char skip);

private:
	unsigned char m_bfmeHead[0x270];	// 0x000
	unsigned char m_bfmeTable[8];		// 0x270
};

void BfmeThingMH::bfmeMarkMH(int at, unsigned short *out, unsigned char skip)
{
	if (skip != 0)
		return;

	*out = 0x30;

	if (at < 1)
		return;

	if (at >= 8)
		return;

	if (at < 0)
		return;

	if (m_bfmeTable[at] != 0)
		*out = 0x31;
}
