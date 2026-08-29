// Open-BFME5 conversions.

extern char g_bfme911Flag;
extern int g_bfme911Val;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static bool Has_Stencil();
};

void bfmeGo911A(void)
{
	if (g_bfme911Flag) {
		if (DX8Wrapper::Has_Stencil())
			g_bfme911Val = 0x100;
		g_bfme911Flag = 0;
	}
}

class RayCollisionTestClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/aabtree.h
class AABTreeClass
{
public:
	struct CullNodeStruct;
	char m_bfmePad[0xc];
	CullNodeStruct *m_bfmeRoot;
private:
	bool Cast_Ray_Recursive(CullNodeStruct *n, RayCollisionTestClass &r);
	friend class BfmeThing911B;
};

class BfmeThing911B
{
public:
	void bfmeGo911B(void *a);
	void bfmeElse911B(void *a);
	char m_bfmePad[0x90];
	AABTreeClass *m_bfmeSub;
};

void BfmeThing911B::bfmeGo911B(void *a)
{
	AABTreeClass *s = m_bfmeSub;
	if (s) {
		s->Cast_Ray_Recursive(s->m_bfmeRoot, *(RayCollisionTestClass *)a);
		return;
	}
	bfmeElse911B(a);
}

class BfmeObj911C
{
public:
	virtual void bfmeRelease911C();
	int m_bfmeRef;
};

extern BfmeObj911C *g_bfme911Ptr;
extern char g_bfme911Busy;

void bfmeGo911C(void)
{
	BfmeObj911C *p = g_bfme911Ptr;
	if (p) {
		if (--p->m_bfmeRef == 0)
			p->bfmeRelease911C();
		g_bfme911Ptr = 0;
	}
	g_bfme911Busy = 0;
}

class BfmeA911D
{
public:
	virtual void bfmeSlot911D0();
	virtual void bfmeSlot911D1();
	virtual void bfmeStop911D();
};

class BfmeB911D
{
public:
	virtual void bfmeSlot911E0();
	virtual void bfmeFree911D();
};

class BfmeThing911D
{
public:
	void bfmeGo911D();
	char m_bfmePad[0x4c];
	BfmeB911D *m_bfmeB;
	BfmeA911D *m_bfmeA;
};

void BfmeThing911D::bfmeGo911D()
{
	BfmeA911D *a = m_bfmeA;
	if (a)
		a->bfmeStop911D();
	BfmeB911D *b = m_bfmeB;
	if (b)
		b->bfmeFree911D();
	m_bfmeB = 0;
}

class BfmeSub911E
{
public:
	virtual void bfmeSlot911F0();
	virtual void bfmeDrop911E(int f);
	void bfmePrep911E();
};

class BfmeThing911E
{
public:
	void bfmeGo911E();
	char m_bfmePad[0x14];
	BfmeSub911E *m_bfmeSub;
};

void BfmeThing911E::bfmeGo911E()
{
	m_bfmeSub->bfmePrep911E();
	BfmeSub911E *s = m_bfmeSub;
	if (s)
		s->bfmeDrop911E(1);
	m_bfmeSub = 0;
}

class BfmeThingVDW
{
public:
	void bfmeBaseVDW(int a, int b);
};

extern char g_bfme911Vft[];

class BfmeThing911F
{
public:
	BfmeThing911F *bfmeGo911F(int a, void *b);
	char *m_bfmeVft;
	char m_bfmePad[0x1c];
	void *m_bfmeArg;
};

BfmeThing911F *BfmeThing911F::bfmeGo911F(int a, void *b)
{
	((BfmeThingVDW *)this)->bfmeBaseVDW(a, 8);
	m_bfmeVft = g_bfme911Vft;
	m_bfmeArg = b;
	return this;
}
