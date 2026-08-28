void __cdecl bfmeFreeELA(void *p);

struct BfmeThingELAa
{
	void bfmeGoELAa();
	void bfmeClearELAa();
	void *m_bfmeP;
};

void BfmeThingELAa::bfmeGoELAa()
{
	bfmeClearELAa();
	void *p = m_bfmeP;
	if (p)
		bfmeFreeELA(p);
}

struct BfmeThingELAb
{
	void bfmeGoELAb();
	void bfmeClearELAa();
	void *m_bfmeP;
};

void BfmeThingELAb::bfmeGoELAb()
{
	bfmeClearELAa();
	void *p = m_bfmeP;
	if (p)
		bfmeFreeELA(p);
}

class BfmeObjELB
{
public:
	void bfmeTailELB(int n);
};

extern BfmeObjELB *g_bfmeObjELB;

void __stdcall bfmeGoELB(int unused)
{
	BfmeObjELB *o = g_bfmeObjELB;
	if (o)
		o->bfmeTailELB(1);
}

struct BfmeSubELC
{
	void bfmeTailELC(int n);
	unsigned char m_bfmeHead[0x20];
	unsigned char m_bfmeFlags;
};

struct BfmeThingELC
{
	void bfmeGoELC(int unused);
	unsigned char m_bfmeHead[0x10];
	BfmeSubELC *m_bfmeS;
};

void BfmeThingELC::bfmeGoELC(int unused)
{
	BfmeSubELC *s = m_bfmeS;
	if (s->m_bfmeFlags & 1)
		s->bfmeTailELC(0x1f4);
}

void __cdecl bfmeFreeELD(void *p);

struct BfmeThingELDa
{
	void bfmeGoELDa(void *a);
	void *m_bfmeP;
};

void BfmeThingELDa::bfmeGoELDa(void *a)
{
	void *old = m_bfmeP;
	if (a != old)
	{
		bfmeFreeELD(old);
		m_bfmeP = a;
	}
}

struct BfmeThingELDb
{
	void bfmeGoELDb(void *a);
	void *m_bfmeP;
};

void BfmeThingELDb::bfmeGoELDb(void *a)
{
	void *old = m_bfmeP;
	if (a != old)
	{
		bfmeFreeELD(old);
		m_bfmeP = a;
	}
}

void __cdecl bfmeCallELE(void *p, void *a);

struct BfmeThingELE
{
	void bfmeGoELE(void *a);
	unsigned char m_bfmeHeadA[0x3d];
	char m_bfmeFlag;
	unsigned char m_bfmeHeadB[0x26];
	void *m_bfmeP;
};

void BfmeThingELE::bfmeGoELE(void *a)
{
	if (m_bfmeFlag)
		bfmeCallELE(m_bfmeP, a);
}

struct BfmeThingELF
{
	void bfmeGoELF(void *a);
	unsigned char m_bfmeHead[4];
	void (__cdecl *m_bfmeFn)(void *ctx, void *a);
	void *m_bfmeCtx;
};

void BfmeThingELF::bfmeGoELF(void *a)
{
	void (__cdecl *fn)(void *, void *) = m_bfmeFn;
	if (fn)
		fn(m_bfmeCtx, a);
}

class BfmeSubELGa
{
public:
	void bfmeTailELGa(void *a);
};

struct BfmeThingELGa
{
	void bfmeGoELGa(void *a);
	unsigned char m_bfmeHead[0x30b4];
	BfmeSubELGa *m_bfmeS;
};

void BfmeThingELGa::bfmeGoELGa(void *a)
{
	BfmeSubELGa *s = m_bfmeS;
	if (s && a)
		s->bfmeTailELGa(a);
}

class BfmeSubELGb
{
public:
	void bfmeTailELGb(void *a);
};

struct BfmeThingELGb
{
	void bfmeGoELGb(void *a);
	unsigned char m_bfmeHead[0x10];
	BfmeSubELGb *m_bfmeS;
};

void BfmeThingELGb::bfmeGoELGb(void *a)
{
	BfmeSubELGb *s = m_bfmeS;
	if (s && a)
		s->bfmeTailELGb(a);
}

struct BfmeObjELH;

