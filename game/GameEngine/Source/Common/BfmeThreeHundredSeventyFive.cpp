struct BfmeNodeYC
{
	BfmeNodeYC *m_bfmeNext;
	unsigned char m_bfmeGap[4];
	void *m_bfmeItem;
};

class BfmeThingYC
{
public:
	virtual void bfmeSpareYC0();
	virtual void bfmeSpareYC1();
	virtual void bfmeSpareYC2();
	virtual void bfmeSpareYC3();
	virtual void bfmeSpareYC4();
	virtual void bfmeSpareYC5();
	virtual void bfmeSpareYC6();
	virtual void bfmeSpareYC7();
	virtual void bfmeSpareYC8();
	virtual void bfmeSpareYC9();
	virtual void bfmeSpareYC10();
	virtual void bfmeSpareYC11();
	virtual void bfmeSpareYC12();
	virtual void bfmeSpareYC13();
	virtual void bfmeSpareYC14();
	virtual void bfmeSpareYC15();
	virtual void bfmeSpareYC16();
	virtual void bfmeSpareYC17();
	virtual void bfmeSpareYC18();
	virtual void bfmeSpareYC19();
	virtual void bfmeSpareYC20();
	virtual void bfmeSpareYC21();
	virtual void bfmeSpareYC22();
	virtual void bfmeSpareYC23();
	virtual void bfmeSpareYC24();
	virtual void bfmeSpareYC25();
	virtual void bfmeSpareYC26();
	virtual void bfmeSpareYC27();
	virtual void bfmeSpareYC28();
	virtual void bfmeSpareYC29();
	virtual void bfmeSpareYC30();
	virtual void bfmeSpareYC31();
	virtual void bfmeSpareYC32();
	virtual void bfmeSpareYC33();
	virtual void bfmeSpareYC34();
	virtual void bfmeSpareYC35();
	virtual void bfmeStepYC(void *item, void *what);
	void bfmeFinishYC(void *what);
	void bfmeGoYC(void *what);
	unsigned char m_bfmeHead[0x99c - 4];
	BfmeNodeYC *m_bfmeList;
};

void BfmeThingYC::bfmeGoYC(void *what)
{
	while (m_bfmeList->m_bfmeNext != m_bfmeList)
		bfmeStepYC(m_bfmeList->m_bfmeNext->m_bfmeItem, what);
	bfmeFinishYC(what);
}
