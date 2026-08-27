// Four short pieces of chain and record keeping.

class BfmeHolderXU
{
public:
	unsigned char m_bfmeHead[0x58];		// 0x00
	unsigned char m_bfmeBusy;		// 0x58
};

class BfmeThingXU
{
public:
	int bfmeFreeXU(void) const;

private:
	int m_bfmeFirst;			// 0x0
	BfmeHolderXU *m_bfmeHolder;		// 0x4
};

int BfmeThingXU::bfmeFreeXU(void) const
{
	BfmeHolderXU *holder = m_bfmeHolder;

	if (holder != 0 && holder->m_bfmeBusy != 0)
		return 0;

	return 1;
}

class BfmeKeyXW
{
public:
	int bfmeDiffersXW(const BfmeKeyXW *other) const;

private:
	int m_bfmeNumber;			// 0x0
	unsigned short m_bfmeTag;		// 0x4
};

int BfmeKeyXW::bfmeDiffersXW(const BfmeKeyXW *other) const
{
	if (m_bfmeNumber == other->m_bfmeNumber && m_bfmeTag == other->m_bfmeTag)
		return 0;

	return 1;
}

class BfmeLinkXX;

class BfmeReachXX
{
public:
	BfmeLinkXX *m_bfmeBack;			// 0x00
	unsigned char m_bfmeBody[0xc];		// 0x04
	BfmeReachXX *m_bfmeOn;			// 0x10
};

class BfmeLinkXX
{
public:
	void bfmeDropXX(void);

private:
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeReachXX *m_bfmeOn;			// 0x10
	BfmeLinkXX *m_bfmeBack;			// 0x14
};

void BfmeLinkXX::bfmeDropXX(void)
{
	if (m_bfmeOn != 0)
	{
		if (m_bfmeBack != 0)
			m_bfmeBack->m_bfmeOn = m_bfmeOn;

		m_bfmeOn->m_bfmeBack = m_bfmeBack;
		m_bfmeOn = 0;
	}
}

struct BfmeNodeXZ
{
	BfmeNodeXZ *m_bfmeNext;			// 0x0
};

struct BfmeHeadXZ
{
	BfmeNodeXZ *m_bfmeFirst;		// 0x0
	BfmeNodeXZ *m_bfmeSecond;		// 0x4
};

void __stdcall bfmeInsertXZ(BfmeHeadXZ *head, BfmeNodeXZ *node, BfmeNodeXZ *after)
{
	if (after != 0)
	{
		node->m_bfmeNext = after->m_bfmeNext;
		after->m_bfmeNext = node;
	}
	else
	{
		node->m_bfmeNext = head->m_bfmeSecond;
		head->m_bfmeSecond = node;
	}
}
