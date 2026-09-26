// Open-BFME5 conversions.

class BfmeTickC976
{
public:
	virtual void bfmeV0976();
	virtual void bfmeV1976();
	virtual void bfmeV2976();
	virtual void bfmeV3976();
	virtual void bfmeV4976();
	virtual void bfmeTick976C();
};

struct BfmeProbe976;

struct BfmeProbeTab976
{
	char m_bfmePad[0xc];
	int (__stdcall *m_bfmeAsk)(BfmeProbe976 *p);
};

struct BfmeProbe976
{
	BfmeProbeTab976 *m_bfmeTab;
};

class BfmeEndC976
{
public:
	virtual void bfmeV0976();
	virtual void bfmeV1976();
	virtual void bfmeV2976();
	virtual void bfmeV3976();
	virtual void bfmeV4976();
	virtual void bfmeEnd976C();
};

extern BfmeTickC976 *g_bfmeTickC976;
extern BfmeProbe976 *g_bfmeProbe976;
extern BfmeEndC976 *g_bfmeEndC976;

void bfmeGo976C(void)
{
	g_bfmeTickC976->bfmeTick976C();

	BfmeProbe976 *p = g_bfmeProbe976;

	if (p && !p->m_bfmeTab->m_bfmeAsk(p))
		g_bfmeEndC976->bfmeEnd976C();
}

class BfmeDev976
{
public:
	virtual void bfmeV0976();
	virtual void bfmeV1976();
	virtual void bfmeV2976();
	virtual void bfmeV3976();
	virtual void bfmeV4976();
	virtual void bfmeV5976();
	virtual void bfmeV6976();
	virtual void bfmeV7976();
	virtual void bfmeV8976();
	virtual void bfmeV9976();
	virtual void bfmeV10976();
	virtual void bfmeV11976();
	virtual char bfmeReady976E();
	virtual void bfmeGap976E();
	virtual void bfmeStop976E(int a);
	virtual void bfmeFinish976E();
};

class BfmeE976
{
public:
	void bfmeGo976E();

	char m_bfmePad[4];
	BfmeDev976 *m_bfmeDev;
	char m_bfmePad2[0x10];
	char m_bfmeOn;
};

void BfmeE976::bfmeGo976E()
{
	if (m_bfmeOn) {
		m_bfmeOn = 0;
		m_bfmeDev->bfmeStop976E(0);

		if (m_bfmeDev->bfmeReady976E())
			m_bfmeDev->bfmeFinish976E();
	}
}
