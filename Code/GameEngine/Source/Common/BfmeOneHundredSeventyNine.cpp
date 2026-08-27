// A question with two short answers of its own, and a piece of tidying that
// only sometimes needs handing on.

class BfmeOwnerCC
{
public:
	virtual void bfmeSpare000CC(void) = 0;
	virtual void bfmeSpare001CC(void) = 0;
	virtual void bfmeSpare002CC(void) = 0;
	virtual void bfmeSpare003CC(void) = 0;
	virtual int bfmeDoCC(void) = 0;

	unsigned char m_bfmeGap[0x18];		// 0x04
	struct BfmeJobCC *m_bfmeJob;		// 0x1c
};

struct BfmeJobCC
{
	unsigned char m_bfmeHead[4];		// 0x0
	int m_bfmeWhen;				// 0x4
};

class BfmeThingCC
{
public:
	int bfmeAskCC(void);

private:
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeOwnerCC *m_bfmeOwner;		// 0x24
};

int BfmeThingCC::bfmeAskCC(void)
{
	BfmeOwnerCC *owner = m_bfmeOwner;

	if (owner == 0)
		return -2;

	BfmeJobCC *job = owner->m_bfmeJob;

	if (job != 0 && job->m_bfmeWhen == 0xF423E)
		return -1;

	return m_bfmeOwner->bfmeDoCC();
}

struct BfmeItemCD
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	int m_bfmeKind;				// 0x10
	unsigned char m_bfmeGap[0x3c];		// 0x14
	int m_bfmeFirst;			// 0x50
	int m_bfmeSecond;			// 0x54
	unsigned char m_bfmeDone;		// 0x58
};


class BfmeThingCD
{
public:
	virtual void bfmeDoCD(BfmeItemCD *item) = 0;

	void bfmeGoCD(BfmeItemCD *item);
};

void BfmeThingCD::bfmeGoCD(BfmeItemCD *item)
{
	if (item == 0)
		return;

	if (item->m_bfmeKind != 7)
	{
		bfmeDoCD(item);

		return;
	}

	item->m_bfmeFirst = 0;
	item->m_bfmeSecond = 0;
	item->m_bfmeDone = 1;
}
