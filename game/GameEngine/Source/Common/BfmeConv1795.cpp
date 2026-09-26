class BfmeThingLP;

class BfmeInnerLP
{
public:
	BfmeThingLP *bfmeResolveLP(void);
};

class BfmeThingLP
{
public:
	void *bfmeTestLP(unsigned int *mask);

	int m_bfmeSpareLP;
	BfmeInnerLP *m_bfmeInnerLP;
};

class BfmeHolderLP
{
public:
	void bfmeHitLP(unsigned int bit);

	int m_bfmeSpareLP;
	BfmeThingLP *m_bfmeThingLP;
};

class BfmeNodeLP
{
public:
	BfmeNodeLP *m_bfmeNextLP;
	int m_bfmeSpareLP;
	BfmeHolderLP *m_bfmeHolderLP;
};

class BfmeOwnerLP
{
public:
	void bfmeSweepLP(unsigned int bit);

	int m_bfmeSpareLP;
	BfmeNodeLP *m_bfmeListLP;
};

void BfmeOwnerLP::bfmeSweepLP(unsigned int bit)
{
	BfmeNodeLP *node;

	for (node = m_bfmeListLP->m_bfmeNextLP; node != m_bfmeListLP; node = node->m_bfmeNextLP)
	{
		BfmeHolderLP *holder = node->m_bfmeHolderLP;
		unsigned int mask = 1 << (bit & 0x1f);
		BfmeThingLP *thing = holder->m_bfmeThingLP;

		if (thing && thing->m_bfmeInnerLP)
			thing = thing->m_bfmeInnerLP->bfmeResolveLP();

		if (thing->bfmeTestLP(&mask))
			holder->bfmeHitLP(bit);
	}
}
