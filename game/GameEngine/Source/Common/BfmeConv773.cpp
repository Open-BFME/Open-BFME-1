extern const float g_rva01075350;
void j_0002d538(void);

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
	char m_bfmeHead[0x4c];
	BfmeSubDSK *m_bfmeSub;
};

typedef bool (__fastcall *BfmeThingDSKAskCall)(BfmeThingDSK *);

bool BfmeThingDSK::bfmeGoDSK()
{
	if (reinterpret_cast<BfmeThingDSKAskCall>(&::j_0002d538)(this))
		return m_bfmeSub->bfmeRunDSK();
	return false;
}

bool BfmeThingDSK::bfmeGoDSL()
{
	if (reinterpret_cast<BfmeThingDSKAskCall>(&::j_0002d538)(this))
		return m_bfmeSub->bfmeRunDSL();
	return false;
}

float BfmeThingDSK::bfmeGoDSM()
{
	if (reinterpret_cast<BfmeThingDSKAskCall>(&::j_0002d538)(this))
		return m_bfmeSub->bfmeRunDSM();
	return g_rva01075350;
}

float BfmeThingDSK::bfmeGoDSN()
{
	if (reinterpret_cast<BfmeThingDSKAskCall>(&::j_0002d538)(this))
		return m_bfmeSub->bfmeRunDSN();
	return g_rva01075350;
}

void BfmeThingDSK::bfmeGoDSP()
{
	if (reinterpret_cast<BfmeThingDSKAskCall>(&::j_0002d538)(this))
		m_bfmeSub->bfmeRun9DSK();
}
