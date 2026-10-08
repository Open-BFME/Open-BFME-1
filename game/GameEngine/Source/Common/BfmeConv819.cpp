class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;

struct BfmeSubEMA
{
	unsigned char m_bfmeHead[4];
};

struct BfmeThingEMA
{
	unsigned char m_bfmeHead[0x9c];
	BfmeSubEMA m_bfmeSub;
};

void __cdecl bfmeCallEMA(void *a, BfmeThingEMA *b, BfmeSubEMA *s);

void bfmeGoEMA(void *a, BfmeThingEMA *b)
{
	bfmeCallEMA(a, b, &b->m_bfmeSub);
}

extern "C" void bfmeCbEMB();

struct BfmeThingEMB
{
	unsigned char m_bfmeHead[0xab4];
	void *m_bfmeP;
};

void __cdecl bfmeCallEMB(void *p, void (*cb)(), void **out);

// GameSpy 2004 peer piFindPlayerByIP(peer, IP) (pin _piFindPlayerByIP,
// vendored=gamespy-2004): maps the connection player table with the IP;
// the table call leaves the found player in eax.
extern "C" void piFindPlayerByIP(BfmeThingEMB *a, void *b)
{
	bfmeCallEMB(a->m_bfmeP, bfmeCbEMB, &b);
}

class BfmeObjEMC
{
public:
	void bfmeCallEMC(void *x, void *b, void *c);
};

extern void *g_bfmeXEMC;

void __stdcall bfmeGoEMC(BfmeObjEMC *o, void *b, void *c)
{
	o->bfmeCallEMC(g_bfmeXEMC, b, c);
}

class BfmeObjEME
{
public:
	bool bfmeAskEME(void *a);
	void *bfmeGetEME(void *a);
};

class AssetManagerImpl;
class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;

bool bfmeGoEMEa(void *a)
{
	BfmeObjEME *o = (BfmeObjEME *)g_theAssetRegistry;
	if (!o)
		return false;
	return o->bfmeAskEME(a);
}

void *bfmeGoEMEb(void *a)
{
	BfmeObjEME *o = (BfmeObjEME *)g_theAssetRegistry;
	if (!o)
		return 0;
	return o->bfmeGetEME(a);
}

void __stdcall bfmeCallEMGa(void *a, int i);
void __stdcall bfmeCallEMGb(int i, void *a);

void __stdcall bfmeGoEMGa(void *a)
{
	for (int i = 0; i < 2; ++i)
		bfmeCallEMGa(a, i);
}

void __stdcall bfmeGoEMGb(void *a)
{
	for (int i = 0; i < 6; ++i)
		bfmeCallEMGb(i, a);
}

struct BfmeSubEMH
{
	unsigned char m_bfmeHead[4];
	char m_bfmeFlag;
};

class BfmeGlobEMHa
{
public:
	void bfmeDoEMHa();
};

class BfmeGlobEMHb
{
public:
	void bfmeDoEMHb();
};




struct BfmeThingEMH
{
	void bfmeGoEMHa();
	void bfmeGoEMHb();
	unsigned char m_bfmeHead[0x148];
	BfmeSubEMH *m_bfmeS;
};

void BfmeThingEMH::bfmeGoEMHa()
{
	((BfmeGlobEMHa *&)TheW3DShadowManager)->bfmeDoEMHa();
	BfmeSubEMH *s = m_bfmeS;
	if (s)
		s->m_bfmeFlag = 1;
}

void BfmeThingEMH::bfmeGoEMHb()
{
	((BfmeGlobEMHb *&)TheW3DShadowManager)->bfmeDoEMHb();
	BfmeSubEMH *s = m_bfmeS;
	if (s)
		s->m_bfmeFlag = 0;
}
