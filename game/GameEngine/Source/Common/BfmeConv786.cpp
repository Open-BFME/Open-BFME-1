class BfmeSubDVA
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual bool bfmeAskDVA();
};

struct BfmeThingDVA
{
	bool bfmeGoDVA();
	unsigned char m_bfmeHead[0x1c];
	BfmeSubDVA *m_bfmeSub;
};

bool BfmeThingDVA::bfmeGoDVA()
{
	if (m_bfmeSub && m_bfmeSub->bfmeAskDVA())
		return true;
	return false;
}
