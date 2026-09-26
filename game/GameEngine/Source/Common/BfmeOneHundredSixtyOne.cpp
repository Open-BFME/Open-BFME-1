// A node joined to whatever owner a holder names, and a node taken out of use
// and put on the spare pile.

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
	BfmeOwnerZK *m_bfmeOwner;		// 0x0
	BfmeNodeZK *m_bfmeAfter;		// 0x4
	BfmeNodeZK *m_bfmeBefore;		// 0x8
};

void bfmeJoinZS(BfmeNodeZK *node, BfmeOwnerZK **holder)
{
	if (node == 0)
		return;

	BfmeOwnerZK *owner = *holder;

	node->m_bfmeOwner = owner;

	if (owner != 0)
	{
		node->m_bfmeAfter = owner->m_bfmeFirst;
		node->m_bfmeBefore = 0;
		owner->m_bfmeFirst = node;

		if (node->m_bfmeAfter != 0)
			node->m_bfmeAfter->m_bfmeBefore = node;
		else
			node->m_bfmeOwner->m_bfmeLast = node;

		return;
	}

	node->m_bfmeBefore = 0;
	node->m_bfmeAfter = 0;
}

struct BfmeHolderZT
{
	BfmeHolderZT *m_bfmeFirst;		// 0x0
};

struct BfmeNodeZT
{
	unsigned char m_bfmeHead[0x2c];		// 0x00
	BfmeHolderZT *m_bfmeBefore;		// 0x2c
	BfmeNodeZT *m_bfmeAfter;		// 0x30
};

class BfmeListZT
{
public:
	void bfmeFreeZT(BfmeNodeZT *node);

private:
	unsigned char m_bfmeHead[0xadec];	// 0x0000
	BfmeNodeZT *m_bfmeSpare;		// 0xadec
	unsigned char m_bfmeGap[4];		// 0xadf0
	BfmeNodeZT *m_bfmeAt;			// 0xadf4
};

void BfmeListZT::bfmeFreeZT(BfmeNodeZT *node)
{
	if (m_bfmeAt == node)
		m_bfmeAt = m_bfmeAt->m_bfmeAfter;

	if (node->m_bfmeAfter != 0)
		node->m_bfmeAfter->m_bfmeBefore = node->m_bfmeBefore;

	node->m_bfmeBefore->m_bfmeFirst = (BfmeHolderZT *)node->m_bfmeAfter;
	node->m_bfmeBefore = 0;
	node->m_bfmeAfter = m_bfmeSpare;
	m_bfmeSpare = node;
}
