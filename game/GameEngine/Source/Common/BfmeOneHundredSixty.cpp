// A mark chosen by the first bit set, a block of settings put back to nothing,
// and two ways of taking a node out of the chain it sits in.

class BfmeThingZN
{
public:
	unsigned char bfmePickZN(unsigned char which) const;

private:
	unsigned char m_bfmeHead[0x62a];	// 0x000
	unsigned char m_bfmePlain;		// 0x62a
	unsigned char m_bfmeSecond;		// 0x62b
	unsigned char m_bfmeThird;		// 0x62c
	unsigned char m_bfmeFirst;		// 0x62d
	unsigned char m_bfmeFifth;		// 0x62e
};

unsigned char BfmeThingZN::bfmePickZN(unsigned char which) const
{
	if ((which & 1) != 0)
		return m_bfmeFirst;

	if ((which & 2) != 0)
		return m_bfmeSecond;

	if ((which & 4) != 0)
		return m_bfmeThird;

	if ((which & 0x10) != 0)
		return m_bfmeFifth;

	return m_bfmePlain;
}

class BfmeSettingsZQ
{
public:
	void bfmeResetZQ(void);

private:
	unsigned char m_bfmeHead[0x3ec];	// 0x3ec
	int m_bfmeFirst;			// 0x3ec
	int m_bfmeSecond;			// 0x3f0
	int m_bfmeThird;			// 0x3f4
	int m_bfmeFourth;			// 0x3f8
	int m_bfmeFifth;			// 0x3fc
	unsigned char m_bfmeOne;		// 0x400
	unsigned char m_bfmeTwo;		// 0x401
	unsigned char m_bfmeThree;		// 0x402
	unsigned char m_bfmeFour;		// 0x403
	unsigned char m_bfmeFive;		// 0x404
};

void BfmeSettingsZQ::bfmeResetZQ(void)
{
	m_bfmeFirst = 0;
	m_bfmeOne = 0;
	m_bfmeFive = 0;
	m_bfmeFour = 0;
	m_bfmeTwo = 0;
	m_bfmeSecond = 0;
	m_bfmeThree = 0;
	m_bfmeThird = 0;
	m_bfmeFourth = 0;
	m_bfmeFifth = 0;
}

struct BfmeNodeZP
{
	unsigned char m_bfmeHead[0x108];	// 0x000
	BfmeNodeZP *m_bfmeBefore;		// 0x108
	BfmeNodeZP *m_bfmeAfter;		// 0x10c
};

class BfmeListZP
{
public:
	void bfmeDropZP(BfmeNodeZP *node);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	BfmeNodeZP *m_bfmeLast;			// 0x8
};

void BfmeListZP::bfmeDropZP(BfmeNodeZP *node)
{
	if (node == 0)
		return;

	if (node->m_bfmeBefore != 0)
		node->m_bfmeBefore->m_bfmeAfter = node->m_bfmeAfter;

	if (node->m_bfmeAfter != 0)
		node->m_bfmeAfter->m_bfmeBefore = node->m_bfmeBefore;
	else
		m_bfmeLast = node->m_bfmeBefore;
}

class BfmeNodeZK;

class BfmeOwnerZK
{
public:
	unsigned char m_bfmeHead[0x98];		// 0x00
	BfmeNodeZK *m_bfmeLast;			// 0x98
	BfmeNodeZK *m_bfmeFirst;		// 0x9c
};

class BfmeNodeZK
{
public:
	void bfmeLeaveZK(void);

	BfmeOwnerZK *m_bfmeOwner;		// 0x0
	BfmeNodeZK *m_bfmeAfter;		// 0x4
	BfmeNodeZK *m_bfmeBefore;		// 0x8
};

void BfmeNodeZK::bfmeLeaveZK(void)
{
	BfmeOwnerZK *owner = m_bfmeOwner;

	if (owner == 0)
		return;

	if (m_bfmeAfter != 0)
		m_bfmeAfter->m_bfmeBefore = m_bfmeBefore;
	else
		owner->m_bfmeLast = m_bfmeBefore;

	if (m_bfmeBefore != 0)
		m_bfmeBefore->m_bfmeAfter = m_bfmeAfter;
	else
		m_bfmeOwner->m_bfmeFirst = m_bfmeAfter;

	m_bfmeAfter = 0;
	m_bfmeBefore = 0;
	m_bfmeOwner = 0;
}
