// Open-BFME5 conversions.

struct BfmeObj926C;

class BfmeKey926C
{
public:
	BfmeObj926C *bfmeFind926C();
};

struct BfmeObj926C
{
	char m_bfmePad[0x22c];
	char *m_bfmeUse;
};

class BfmeThing933A
{
public:
	char *bfmeGo933A();
};

char *BfmeThing933A::bfmeGo933A()
{
	BfmeKey926C *k = *(BfmeKey926C **)((char *)this - 0x18);
	BfmeObj926C *o = k->bfmeFind926C();
	return o->m_bfmeUse + 8;
}

class BfmeTail933B
{
public:
	void bfmeTail933B();
};

struct BfmeB933B
{
	char m_bfmePad[0x20];
	BfmeTail933B m_bfmeTail;
};

struct BfmeA933B
{
	char m_bfmePad[0x204];
	BfmeB933B *m_bfmeB;
};

class BfmeThing933B
{
public:
	void bfmeGo933B();
	char m_bfmePad[8];
	BfmeA933B *m_bfmeA;
};

void BfmeThing933B::bfmeGo933B()
{
	BfmeA933B *a = m_bfmeA;
	BfmeB933B *b = a->m_bfmeB;
	b->m_bfmeTail.bfmeTail933B();
}

// TU-local view of the GameLogic singleton's dword at +0x3C.
struct BfmeGlob933C
{
	char m_bfmePad[0x3c];
	unsigned int m_bfmeVal;
};

// Retail's GameLogic singleton at 0x012F0898; the one canonical spelling.
class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeThing933C
{
public:
	int bfmeGo933C();
	char m_bfmePad[0x988];
	unsigned int m_bfmeLimit;
};

int BfmeThing933C::bfmeGo933C()
{
	return ((BfmeGlob933C *)TheGameLogic)->m_bfmeVal < m_bfmeLimit;
}

struct BfmeA933D
{
	char m_bfmePad[0x152];
	char m_bfmeFlag;
};

class BfmeSub933D
{
public:
	void bfmeCall933D();
};

// RVA 0x0024CEE0: HordeTransportContain introduces this die-slot callback.
// The ledger names HordeTransportContain::Rva0024CEE0; this opaque emission
// view is retained through object-symbol. See diemodule-slot0-container-ondie.md.
class BfmeThing933D
{
public:
	void bfmeGo933D(void *a);
};

void BfmeThing933D::bfmeGo933D(void *a)
{
	BfmeA933D *p = *(BfmeA933D **)((char *)this - 0x24);
	if (p->m_bfmeFlag)
		((BfmeSub933D *)((char *)this - 0x28))->bfmeCall933D();
}

struct BfmeVec933F
{
	int m_bfmeX;
	int m_bfmeY;
};

class BfmeThing933G
{
public:
	void bfmeGo933G(BfmeVec933F *out);
};

void BfmeThing933G::bfmeGo933G(BfmeVec933F *out)
{
	volatile int tmp = 0;
	out->m_bfmeX = 0;
	out->m_bfmeY = 0;
}

