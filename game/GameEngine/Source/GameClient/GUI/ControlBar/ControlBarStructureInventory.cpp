struct Rva002EE330PlayerList
{
	unsigned char m_bfmeHeadZA[0xc];
	void *m_bfme0CZA;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class BfmeCZA
{
public:
	virtual void bfmeV00ZA();
	virtual void bfmeV04ZA();
	virtual void bfmeV08ZA();
	virtual void bfmeV0CZA();
	virtual void bfmeV10ZA();
	virtual void bfmeV14ZA();
	virtual void bfmeV18ZA();
	virtual void bfmeV1CZA();
	virtual void bfmeV20ZA();
	virtual void bfmeV24ZA();
	virtual void bfmeV28ZA();
	virtual void bfmeV2CZA();
	virtual void bfmeV30ZA();
	virtual void bfmeV34ZA();
	virtual void bfmeV38ZA();
	virtual void bfmeV3CZA();
	virtual void bfmeV40ZA();
	virtual void bfmeV44ZA();
	virtual void bfmeV48ZA();
	virtual void bfmeV4CZA();
	virtual void bfmeV50ZA();
	virtual void bfmeV54ZA();
	virtual void bfmeV58ZA();
	virtual void bfmeV5CZA();
	virtual void bfmeV60ZA();
	virtual void bfmeV64ZA();
	virtual void bfmeV68ZA();
	virtual void bfmeV6CZA();
	virtual void bfmeV70ZA();
	virtual void bfmeV74ZA();
	virtual void bfmeV78ZA();
	virtual void bfmeV7CZA();
	virtual void bfmeV80ZA();
	virtual void bfmeV84ZA();
	virtual void bfmeV88ZA();
	virtual void bfmeV8CZA();
	virtual void bfmeV90ZA();
	virtual void bfmeV94ZA();
	virtual void bfmeV98ZA();
	virtual void bfmeV9CZA();
	virtual void bfmeVA0ZA();
	virtual void bfmeVA4ZA();
	virtual void bfmeVA8ZA();
	virtual void bfmeVACZA();
	virtual void bfmeVB0ZA();
	virtual void bfmeVB4ZA();
	virtual void bfmeVB8ZA();
	virtual void bfmeVBCZA();
	virtual void bfmeVC0ZA();
	virtual char bfmeCheckZA();
	virtual void bfmeVC8ZA();
	virtual void *bfmeOwnerZA();
	virtual void bfmeVD0ZA();
	virtual void bfmeVD4ZA();
	virtual void bfmeVD8ZA();
	virtual void bfmeVDCZA();
	virtual void bfmeVE0ZA();
	virtual void bfmeVE4ZA();
	virtual void bfmeVE8ZA();
	virtual void bfmeVECZA();
	virtual void bfmeVF0ZA();
	virtual void bfmeVF4ZA();
	virtual void bfmeVF8ZA();
	virtual void bfmeVFCZA();
	virtual void bfmeV100ZA();
	virtual void bfmeV104ZA();
	virtual void bfmeV108ZA();
	virtual void bfmeV10CZA();
	virtual void bfmeV110ZA();
	virtual void bfmeV114ZA();
	virtual int bfmeIdZA();
};

class BfmeBZA
{
public:
	unsigned char m_bfmeHeadZA[0x1fc];
	BfmeCZA *m_bfme1FCZA;
};

class BfmeAZA
{
public:
	unsigned char m_bfmeHeadZA[0xfc];
	BfmeBZA *m_bfmeFCZA;
};

class BfmeHostZA
{
public:
	void bfmeTickZA();
	void bfmeFallbackZA(BfmeCZA *c, BfmeAZA *a);
	void bfmeApplyZA(BfmeBZA *b, int flag);
	void bfmeOtherZA();

	unsigned char m_bfmeHeadZA[0x5c];
	BfmeAZA *m_bfme5CZA;
	unsigned char m_bfmeMidZA[0x70 - 0x60];
	int m_bfme70ZA;
};

void BfmeHostZA::bfmeTickZA()
{
	BfmeAZA *a = m_bfme5CZA;
	BfmeBZA *b = a->m_bfmeFCZA;
	BfmeCZA *c = b->m_bfme1FCZA;

	if (c == 0)
	{
		bfmeFallbackZA(c, a);
		return;
	}

	void *p = Rva002EE330ThePlayers->m_bfme0CZA;

	if (c->bfmeCheckZA() && c->bfmeOwnerZA() == p)
	{
		if (m_bfme70ZA != c->bfmeIdZA())
			bfmeApplyZA(b, 1);

		return;
	}

	bfmeOtherZA();
}
