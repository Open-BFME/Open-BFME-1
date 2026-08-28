class BfmeSubDSK
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual bool bfmeRunDSK();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual bool bfmeRunDSL();
};

class BfmeThingDSK
{
public:
	bool bfmeGoDSK();
	bool bfmeGoDSL();
	bool bfmeAskDSK();
	char m_bfmeHead[0x4c];
	BfmeSubDSK *m_bfmeSub;
};

bool BfmeThingDSK::bfmeGoDSK()
{
	if (bfmeAskDSK())
		return m_bfmeSub->bfmeRunDSK();
	return false;
}

bool BfmeThingDSK::bfmeGoDSL()
{
	if (bfmeAskDSK())
		return m_bfmeSub->bfmeRunDSL();
	return false;
}
