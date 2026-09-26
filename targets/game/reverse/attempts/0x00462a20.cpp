// ?bfmeEachABN@@YAXXZ
// partial score=0.82 date=2026-09-09
class BfmeThingABN
{
public:
	virtual void bfmeSlot0ABN();
	virtual void bfmeSlot1ABN();
	virtual void bfmeSlot2ABN();
	virtual void bfmeSlot3ABN();
	virtual void bfmeSlot4ABN();
	virtual void bfmeTouchABN();
};

struct BfmeNodeABN
{
	BfmeNodeABN *m_bfmeNextABN;
	unsigned int m_bfmeKeyABN;
	unsigned char m_bfmeGapABN[0x10];
	BfmeThingABN *m_bfme18ABN;
};

struct BfmeTableABN
{
	unsigned char m_bfmeHeadABN[4];
	BfmeNodeABN **m_bfmeBucketsABN;
	BfmeNodeABN **m_bfmeEndABN;

	unsigned int bfmeBucketABN(void *key, unsigned int count);
};

struct BfmeIterABN
{
	BfmeNodeABN *m_bfmeNodeABN;
	BfmeTableABN *m_bfmeTableABN;
};

struct BfmeOwnerABN
{
	void bfmeBeginABN(BfmeIterABN *out);
};

extern BfmeOwnerABN g_bfmeOwnerABN;

void bfmeEachABN(void);

void bfmeEachABN(void)
{
	BfmeIterABN it;

	g_bfmeOwnerABN.bfmeBeginABN(&it);

	BfmeNodeABN *n = it.m_bfmeNodeABN;

	while (n != 0)
	{
		BfmeThingABN *t = n->m_bfme18ABN;

		if (t != 0)
			t->bfmeTouchABN();

		BfmeNodeABN *nx = n->m_bfmeNextABN;

		if (nx == 0)
		{
			BfmeTableABN *tb = it.m_bfmeTableABN;
			unsigned int b = tb->bfmeBucketABN(&n->m_bfmeKeyABN,
				(unsigned int)(tb->m_bfmeEndABN - tb->m_bfmeBucketsABN));
			unsigned int cnt = (unsigned int)(tb->m_bfmeEndABN - tb->m_bfmeBucketsABN);

			nx = 0;

			for (++b; b < cnt; ++b)
			{
				BfmeNodeABN *c = tb->m_bfmeBucketsABN[b];

				if (c != 0)
				{
					nx = c;
					break;
				}
			}
		}

		n = nx;
	}
}
