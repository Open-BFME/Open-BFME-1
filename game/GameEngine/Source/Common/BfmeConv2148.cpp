class BfmeItemZB
{
public:
	unsigned char m_bfmeHeadZB[4];
	int m_bfme04ZB;
};

class BfmeNodeZB
{
public:
	virtual void bfmeCloseZB(int flag);

	int m_bfme04ZB;
	unsigned char m_bfmeMidZB[4];
	BfmeItemZB *m_bfme0CZB;
	unsigned char m_bfmeMid2ZB[0x28 - 0x10];
	unsigned int m_bfme28ZB;
	unsigned char m_bfmeMid3ZB[0x3c - 0x2c];
	BfmeNodeZB *m_bfme3CZB;
};

class Money
{
public:
	void deposit(unsigned int amount, bool flag);
};

class BfmePlayerZB
{
public:
	bool bfmeCanZB(BfmeItemZB *item);
	void bfmeFinishZB(BfmeItemZB *item);

	unsigned char m_bfmeHeadZB[0x48];
	Money m_bfmeMoneyZB;
};

class BfmeOwnerZB
{
public:
	BfmePlayerZB *bfmeGetPlayerZB();
};

class BfmeSinkZB
{
public:
	void bfmeNotifyZB(BfmeNodeZB *n);
};

class BfmeHostZB
{
public:
	void bfmeGiveZB(BfmeItemZB *item);

	unsigned char m_bfmeHeadZB[8];
	BfmeNodeZB *m_bfme08ZB;
};

void BfmeHostZB::bfmeGiveZB(BfmeItemZB *item)
{
	if (item == 0)
		return;

	BfmePlayerZB *pl = (*(BfmeOwnerZB **)((char *)this - 0x18))->bfmeGetPlayerZB();

	if (item->m_bfme04ZB == 0)
	{
		if (!pl->bfmeCanZB(item))
			return;
	}

	BfmeNodeZB *n = m_bfme08ZB;

	while (n != 0)
	{
		if (n->m_bfme04ZB == 2 && n->m_bfme0CZB == item)
		{
			pl->m_bfmeMoneyZB.deposit(n->m_bfme28ZB, 1);
			((BfmeSinkZB *)((char *)this - 0x20))->bfmeNotifyZB(n);
			n->bfmeCloseZB(1);

			if (item->m_bfme04ZB == 0)
				pl->bfmeFinishZB(item);

			return;
		}

		n = n->m_bfme3CZB;
	}
}
