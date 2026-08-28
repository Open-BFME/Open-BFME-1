struct BfmeNodeAGA
{
	BfmeNodeAGA *m_bfmeNext;
	unsigned char m_bfmeGap[4];
	void *m_bfmeItem;
};

class BfmeThingAGA
{
public:
	virtual void bfmeSpareAGA0();
	virtual void bfmeSpareAGA1();
	virtual void bfmeSpareAGA2();
	virtual void bfmeSpareAGA3();
	virtual void bfmeSpareAGA4();
	virtual void bfmeSpareAGA5();
	virtual void bfmeSpareAGA6();
	virtual void bfmeSpareAGA7();
	virtual void bfmeSpareAGA8();
	virtual void bfmeSpareAGA9();
	virtual void bfmeSpareAGA10();
	virtual void bfmeSpareAGA11();
	virtual void bfmeSpareAGA12();
	virtual void bfmeSpareAGA13();
	virtual void bfmeSpareAGA14();
	virtual void bfmeSpareAGA15();
	virtual void bfmeSpareAGA16();
	virtual void bfmeSpareAGA17();
	virtual void bfmeSpareAGA18();
	virtual void bfmeSpareAGA19();
	virtual void bfmeSpareAGA20();
	virtual void bfmeSpareAGA21();
	virtual void bfmeSpareAGA22();
	virtual void bfmeSpareAGA23();
	virtual void bfmeSpareAGA24();
	virtual void bfmeSpareAGA25();
	virtual void bfmeSpareAGA26();
	virtual void bfmeSpareAGA27();
	virtual void bfmeSpareAGA28();
	virtual void bfmeSpareAGA29();
	virtual void bfmeSpareAGA30();
	virtual void bfmeSpareAGA31();
	virtual void bfmeSpareAGA32();
	virtual void bfmeSpareAGA33();
	virtual void bfmeSpareAGA34();
	virtual void bfmeSpareAGA35();
	virtual void bfmeStepAGA(void *item, void *what);
	void bfmeFinishAGA(void *what);
	void bfmeGoAGA(void *what);
	unsigned char m_bfmeHead[0xc4 - 4];
	BfmeNodeAGA *m_bfmeList;
};

void BfmeThingAGA::bfmeGoAGA(void *what)
{
	while (m_bfmeList->m_bfmeNext != m_bfmeList)
	{
		void *item = m_bfmeList->m_bfmeNext->m_bfmeItem;
		if (item != 0)
			bfmeStepAGA(item, what);
	}
	bfmeFinishAGA(what);
}
