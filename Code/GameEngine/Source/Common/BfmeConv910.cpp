// Open-BFME5 conversions.

__declspec(dllimport) void __cdecl bfmeFreeUEW(void *p, unsigned int n);

class BfmeThingUEW
{
public:
	void *bfmeGoUE(unsigned int flags);
	void bfmeDtorUEW();
};

void *BfmeThingUEW::bfmeGoUE(unsigned int flags)
{
	bfmeDtorUEW();
	if (flags & 1)
		bfmeFreeUEW(this, 0x12b4);
	return this;
}

class BfmeSubVBW
{
public:
	void bfmeDtorVBW();
	int m_bfmeRef;
};

class BfmeThingVBW
{
public:
	void bfmeGoVB();
	int m_bfmePad;
	BfmeSubVBW *m_bfmeP;
};

void BfmeThingVBW::bfmeGoVB()
{
	BfmeSubVBW *p = m_bfmeP;
	if (!p)
		return;
	if (--p->m_bfmeRef != 0)
		return;
	BfmeSubVBW *s = m_bfmeP;
	if (s) {
		s->bfmeDtorVBW();
		bfmeFreeUEW(s, 0x18);
	}
}

__declspec(dllimport) void __cdecl bfmeFreeVCW(void *p);

class Gen_00893990
{
public:
	void bfmeCleanup();
};

class BfmeNodeVCW
{
public:
	int m_bfmePad;
	BfmeNodeVCW *m_bfmeNext;
};

class BfmeThingVCW
{
public:
	void bfmeGoVC();
	BfmeNodeVCW *m_bfmeHead;
};

void BfmeThingVCW::bfmeGoVC()
{
	BfmeNodeVCW *n = m_bfmeHead;
	if (n) {
		BfmeNodeVCW *next = n->m_bfmeNext;
		((Gen_00893990 *)n)->bfmeCleanup();
		bfmeFreeVCW(n);
		m_bfmeHead = next;
	}
}

extern char g_bfmeVftVDW[];

class BfmeThingVDW
{
public:
	BfmeThingVDW *bfmeGoVD();
	void bfmeBaseVDW(int a, int b);
	char *m_bfmeVft;
	unsigned int m_bfmeBits;
};

BfmeThingVDW *BfmeThingVDW::bfmeGoVD()
{
	bfmeBaseVDW(0x18, 8);
	m_bfmeBits = (m_bfmeBits & 0xffffc07f) | 0x0fff0040;
	m_bfmeVft = g_bfmeVftVDW;
	return this;
}
