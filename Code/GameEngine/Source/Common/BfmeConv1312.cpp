// Open-BFME5 conversions.

class BfmeSubTFA
{
public:
	void bfmeSetTFA(int a);
};

class BfmeBaseTFA
{
public:
	void bfmeInitTFA();
};

class BfmeThingTFA
{
public:
	void bfmeGoTFA();
};

void BfmeThingTFA::bfmeGoTFA()
{
	((BfmeBaseTFA *)((char *)this - 0x10))->bfmeInitTFA();
	(*(BfmeSubTFA **)((char *)this - 8))->bfmeSetTFA(3);
}

class BfmeThingTFB
{
public:
	void bfmeGoTFB(int a);
	void bfmeOneTFB();
	void bfmeTwoTFB(int a, int b);
};

void BfmeThingTFB::bfmeGoTFB(int a)
{
	bfmeOneTFB();
	bfmeTwoTFB(a, 0);
}

class BfmeSinkTFC
{
public:
	void bfmeUseTFC(void *a, void *b);
};

class BfmeThingTFC
{
public:
	virtual void bfmeV0TFC() = 0;
	virtual void bfmeV1TFC() = 0;
	virtual void bfmeV2TFC() = 0;
	virtual void bfmeV3TFC() = 0;
	virtual void bfmeV4TFC() = 0;
	virtual void bfmeV5TFC() = 0;
	virtual void bfmeV6TFC() = 0;
	virtual void bfmeV7TFC() = 0;
	virtual void bfmeV8TFC() = 0;
	virtual void bfmeV9TFC() = 0;
	virtual void bfmeV10TFC() = 0;
	virtual void bfmeV11TFC() = 0;
	virtual void bfmeV12TFC() = 0;
	virtual void bfmeV13TFC() = 0;
	virtual void bfmeV14TFC() = 0;
	virtual void bfmeV15TFC() = 0;
	virtual void bfmeV16TFC() = 0;
	virtual void bfmeV17TFC() = 0;
	virtual void bfmeV18TFC() = 0;
	virtual void bfmeV19TFC() = 0;
	virtual void bfmeStartTFC() = 0;
	void bfmeGoTFC();
	BfmeSinkTFC *m_bfmeSink;
	void *m_bfmeFirst;
	void *m_bfmeSecond;
};

void BfmeThingTFC::bfmeGoTFC()
{
	bfmeStartTFC();
	m_bfmeSink->bfmeUseTFC(m_bfmeSecond, m_bfmeFirst);
}

class BfmeHolderTFD
{
public:
	void bfmeMakeTFD(void *p);
	void bfmeRunTFD();
	void *m_bfmeHeld;
};

class BfmeThingTFD
{
public:
	void bfmeGoTFD();
	char m_bfmePad[0xa0];
	int m_bfmeField;
};

void BfmeThingTFD::bfmeGoTFD()
{
	BfmeHolderTFD h;
	h.bfmeMakeTFD(&m_bfmeField);
	h.bfmeRunTFD();
}
