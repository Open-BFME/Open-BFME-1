class BfmeBBP;
class BfmeUBP;
class BfmeItemBP;

class BfmeUBP
{
public:
	virtual void bfmeSlot00U();
	virtual void bfmeSlot01U();
	virtual void bfmeSlot02U();
	virtual void bfmeSlot03U();
	virtual void bfmeSlot04U();
	virtual void bfmeSlot05U();
	virtual void bfmeSlot06U();
	virtual void bfmeSlot07U();
	virtual void bfmeSlot08U();
	virtual void bfmeSlot09U();
	virtual void bfmeSlot10U();
	virtual void bfmeSlot11U();
	virtual void bfmeSlot12U();
	virtual void bfmeSlot13U();
	virtual void bfmeSlot14U();
	virtual void bfmeSlot15U();
	virtual void bfmeSlot16U();
	virtual void bfmeSlot17U();
	virtual int bfmeCheckBP();
};

class BfmeItemBP
{
public:
	virtual void bfmeSlot00I();
	virtual void bfmeSlot01I();
	virtual void bfmeSlot02I();
	virtual void bfmeSlot03I();
	virtual void bfmeSlot04I();
	virtual void bfmeSlot05I();
	virtual void bfmeSlot06I();
	virtual void bfmeSlot07I();
	virtual void bfmeSlot08I();
	virtual void bfmeSlot09I();
	virtual void bfmeSlot10I();
	virtual void bfmeSlot11I();
	virtual void bfmeSlot12I();
	virtual void bfmeSlot13I();
	virtual void bfmeSlot14I();
	virtual void bfmeSlot15I();
	virtual void bfmeSlot16I();
	virtual void bfmeSlot17I();
	virtual void bfmeSlot18I();
	virtual void bfmeSlot19I();
	virtual void bfmeSlot20I();
	virtual void bfmeSlot21I();
	virtual void bfmeSlot22I();
	virtual void bfmeSlot23I();
	virtual void bfmeSlot24I();
	virtual void bfmeSlot25I();
	virtual void bfmeSlot26I();
	virtual void bfmeSlot27I();
	virtual void bfmeSlot28I();
	virtual void bfmeSlot29I();
	virtual void bfmeSlot30I();
	virtual void bfmeSlot31I();
	virtual void bfmeSlot32I();
	virtual void bfmeSlot33I();
	virtual void bfmeSlot34I();
	virtual void bfmeSlot35I();
	virtual void bfmeSlot36I();
	virtual void bfmeSlot37I();
	virtual void bfmeSlot38I();
	virtual void bfmeSlot39I();
	virtual void bfmeSlot40I();
	virtual void bfmeSlot41I();
	virtual void bfmeSlot42I();
	virtual void bfmeSlot43I();
	virtual void bfmeSlot44I();
	virtual void bfmeSlot45I();
	virtual BfmeUBP *bfmeGetBP();
};

class BfmeBBP
{
public:
	void bfmeSetBP(int mode);
	BfmeItemBP **bfmeListBP();
};

class BfmeABP
{
public:
	virtual void bfmeSlot00A();
	virtual void bfmeSlot01A();
	virtual void bfmeSlot02A();
	virtual void bfmeSlot03A();
	virtual void bfmeSlot04A();
	virtual void bfmeSlot05A();
	virtual void bfmeSlot06A();
	virtual void bfmeSlot07A();
	virtual void bfmeSlot08A();
	virtual void bfmeSlot09A();
	virtual BfmeBBP *bfmeMakeBP();
};

class BfmeGlobPB
{
public:
	virtual void bfmeSlot00G();
	virtual void bfmeSlot01G();
	virtual void bfmeDropBP(BfmeUBP *u);
};

extern BfmeGlobPB *g_bfmeGlobPB;

class BfmeHostBP
{
public:
	void bfmeSweepBP();

	unsigned char m_bfmeHeadBP[0xc];
	BfmeABP *m_bfmeABP;
};

void BfmeHostBP::bfmeSweepBP()
{
	BfmeBBP *b = m_bfmeABP->bfmeMakeBP();

	if (b == 0)
		return;

	b->bfmeSetBP(0);

	for (BfmeItemBP **p = b->bfmeListBP(); *p != 0; p++)
	{
		BfmeUBP *u = (*p)->bfmeGetBP();

		if (u != 0 && u->bfmeCheckBP() == 0)
			g_bfmeGlobPB->bfmeDropBP(u);
	}
}
