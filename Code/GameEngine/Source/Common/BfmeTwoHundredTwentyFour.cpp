// A twice-emitted newcomer errand, both copies converted here under their own
// names. A newcomer already known is left alone; otherwise it is marked, asked
// whether it wants the held piece, given one made to order when there is none
// yet, handed it, and finally told where the rest of the record sits.

struct BfmePairKU
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};

class BfmeItemKU
{
public:
	virtual void bfmeSpare000KU(void) = 0;
	virtual void bfmeSpare001KU(void) = 0;
	virtual void bfmeSpare002KU(void) = 0;
	virtual void bfmeSpare003KU(void) = 0;
	virtual unsigned char bfmeIsKU(void) = 0;
	virtual void bfmeSpare005KU(void) = 0;
	virtual void bfmeSpare006KU(void) = 0;
	virtual void bfmeSpare007KU(void) = 0;
	virtual void bfmeSpare008KU(void) = 0;
	virtual void bfmeSpare009KU(void) = 0;
	virtual void bfmeMarkKU(BfmePairKU *both) = 0;
	virtual void bfmeSpare011KU(void) = 0;
	virtual void bfmeHandKU(void *what) = 0;
	virtual void bfmeSpare013KU(void) = 0;
	virtual void bfmeSpare014KU(void) = 0;
	virtual void bfmeSpare015KU(void) = 0;
	virtual void bfmeSpare016KU(void) = 0;
	virtual void bfmeSpare017KU(void) = 0;
	virtual void bfmeSpare018KU(void) = 0;
	virtual void bfmeSpare019KU(void) = 0;
	virtual void bfmeSpare020KU(void) = 0;
	virtual void bfmeSpare021KU(void) = 0;
	virtual void bfmeSpare022KU(void) = 0;
	virtual void bfmeSpare023KU(void) = 0;
	virtual void bfmeSpare024KU(void) = 0;
	virtual void bfmeSpare025KU(void) = 0;
	virtual void bfmeSpare026KU(void) = 0;
	virtual void bfmeSpare027KU(void) = 0;
	virtual void bfmeSpare028KU(void) = 0;
	virtual void bfmeWhereKU(void *rest) = 0;
	virtual void bfmeSpare030KU(void) = 0;
	virtual void bfmeSpare031KU(void) = 0;
	virtual void bfmeSpare032KU(void) = 0;
	virtual void bfmeSpare033KU(void) = 0;
	virtual void bfmeSpare034KU(void) = 0;
	virtual void bfmeWantKU(unsigned char *yes) = 0;
};

class BfmeMakerKU
{
public:
	virtual void bfmeSpare000KU(void) = 0;
	virtual void bfmeSpare001KU(void) = 0;
	virtual void bfmeSpare002KU(void) = 0;
	virtual void bfmeSpare003KU(void) = 0;
	virtual void bfmeSpare004KU(void) = 0;
	virtual void bfmeSpare005KU(void) = 0;
	virtual void bfmeSpare006KU(void) = 0;
	virtual void bfmeSpare007KU(void) = 0;
	virtual void bfmeSpare008KU(void) = 0;
	virtual void *bfmeMakeKU(void) = 0;
};

class BfmeThingKU
{
public:
	void bfmeTakeKU(BfmeItemKU *item);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeMakerKU *m_bfmeMaker;		// 0x1c
	unsigned char m_bfmeGap[4];		// 0x20
	void *m_bfmeHeld;			// 0x24
	unsigned char m_bfmeRest[4];		// 0x28
};

void BfmeThingKU::bfmeTakeKU(BfmeItemKU *item)
{
	if (item->bfmeIsKU() != 0)
		return;

	BfmePairKU both;

	both.m_bfmeFirst = 1;
	both.m_bfmeSecond = 1;

	item->bfmeMarkKU(&both);

	unsigned char yes = (unsigned char)(m_bfmeHeld != 0);

	item->bfmeWantKU(&yes);

	if (yes != 0)
	{
		if (m_bfmeHeld == 0)
			m_bfmeHeld = m_bfmeMaker->bfmeMakeKU();

		if (yes != 0)
			item->bfmeHandKU(m_bfmeHeld);
	}

	item->bfmeWhereKU(m_bfmeRest);
}


class BfmeThingKX
{
public:
	void bfmeTakeKX(BfmeItemKU *item);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeMakerKU *m_bfmeMaker;		// 0x1c
	unsigned char m_bfmeGap[4];		// 0x20
	void *m_bfmeHeld;			// 0x24
	unsigned char m_bfmeRest[4];		// 0x28
};

void BfmeThingKX::bfmeTakeKX(BfmeItemKU *item)
{
	if (item->bfmeIsKU() != 0)
		return;

	BfmePairKU both;

	both.m_bfmeFirst = 1;
	both.m_bfmeSecond = 1;

	item->bfmeMarkKU(&both);

	unsigned char yes = (unsigned char)(m_bfmeHeld != 0);

	item->bfmeWantKU(&yes);

	if (yes != 0)
	{
		if (m_bfmeHeld == 0)
			m_bfmeHeld = m_bfmeMaker->bfmeMakeKU();

		if (yes != 0)
			item->bfmeHandKU(m_bfmeHeld);
	}

	item->bfmeWhereKU(m_bfmeRest);
}

