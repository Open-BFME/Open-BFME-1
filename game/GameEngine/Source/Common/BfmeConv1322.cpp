// Open-BFME5 conversions.

class BfmePoolTRB
{
public:
	void bfmeFreeTRB(void *p);
};

extern BfmePoolTRB g_bfmePoolTRB;

class BfmeThingTRB
{
public:
	void *bfmeDelTRB(unsigned char flags);
	void bfmeDtorTRB();
};

void *BfmeThingTRB::bfmeDelTRB(unsigned char flags)
{
	bfmeDtorTRB();
	if ((flags & 1) && this)
		g_bfmePoolTRB.bfmeFreeTRB(this);
	return this;
}

struct BfmeGuidTSA
{
	char m_bfmeBytes[16];
};

extern BfmeGuidTSA g_bfmeIidTSA;

class BfmeThingTSA;

struct BfmeVtTSA
{
	void *m_bfmeSlot0;
	void *m_bfmeSlot1;
	void *m_bfmeSlot2;
	void *m_bfmeSlot3;
	void *m_bfmeSlot4;
	void *m_bfmeSlot5;
	void *m_bfmeSlot6;
	void *m_bfmeSlot7;
	long (__stdcall *m_bfmeOneTSA)(BfmeThingTSA *self);
	void *m_bfmeSlot9;
	void *m_bfmeSlot10;
	void *m_bfmeSlot11;
	void *m_bfmeSlot12;
	void *m_bfmeSlot13;
	void *m_bfmeSlot14;
	long (__stdcall *m_bfmeTwoTSA)(BfmeThingTSA *self);
};

void __stdcall bfmeReportTSA(long hr, BfmeThingTSA *o, BfmeGuidTSA *iid);

class BfmeThingTSA
{
public:
	long bfmeGoOneTSA();
	long bfmeGoTwoTSA();
	BfmeVtTSA *m_bfmeVt;
};

long BfmeThingTSA::bfmeGoOneTSA()
{
	long hr = m_bfmeVt->m_bfmeOneTSA(this);
	if (hr < 0)
		bfmeReportTSA(hr, this, &g_bfmeIidTSA);
	return hr;
}

long BfmeThingTSA::bfmeGoTwoTSA()
{
	long hr = m_bfmeVt->m_bfmeTwoTSA(this);
	if (hr < 0)
		bfmeReportTSA(hr, this, &g_bfmeIidTSA);
	return hr;
}
