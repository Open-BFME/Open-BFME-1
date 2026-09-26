struct BfmeVecYB
{
	int m_bfmeAYB;
	int m_bfmeBYB;
	int m_bfmeCYB;
};

class BfmeClientYB
{
public:
	virtual void bfmeC00YB();
	virtual void bfmeC01YB();
	virtual void bfmeC02YB();
	virtual void bfmeC03YB();
	virtual void bfmeC04YB();
	virtual void bfmeC05YB();
	virtual void bfmeC06YB();
	virtual void bfmeC07YB();
	virtual void bfmeC08YB();
	virtual void bfmeC09YB();
	virtual void bfmeC10YB();
	virtual void bfmeC11YB();
	virtual void bfmeC12YB();
	virtual void bfmeC13YB();
	virtual void bfmeC14YB();
	virtual void bfmeC15YB();
	virtual void bfmeC16YB();
	virtual void bfmeC17YB();
	virtual void bfmeC18YB();
	virtual void bfmeC19YB();
	virtual void bfmeC20YB();
	virtual void bfmeC21YB();
	virtual void bfmeC22YB();
	virtual void bfmeC23YB();
	virtual void bfmeC24YB();
	virtual void bfmeC25YB();
	virtual int bfmeNowYB();
};

extern BfmeClientYB *TheBfmeClientYB;

class BfmeOwnerYB
{
public:
	void bfmeSetYB(int a1, int a2, int a3, void *a4);

	unsigned char m_bfmeHeadYB[0x278];
	int m_bfmeFlagYB;
	int m_bfmeTimeYB;
	void *m_bfmeExtraYB;
	BfmeVecYB m_bfmeFirstYB;
	BfmeVecYB m_bfmeSecondYB;
};

void BfmeOwnerYB::bfmeSetYB(int a1, int a2, int a3, void *a4)
{
	m_bfmeSecondYB.m_bfmeAYB = a1;
	m_bfmeSecondYB.m_bfmeCYB = a3;
	m_bfmeSecondYB.m_bfmeBYB = a2;

	m_bfmeFirstYB.m_bfmeAYB = a1;
	m_bfmeFirstYB.m_bfmeCYB = a3;
	m_bfmeFirstYB.m_bfmeBYB = a2;

	m_bfmeTimeYB = TheBfmeClientYB->bfmeNowYB();
	m_bfmeFlagYB = 1;
	m_bfmeExtraYB = a4;
}
