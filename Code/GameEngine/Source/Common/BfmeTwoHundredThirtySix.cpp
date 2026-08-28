// Three short errands with nothing but their own memory to work on: a setting
// written down and passed on when it actually changes, the row that follows a
// named one, and the value a key names, reached by counting back along its
// chain.

class BfmeSubMB
{
public:
	virtual void bfmeSpare000MB(void) = 0;
	virtual void bfmeSpare001MB(void) = 0;
	virtual void bfmeSpare002MB(void) = 0;
	virtual void bfmeSpare003MB(void) = 0;
	virtual void bfmeSpare004MB(void) = 0;
	virtual void bfmeSpare005MB(void) = 0;
	virtual void bfmeSpare006MB(void) = 0;
	virtual void bfmeSpare007MB(void) = 0;
	virtual void bfmeSpare008MB(void) = 0;
	virtual void bfmeSpare009MB(void) = 0;
	virtual void bfmeSpare010MB(void) = 0;
	virtual void bfmeSpare011MB(void) = 0;
	virtual void bfmeSpare012MB(void) = 0;
	virtual void bfmeSpare013MB(void) = 0;
	virtual void bfmeSpare014MB(void) = 0;
	virtual void bfmeSpare015MB(void) = 0;
	virtual void bfmeSpare016MB(void) = 0;
	virtual void bfmeTellMB(void *what) = 0;
};

class BfmeThingMB
{
public:
	void bfmeSetMB(void *what);

private:
	unsigned char m_bfmeHead[0xa8];		// 0x000
	void *m_bfmeWhat;			// 0x0a8
	unsigned char m_bfmeGap[0xa4];		// 0x0ac
	BfmeSubMB **m_bfmeList;			// 0x150
};

void BfmeThingMB::bfmeSetMB(void *what)
{
	if (m_bfmeWhat == what)
		return;

	m_bfmeWhat = what;

	BfmeSubMB *sub = *m_bfmeList;

	if (sub == 0)
		return;

	sub->bfmeTellMB(what);
}

struct BfmeRowMC
{
	unsigned char m_bfmeBody[0xbc];		// 0x00
};

struct BfmeOwnerMC
{
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeRowMC *m_bfmeBegin;			// 0x24
	BfmeRowMC *m_bfmeEnd;			// 0x28
};

class BfmeThingMC
{
public:
	BfmeRowMC *bfmeNextMC(BfmeRowMC *want);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeOwnerMC *m_bfmeOwner;		// 0x4
};

BfmeRowMC *BfmeThingMC::bfmeNextMC(BfmeRowMC *want)
{
	BfmeRowMC *at = m_bfmeOwner->m_bfmeBegin;
	BfmeRowMC *end = m_bfmeOwner->m_bfmeEnd;

	bool found = false;

	while (at != end)
	{
		if (found)
			return at;

		if (at == want)
			found = true;

		++at;
	}

	return 0;
}

struct BfmeLinkMD
{
	BfmeLinkMD *m_bfmeNext;			// 0x0
	int m_bfmeValue;			// 0x4
};

struct BfmeRowMD
{
	unsigned char m_bfmeHead[0xe];		// 0x00
	short m_bfmeHave;			// 0x0e
	BfmeLinkMD *m_bfmeHead2;		// 0x10
};

struct BfmeKeyMD
{
	unsigned char m_bfmeHead[4];		// 0x0
	int m_bfmeIndex;			// 0x4
	int m_bfmeBack;				// 0x8
};

class BfmeThingMD
{
public:
	int *bfmeAtMD(const BfmeKeyMD *key);

private:
	unsigned char m_bfmeHead[0x18];		// 0x00
	BfmeRowMD *m_bfmeRows;			// 0x18
};

int *BfmeThingMD::bfmeAtMD(const BfmeKeyMD *key)
{
	int back = key->m_bfmeBack;

	BfmeRowMD *row = &m_bfmeRows[key->m_bfmeIndex];

	int have = row->m_bfmeHave;

	BfmeLinkMD *link = row->m_bfmeHead2;

	if (have > back)
	{
		int steps = have - back;

		do
		{
			--steps;

			link = link->m_bfmeNext;
		}
		while (steps != 0);
	}

	return &link->m_bfmeValue;
}
