extern "C" unsigned char bfmeVftUC[];

class BfmeThingUC;
class BfmeNodeUC;

class BfmeSubUC
{
public:
	virtual void bfmeSpareUC0();
	virtual void bfmeSpareUC1();
	virtual void bfmeSpareUC2();
	virtual void bfmeSpareUC3();
	virtual void bfmeSpareUC4();
	virtual void bfmeSpareUC5();
	virtual void bfmeSpareUC6();
	virtual void bfmeSpareUC7();
	virtual void bfmeSpareUC8();
	virtual void bfmeSpareUC9();
	virtual void bfmeSpareUCA();
	virtual void bfmeSpareUCB();
	virtual void bfmeSpareUCC();
	virtual BfmeNodeUC *bfmeHeadUC();
	void bfmeDropUC(BfmeThingUC *who);
};

class BfmeThingUC
{
public:
	void bfmeResetUC();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	BfmeSubUC *m_bfmeSub;
};

class BfmeNodeUC
{
public:
	virtual void bfmeSpareNodeUC();
	virtual BfmeNodeUC *bfmeNextUC();
	BfmeNodeUC *m_bfmeNext;
};

extern BfmeNodeUC *g_bfmeThingUCHead; // 0x0130B198

void BfmeThingUC::bfmeResetUC()
{
	BfmeSubUC *sub = m_bfmeSub;
	m_bfmeVft = bfmeVftUC;
	if (sub != 0)
		sub->bfmeDropUC(this);
}

void BfmeSubUC::bfmeDropUC(BfmeThingUC *who)
{
	BfmeNodeUC *previous = 0;
	BfmeNodeUC *at = bfmeHeadUC();
	while (at != 0)
	{
		if ((BfmeThingUC *)at == who)
		{
			if (at != 0)
			{
				if (previous != 0)
					previous->m_bfmeNext = at->m_bfmeNext;
				else
					g_bfmeThingUCHead = at->m_bfmeNext;
			}
			break;
		}
		previous = at;
		at = at->bfmeNextUC();
	}
}
