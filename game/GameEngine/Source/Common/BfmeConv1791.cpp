class BfmeThingVQ;

// The +4 link is an Overridable chain: retail calls ILT 0x000022BB ->
// 0x00087A80, matched as Overridable::getFinalOverride (INIWater.cpp).
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

typedef Overridable BfmeInnerVQ;

class BfmeThingVQ
{
public:
	int m_bfmeSpareVQ;
	BfmeInnerVQ *m_bfmeInnerVQ;
	unsigned char m_bfmeGapVQ[0xc0];
	int m_bfmeBitsVQ[1];
};

class BfmeHolderVQ
{
public:
	int m_bfmeSpareVQ;
	BfmeThingVQ *m_bfmeThingVQ;
};

class BfmeNodeVQ
{
public:
	BfmeNodeVQ *m_bfmeNextVQ;
	int m_bfmeSpareVQ;
	BfmeHolderVQ *m_bfmeHolderVQ;
};

class BfmeOwnerVQ
{
public:
	char bfmeHasVQ(unsigned int bit);

	unsigned char m_bfmeHeadVQ[0x18];
	BfmeNodeVQ *m_bfmeListVQ;
};

char BfmeOwnerVQ::bfmeHasVQ(unsigned int bit)
{
	BfmeNodeVQ *sentinel = m_bfmeListVQ;
	BfmeNodeVQ *node;

	for (node = sentinel->m_bfmeNextVQ; node != sentinel; node = node->m_bfmeNextVQ)
	{
		BfmeHolderVQ *holder = node->m_bfmeHolderVQ;

		if (holder)
		{
			BfmeThingVQ *thing = holder->m_bfmeThingVQ;

			if (thing && thing->m_bfmeInnerVQ)
				thing = (BfmeThingVQ *)thing->m_bfmeInnerVQ->getFinalOverride();

			if (thing->m_bfmeBitsVQ[bit >> 5] & (1 << (bit & 0x1f)))
				return 1;
		}
	}

	return 0;
}
