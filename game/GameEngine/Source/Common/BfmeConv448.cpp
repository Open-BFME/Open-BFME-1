class BfmeGotBEC
{
public:
	virtual void bfmeSpareBEC0();
	virtual void bfmeSpareBEC1();
	virtual void bfmeSpareBEC2();
	virtual void bfmeSpareBEC3();
	virtual void bfmeSpareBEC4();
	virtual void bfmeSpareBEC5();
	virtual void bfmeSpareBEC6();
	virtual void bfmeSpareBEC7();
	virtual void bfmeSpareBEC8();
	virtual void bfmeSpareBEC9();
	virtual void bfmeSpareBECA();
	virtual void bfmeSpareBECB();
	virtual void bfmeSpareBECC();
	virtual void bfmeSpareBECD();
	virtual void bfmeSpareBECE();
	virtual void bfmeSpareBECF();
	virtual void bfmeSpareBECG();
	virtual void bfmeSendBEC(int what);
};

extern void j_0000f498(void);

class BfmeSubBEC
{
};

class BfmeThingBEC
{
public:
	void bfmeGoBEC();
	unsigned char m_bfmeHead[8];
	BfmeSubBEC *m_bfmeSub;
};

void BfmeThingBEC::bfmeGoBEC()
{
	((BfmeGotBEC *(__fastcall *)(BfmeSubBEC *))j_0000f498)(m_bfmeSub)->bfmeSendBEC(1);
}
