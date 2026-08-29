// Open-BFME5 conversions.

class BfmeItem1005
{
public:
	void bfmeDoC1005(int a);
	void bfmeDoD1005(int a);
};

struct BfmeNode1005
{
	BfmeNode1005 *m_bfmeNext;
	char m_bfmePad[4];
	BfmeItem1005 *m_bfmeItem;
};

class BfmeList1005
{
public:
	void bfmeGoC1005(int a);
	void bfmeGoD1005(int a);

	char m_bfmePad[4];
	BfmeNode1005 *m_bfmeHead;
};

void BfmeList1005::bfmeGoC1005(int a)
{
	for (BfmeNode1005 *n = m_bfmeHead->m_bfmeNext; n != m_bfmeHead; n = n->m_bfmeNext)
		n->m_bfmeItem->bfmeDoC1005(a);
}

void BfmeList1005::bfmeGoD1005(int a)
{
	for (BfmeNode1005 *n = m_bfmeHead->m_bfmeNext; n != m_bfmeHead; n = n->m_bfmeNext)
		n->m_bfmeItem->bfmeDoD1005(a);
}

class BfmeMgr1005
{
public:
	virtual void bfmeVM01005();
	virtual void bfmeVM11005();
	virtual void bfmeVM21005();
	virtual void bfmeVM31005();
	virtual void bfmeVM41005();
	virtual void bfmeVM51005();
	virtual void bfmeVM61005();
	virtual void bfmeVM71005();
	virtual void bfmeVM81005();
	virtual void bfmeVM91005();
	virtual void bfmeVM101005();
	virtual void bfmeVM111005();
	virtual void bfmeVM121005();
	virtual void bfmeSet1005(int u, int n);
};

struct BfmeGoal1005
{
	char m_bfmePad[0x74];
	int m_bfmeId;
	char m_bfmePad2[0x184];
	BfmeMgr1005 *m_bfmeMgr;
};

class BfmeHold1005
{
public:
	BfmeGoal1005 *bfmeGoalE1005();
	BfmeGoal1005 *bfmeGoalF1005();

	char m_bfmePad[0x10];
	int m_bfmeUnit;
};

class BfmeE1005
{
public:
	int bfmeGoE1005();
	int bfmeGoF1005();

	char m_bfmePad[0x1c];
	BfmeHold1005 *m_bfmeHold;
	char m_bfmePad2[4];
	int m_bfmeSlot;
};

int BfmeE1005::bfmeGoE1005()
{
	BfmeHold1005 *h = m_bfmeHold;

	m_bfmeSlot = 0;

	int u = h->m_bfmeUnit;
	BfmeGoal1005 *g = h->bfmeGoalE1005();

	if (g) {
		BfmeMgr1005 *m = g->m_bfmeMgr;

		if (m) {
			m->bfmeSet1005(u, 1);
			m_bfmeSlot = g->m_bfmeId;
		}

		return 0;
	}

	return -2;
}

int BfmeE1005::bfmeGoF1005()
{
	BfmeHold1005 *h = m_bfmeHold;

	m_bfmeSlot = 0;

	int u = h->m_bfmeUnit;
	BfmeGoal1005 *g = h->bfmeGoalF1005();

	if (g) {
		BfmeMgr1005 *m = g->m_bfmeMgr;

		if (m) {
			m->bfmeSet1005(u, 1);
			m_bfmeSlot = g->m_bfmeId;
		}

		return 0;
	}

	return -2;
}
