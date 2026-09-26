// Five short bodies: a count, a search, a busy test, a flag read from a part
// looking back at its whole, and a pair of marks set together.

class BfmeListYA
{
public:
	int bfmeCountYA(void) const;

private:
	unsigned char m_bfmeHead[0x44];		// 0x00
	int m_bfmeFrom;				// 0x44
	int m_bfmeTo;				// 0x48
};

int BfmeListYA::bfmeCountYA(void) const
{
	return (m_bfmeTo - m_bfmeFrom) / 12;
}

struct BfmeEntryYB
{
	int m_bfmeKey;				// 0x00
	unsigned char m_bfmeBody[0x50];		// 0x04
};

class BfmeTableYB
{
public:
	BfmeEntryYB *bfmeFindYB(int key) const;

private:
	unsigned char m_bfmeHead[0x98];		// 0x00
	BfmeEntryYB *m_bfmeBegin;		// 0x98
	BfmeEntryYB *m_bfmeEnd;			// 0x9c
};

BfmeEntryYB *BfmeTableYB::bfmeFindYB(int key) const
{
	BfmeEntryYB *at = m_bfmeBegin;
	BfmeEntryYB *end = m_bfmeEnd;

	while (at != end)
	{
		if (at->m_bfmeKey == key)
			return at;

		++at;
	}

	return 0;
}

struct BfmePairYC
{
	int m_bfmeLeft;				// 0x0
	int m_bfmeRight;			// 0x4
};

class BfmeJobYC
{
public:
	unsigned char m_bfmeHead[8];		// 0x00
	BfmePairYC *m_bfmeFrom;			// 0x08
	BfmePairYC *m_bfmeTo;			// 0x0c
	int m_bfmeSpare;			// 0x10
	int m_bfmeKind;				// 0x14
};

class BfmeThingYC
{
public:
	unsigned char bfmeBusyYC(void) const;

private:
	unsigned char m_bfmeHead[0xb58];	// 0x000
	BfmeJobYC *m_bfmeJob;			// 0xb58
};

unsigned char BfmeThingYC::bfmeBusyYC(void) const
{
	BfmeJobYC *job = m_bfmeJob;

	if (job != 0)
	{
		if (job->m_bfmeKind != 1)
			return 1;

		unsigned int count = (unsigned int)(job->m_bfmeTo - job->m_bfmeFrom);

		if (count > 0)
			return 1;
	}

	return 0;
}

class BfmeMarksYE
{
public:
	void bfmeSetYE(unsigned char on, unsigned char value);

private:
	unsigned char m_bfmeHead[0x2d];		// 0x00
	unsigned char m_bfmeHeld;		// 0x2d
	unsigned char m_bfmeSpare;		// 0x2e
	unsigned char m_bfmeOn;			// 0x2f
	unsigned char m_bfmeValue;		// 0x30
};

void BfmeMarksYE::bfmeSetYE(unsigned char on, unsigned char value)
{
	m_bfmeOn = on;

	if (on != 0)
	{
		m_bfmeHeld = 0;
		m_bfmeValue = value;
	}
	else
	{
		m_bfmeValue = value;
	}
}