struct BfmeVtblELH
{
	void (__stdcall *m_bfmeF0)(void *o, void *a);
	void (__stdcall *m_bfmeF1)(void *o, void *a);
	void (__stdcall *m_bfmeF2)(void *o, void *a);
	void (__stdcall *m_bfmeF3)(void *o, void *a);
	void (__stdcall *m_bfmeF4)(void *o, void *a);
	void (__stdcall *m_bfmeF5)(void *o, void *a);
	void (__stdcall *m_bfmeF6)(void *o, void *a);
	void (__stdcall *m_bfmeF7)(void *o, void *a);
	void (__stdcall *m_bfmeF8)(void *o, void *a);
	void (__stdcall *m_bfmeF9)(void *o, void *a);
	void (__stdcall *m_bfmeF10)(void *o, void *a);
	void (__stdcall *m_bfmeF11)(void *o, void *a);
	void (__stdcall *m_bfmeF12)(void *o, void *a);
	void (__stdcall *m_bfmeF13)(void *o, void *a);
	void (__stdcall *m_bfmeF14)(void *o, void *a);
	void (__stdcall *m_bfmeF15)(void *o, void *a);
	void (__stdcall *m_bfmeF16)(void *o, void *a);
	void (__stdcall *m_bfmeF17)(void *o, void *a);
	void (__stdcall *m_bfmeF18)(void *o, void *a);
	void (__stdcall *m_bfmeF19)(void *o, void *a);
	void (__stdcall *m_bfmeF20)(void *o, void *a);
	void (__stdcall *m_bfmeF21)(void *o, void *a);
	void (__stdcall *m_bfmeF22)(void *o, void *a);
	void (__stdcall *m_bfmeF23)(void *o, void *a);
	void (__stdcall *m_bfmeF24)(void *o, void *a);
	void (__stdcall *m_bfmeF25)(void *o, void *a);
	void (__stdcall *m_bfmeF26)(void *o, void *a);
	void (__stdcall *m_bfmeF27)(void *o, void *a);
	void (__stdcall *m_bfmeF28)(void *o, void *a);
	void (__stdcall *m_bfmeF29)(void *o, void *a);
	void (__stdcall *m_bfmeF30)(void *o, void *a);
	void (__stdcall *m_bfmeF31)(void *o, void *a);
	void (__stdcall *m_bfmeF32)(void *o, void *a);
	void (__stdcall *m_bfmeF33)(void *o, void *a);
	void (__stdcall *m_bfmeF34)(void *o, void *a);
	void (__stdcall *m_bfmeF35)(void *o, void *a);
	void (__stdcall *m_bfmeF36)(void *o, void *a);
	void (__stdcall *m_bfmeF37)(void *o, void *a);
	void (__stdcall *m_bfmeF38)(void *o, void *a);
	void (__stdcall *m_bfmeF39)(void *o, void *a);
	void (__stdcall *m_bfmeF40)(void *o, void *a);
	void (__stdcall *m_bfmeF41)(void *o, void *a);
	void (__stdcall *m_bfmeF42)(void *o, void *a);
	void (__stdcall *m_bfmeF43)(void *o, void *a);
	void (__stdcall *m_bfmeF44)(void *o, void *a);
	void (__stdcall *m_bfmeF45)(void *o, void *a);
	void (__stdcall *m_bfmeF46)(void *o, void *a);
	void (__stdcall *m_bfmeF47)(void *o, void *a);
	void (__stdcall *m_bfmeF48)(void *o, void *a);
	void (__stdcall *m_bfmeF49)(void *o, void *a);
	void (__stdcall *m_bfmeF50)(void *o, void *a);
	void (__stdcall *m_bfmeF51)(void *o, void *a);
	void (__stdcall *m_bfmeF52)(void *o, void *a);
	void (__stdcall *m_bfmeF53)(void *o, void *a);
	void (__stdcall *m_bfmeF54)(void *o, void *a);
	void (__stdcall *m_bfmeF55)(void *o, void *a);
	void (__stdcall *m_bfmeF56)(void *o, void *a);
	void (__stdcall *m_bfmeF57)(void *o, void *a);
	void (__stdcall *m_bfmeF58)(void *o, void *a);
	void (__stdcall *m_bfmeF59)(void *o, void *a);
	void (__stdcall *m_bfmeF60)(void *o, void *a);
	void (__stdcall *m_bfmeF61)(void *o, void *a);
	void (__stdcall *m_bfmeF62)(void *o, void *a);
	void (__stdcall *m_bfmeF63)(void *o, void *a);
	void (__stdcall *m_bfmeF64)(void *o, void *a);
	void (__stdcall *m_bfmeF65)(void *o, void *a);
	void (__stdcall *m_bfmeF66)(void *o, void *a);
	void (__stdcall *m_bfmeF67)(void *o, void *a);
	void (__stdcall *m_bfmeF68)(void *o, void *a);
	void (__stdcall *m_bfmeF69)(void *o, void *a);
	void (__stdcall *m_bfmeF70)(void *o, void *a);
	void (__stdcall *m_bfmeF71)(void *o, void *a);
	void (__stdcall *m_bfmeF72)(void *o, void *a);
	void (__stdcall *m_bfmeF73)(void *o, void *a);
	void (__stdcall *m_bfmeF74)(void *o, void *a);
	void (__stdcall *m_bfmeF75)(void *o, void *a);
	void (__stdcall *m_bfmeF76)(void *o, void *a);
	void (__stdcall *m_bfmeF77)(void *o, void *a);
	void (__stdcall *m_bfmeF78)(void *o, void *a);
	void (__stdcall *m_bfmeF79)(void *o, void *a);
	void (__stdcall *m_bfmeF80)(void *o, void *a);
	void (__stdcall *m_bfmeF81)(void *o, void *a);
	void (__stdcall *m_bfmeF82)(void *o, void *a);
	void (__stdcall *m_bfmeF83)(void *o, void *a);
	void (__stdcall *m_bfmeF84)(void *o, void *a);
	void (__stdcall *m_bfmeF85)(void *o, void *a);
	void (__stdcall *m_bfmeF86)(void *o, void *a);
	void (__stdcall *m_bfmeF87)(void *o, void *a);
	void (__stdcall *m_bfmeF88)(void *o, void *a);
	void (__stdcall *m_bfmeF89)(BfmeObjELH *o, void *a);
	void (__stdcall *m_bfmeF90)(BfmeObjELH *o, void *a);
	void (__stdcall *m_bfmeF91)(BfmeObjELH *o, void *a);
	void (__stdcall *m_bfmeF92)(BfmeObjELH *o, void *a);
};

struct BfmeObjELH
{
	BfmeVtblELH *m_bfmeVtbl;
};

extern BfmeObjELH *g_bfmeObjELH;
extern int g_bfmeCountELH;

void bfmeGoELHa(void *a)
{
	BfmeObjELH *o = g_bfmeObjELH;
	o->m_bfmeVtbl->m_bfmeF89(o, a);
	++g_bfmeCountELH;
}

void bfmeGoELHb(void *a)
{
	BfmeObjELH *o = g_bfmeObjELH;
	o->m_bfmeVtbl->m_bfmeF92(o, a);
	++g_bfmeCountELH;
}

