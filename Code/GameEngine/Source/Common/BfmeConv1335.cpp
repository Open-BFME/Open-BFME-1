// Open-BFME5 conversions.

struct BfmeGuidUKA
{
	char m_bfmeBytes[16];
};

extern BfmeGuidUKA g_bfmeIidUKA;

class BfmeThingUKA;

struct BfmeVtUKA
{
	void *m_bfmeSlot0;
	void *m_bfmeSlot1;
	void *m_bfmeSlot2;
	void *m_bfmeSlot3;
	void *m_bfmeSlot4;
	void *m_bfmeSlot5;
	void *m_bfmeSlot6;
	long (__stdcall *m_bfmeCallUKA)(BfmeThingUKA *self, void *a);
};

void __stdcall bfmeReportUKA(long hr, BfmeThingUKA *o, BfmeGuidUKA *iid);

class BfmeThingUKA
{
public:
	long bfmeGoUKA(void *a);
	BfmeVtUKA *m_bfmeVt;
};

long BfmeThingUKA::bfmeGoUKA(void *a)
{
	long hr = m_bfmeVt->m_bfmeCallUKA(this, a);
	if (hr < 0)
		bfmeReportUKA(hr, this, &g_bfmeIidUKA);
	return hr;
}

extern float g_bfmeKUKC;

class BfmeThingUKC
{
public:
	void bfmeGoUKC(int n);
	char m_bfmePad[0x20];
	int m_bfme20;
	int m_bfme24;
};

void BfmeThingUKC::bfmeGoUKC(int n)
{
	m_bfme20 = 0;
	m_bfme24 = (int)(n * g_bfmeKUKC);
}

struct BfmeCfgUKD
{
	char m_bfmePad[0x30];
	int m_bfmeMode;
	char m_bfmePad2[4];
	float m_bfmeRate;
};

extern BfmeCfgUKD *g_bfmeCfgUKD;

class BfmeThingUKD
{
public:
	int bfmeGoUKD();
	char m_bfmePad[0x14];
	float m_bfmeBase;
	float m_bfmeStep;
	char m_bfmePad2[0x28];
	float m_bfmeAcc;
};

int BfmeThingUKD::bfmeGoUKD()
{
	if (g_bfmeCfgUKD->m_bfmeMode == 1)
		m_bfmeAcc = m_bfmeBase;
	return (int)(g_bfmeCfgUKD->m_bfmeRate * m_bfmeStep + m_bfmeAcc);
}
