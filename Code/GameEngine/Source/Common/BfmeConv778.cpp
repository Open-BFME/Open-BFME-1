// cl: /O1
class BfmeSubDTA
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
	virtual bool bfmeRun8DTA();
	virtual void bfmeV9();
	virtual bool bfmeRun10DTA();
	virtual bool bfmeRun11DTA();
	virtual bool bfmeRun12DTA();
};

struct BfmeOwnerDTA
{
	unsigned char m_bfmeHead[0x1c];
	BfmeSubDTA *m_bfmeSub;
};

struct BfmeThingDTA
{
	bool bfmeGoDTA();
	bool bfmeGoDTB();
	bool bfmeGoDTC();
	bool bfmeGoDTD();
	unsigned char m_bfmeHead[0x30];
	BfmeOwnerDTA *m_bfmeOwner;
};

bool BfmeThingDTA::bfmeGoDTA()
{
	BfmeSubDTA *sub = m_bfmeOwner->m_bfmeSub;
	if (sub)
		return sub->bfmeRun12DTA();
	return true;
}

bool BfmeThingDTA::bfmeGoDTB()
{
	BfmeSubDTA *sub = m_bfmeOwner->m_bfmeSub;
	if (sub)
		return sub->bfmeRun8DTA();
	return true;
}

bool BfmeThingDTA::bfmeGoDTC()
{
	BfmeSubDTA *sub = m_bfmeOwner->m_bfmeSub;
	if (sub)
		return sub->bfmeRun10DTA();
	return true;
}

bool BfmeThingDTA::bfmeGoDTD()
{
	BfmeSubDTA *sub = m_bfmeOwner->m_bfmeSub;
	if (sub)
		return sub->bfmeRun11DTA();
	return true;
}
