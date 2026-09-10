class ClientRoot4120
{
public:
	unsigned char m_bfmePad[0xb4];
	int m_bfmeValue;
};

extern ClientRoot4120 *TheGameClient;

class GlobalData
{
public:
	unsigned char m_bfmePad[0xa75];
	unsigned char m_bfmeEnabled;
};

extern GlobalData *TheWritableGlobalData;

class BfmeX1004
{
public:
	virtual void bfmeVX01004();
	virtual void bfmeVX11004();
	virtual void bfmeVX21004();
	virtual void bfmeVX31004();
	virtual void bfmeVX41004();
	virtual void bfmeVX51004();
	virtual void bfmeVX61004();
	virtual void bfmeVX71004();
	virtual void bfmeVX81004();
	virtual void bfmeVX91004();
	virtual void bfmeVX101004();
	virtual void bfmeVX111004();
	virtual void bfmeVX121004();
	virtual void bfmeVX131004();
	virtual void bfmeVX141004();
	virtual void bfmeVX151004();
	virtual void bfmeVX161004();
	virtual void bfmeVX171004();
	virtual void bfmeVX181004();
	virtual void bfmeVX191004();
	virtual void bfmeVX201004();
	virtual void bfmeVX211004();
	virtual void bfmeVX221004();
	virtual void bfmeVX231004();
	virtual void bfmeVX241004();
	virtual void bfmeVX251004();
	virtual void bfmeVX261004();
	virtual void bfmeVX271004();
	virtual void bfmeVX281004();
	virtual void bfmeVX291004();
	virtual void bfmeVX301004();
	virtual void bfmeVX311004();
	virtual void bfmeVX321004();
	virtual void bfmeVX331004();
	virtual void bfmeVX341004();
	virtual void bfmeVX351004();
	virtual void bfmeVX361004();
	virtual void bfmeVX371004();
	virtual void bfmeVX381004();
	virtual void bfmeVX391004();
	virtual void bfmeVX401004();
	virtual void bfmeVX411004();
	virtual void bfmeVX421004();
	virtual void bfmeVX431004();
	virtual void bfmeVX441004();
	virtual void bfmeVX451004();
	virtual void bfmeVX461004();
	virtual void bfmeVX471004();
	virtual void bfmeVX481004();
	virtual void bfmeVX491004();
	virtual void bfmeVX501004();
	virtual void bfmeVX511004();
	virtual void bfmeTail1004();
};

class BfmePreBXF;

class BfmeHold1004
{
public:
	BfmeX1004 *bfmeFind1004();
	unsigned char m_bfmePad[0x1fc];
	BfmePreBXF *m_bfmePre;
};

class BfmeTargetJB
{
public:
	bool bfmeTailJB();
};

class BfmeSubBIC
{
public:
	int bfmeAskBIC();
};

class BfmePreBXF
{
public:
	virtual void bfmeVX00();
	virtual void bfmeVX04();
	virtual void bfmeVX08();
	virtual void bfmeVX0c();
	virtual void bfmeVX10();
	virtual void bfmeVX14();
	virtual void bfmeVX18();
	virtual void bfmeVX1c();
	virtual void bfmeVX20();
	virtual void bfmeVX24();
	virtual void bfmeVX28();
	virtual void bfmeNotify();
};

class BfmeModuleBXF
{
public:
	virtual void bfmeVX00();
	virtual void bfmeVX04();
	virtual void bfmeVX08();
	virtual void bfmeVX0c();
	virtual void bfmeVX10();
	virtual void bfmeVX14();
	virtual void bfmeVX18();
	virtual void bfmeVX1c();
	virtual void bfmeVX20();
	virtual void bfmeVX24();
	virtual void bfmeVX28();
	virtual void bfmeVX2c();
	virtual void bfmeVX30();
	virtual void bfmeVX34();
	virtual void bfmeVX38();
	virtual void bfmeVX3c();
	virtual void bfmeVX40();
	virtual void bfmeVX44();
	virtual void bfmeVX48();
	virtual void bfmeVX4c();
	virtual void bfmeVX50();
	virtual void bfmeVX54();
	virtual void bfmeVX58();
	virtual void bfmeVX5c();
	virtual void bfmeNotify(int, int);
};

class BfmeThingBXF
{
public:
	void bfmeOnceBXF();
	void bfmeThenBXF(int value);
	void bfmeGoBXF();
	unsigned char m_bfmeHead[0xfc];
	BfmeHold1004 *m_bfmeHold;
	unsigned char m_bfmePad100[0x50];
	BfmeModuleBXF **m_bfmeModules;
	unsigned char m_bfmePad154[0x258];
	bool m_bfmeFlag;
};

void BfmeThingBXF::bfmeOnceBXF()
{
	BfmeHold1004 *hold = m_bfmeHold;
	if (!hold)
		return;

	TheGameClient->m_bfmeValue = *(int *)((char *)hold + 0x74);

	BfmePreBXF *pre = hold->m_bfmePre;
	if (pre)
		pre->bfmeNotify();

	if (!TheWritableGlobalData->m_bfmeEnabled)
		return;

	BfmeX1004 *x = hold->bfmeFind1004();
	if (x)
		return x->bfmeTail1004();

	if (!((BfmeTargetJB *)hold)->bfmeTailJB())
		return;

	int value = ((BfmeSubBIC *)hold)->bfmeAskBIC();

	BfmeModuleBXF *module = m_bfmeModules[0];
	if (module)
		module->bfmeNotify(1, value);
}

void BfmeThingBXF::bfmeGoBXF()
{
	if (!m_bfmeFlag)
	{
		m_bfmeFlag = true;
		bfmeOnceBXF();
	}
	bfmeThenBXF(0);
}
