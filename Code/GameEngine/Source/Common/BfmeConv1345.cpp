// Open-BFME5 conversions.

struct BfmeVecUXA
{
	float m_bfmeX;
	float m_bfmeY;
};

int bfmeCrossUXA(const BfmeVecUXA *a, const BfmeVecUXA *b, const BfmeVecUXA *c)
{
	return (int)((c->m_bfmeY - a->m_bfmeY) * (b->m_bfmeX - a->m_bfmeX)
		- (b->m_bfmeY - a->m_bfmeY) * (c->m_bfmeX - a->m_bfmeX));
}

__declspec(dllimport) void __cdecl bfmeFreeUXB(void *p);

class BfmeStrUXB
{
public:
	void bfmeClearUXB();
};

class BfmeThingUXB
{
public:
	virtual void bfmeV0UXB() = 0;
	virtual void bfmeDropUXB() = 0;
	void bfmeGoUXB();
	char m_bfmePad[8];
	void *m_bfmeHandle;
	BfmeStrUXB m_bfmeStr;
};

void BfmeThingUXB::bfmeGoUXB()
{
	if (m_bfmeHandle) {
		bfmeFreeUXB(m_bfmeHandle);
		m_bfmeHandle = 0;
	}
	m_bfmeStr.bfmeClearUXB();
	bfmeDropUXB();
}

class BfmeThingUXC
{
public:
	BfmeThingUXC *bfmeGoUXC(const char *s, float v);
	void bfmeSetStrUXC(const char *s);
	char m_bfmePad[4];
	int m_bfmeKind;
	int m_bfme08;
	int m_bfme0c;
};

BfmeThingUXC *BfmeThingUXC::bfmeGoUXC(const char *s, float v)
{
	bfmeSetStrUXC(s);
	m_bfmeKind = 2;
	int n = (int)v;
	m_bfme08 = n;
	m_bfme0c = n;
	return this;
}
