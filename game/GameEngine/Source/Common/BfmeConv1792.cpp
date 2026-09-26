class BfmeThingWQ;

class BfmeInnerWQ
{
public:
	BfmeThingWQ *bfmeResolveWQ(void);
};

class BfmeThingWQ
{
public:
	int m_bfmeSpareWQ;
	BfmeInnerWQ *m_bfmeInnerWQ;
	unsigned char m_bfmeGapWQ[0xc0];
	int m_bfmeBitsWQ[1];
};

class BfmeHolderWQ
{
public:
	int m_bfmeSpareWQ;
	BfmeThingWQ *m_bfmeThingWQ;
};

class BfmeNodeWQ
{
public:
	BfmeNodeWQ *m_bfmeNextWQ;
	int m_bfmeSpareWQ;
	BfmeHolderWQ *m_bfmeHolderWQ;
};

class BfmeOwnerWQ
{
public:
	char bfmeHasWQ(unsigned int bit);

	unsigned char m_bfmeHeadWQ[0x18];
	BfmeNodeWQ *m_bfmeListWQ;
};

char BfmeOwnerWQ::bfmeHasWQ(unsigned int bit)
{
	BfmeNodeWQ *sentinel = m_bfmeListWQ;
	BfmeNodeWQ *node;

	for (node = sentinel->m_bfmeNextWQ; node != sentinel; node = node->m_bfmeNextWQ)
	{
		BfmeHolderWQ *holder = node->m_bfmeHolderWQ;

		if (holder)
		{
			BfmeThingWQ *thing = holder->m_bfmeThingWQ;

			if (thing && thing->m_bfmeInnerWQ)
				thing = thing->m_bfmeInnerWQ->bfmeResolveWQ();

			if ((thing->m_bfmeBitsWQ[bit >> 5] & (1 << (bit & 0x1f))) == 0)
				return 0;
		}
	}

	return 1;
}
