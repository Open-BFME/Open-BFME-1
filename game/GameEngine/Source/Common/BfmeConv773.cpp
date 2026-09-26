extern "C" const float bfmeKDSM;

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
	virtual bool bfmeRun9DSK();
	virtual bool bfmeRunDSL();
	virtual float bfmeRunDSM();
	virtual float bfmeRunDSN();
};

class BfmeThingDSK
{
public:
	bool bfmeGoDSK();
	void bfmeGoDSP();
	bool bfmeGoDSL();
	float bfmeGoDSM();
	float bfmeGoDSN();
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

float BfmeThingDSK::bfmeGoDSM()
{
	if (bfmeAskDSK())
		return m_bfmeSub->bfmeRunDSM();
	return bfmeKDSM;
}

float BfmeThingDSK::bfmeGoDSN()
{
	if (bfmeAskDSK())
		return m_bfmeSub->bfmeRunDSN();
	return bfmeKDSM;
}

void BfmeThingDSK::bfmeGoDSP()
{
	if (bfmeAskDSK())
		m_bfmeSub->bfmeRun9DSK();
}
