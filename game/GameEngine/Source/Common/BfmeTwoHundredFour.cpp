// Two errands: two kept items checked and dropped if the owner no longer wants
// them, and one entry taken off a list by key.

class BfmeItemGZ;

class BfmeOwnerGZ
{
public:
	virtual void bfmeSpare000GZ(void) = 0;
	virtual void bfmeSpare001GZ(void) = 0;
	virtual void bfmeSpare002GZ(void) = 0;
	virtual void bfmeSpare003GZ(void) = 0;
	virtual void bfmeSpare004GZ(void) = 0;
	virtual void bfmeSpare005GZ(void) = 0;
	virtual void bfmeSpare006GZ(void) = 0;
	virtual void bfmeSpare007GZ(void) = 0;
	virtual void bfmeSpare008GZ(void) = 0;
	virtual unsigned char bfmeAskGZ(BfmeItemGZ *item) = 0;
};

class BfmeItemGZ
{
public:
	int m_bfmeFirst;			// 0x0
};

class BfmeThingGZ
{
public:
	void bfmeCheckGZ(void);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	BfmeOwnerGZ *m_bfmeOwner;		// 0x4
	BfmeItemGZ *m_bfmeFirst;		// 0x8
	BfmeItemGZ *m_bfmeSecond;		// 0xc
};

void BfmeThingGZ::bfmeCheckGZ(void)
{
	BfmeItemGZ *first = m_bfmeFirst;

	if (first != 0 && m_bfmeOwner->bfmeAskGZ(first) == 0)
		m_bfmeFirst = 0;

	BfmeItemGZ *second = m_bfmeSecond;

	if (second != 0 && m_bfmeOwner->bfmeAskGZ(second) == 0)
		m_bfmeSecond = 0;
}

class BfmeNodeHA
{
public:
	virtual void bfmeDoHA(int how) = 0;

	int m_bfmeKey;				// 0x4
	BfmeNodeHA *m_bfmeNext;			// 0x8
};

class BfmeThingHA
{
public:
	int bfmeDropHA(int key);

private:
	unsigned char m_bfmeHead[0x20];		// 0x00
	BfmeNodeHA *m_bfmeNode;			// 0x20
};

int BfmeThingHA::bfmeDropHA(int key)
{
	if (key == 0)
		return -2;

	BfmeNodeHA *node = m_bfmeNode;

	if (node != 0 && node->m_bfmeKey == key)
	{
		BfmeNodeHA *next = node->m_bfmeNext;

		node->bfmeDoHA(1);

		m_bfmeNode = next;

		return 0;
	}

	return -1;
}
