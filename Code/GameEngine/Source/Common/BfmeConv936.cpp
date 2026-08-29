// Open-BFME5 conversions.

void __stdcall bfmeElem936B(void *p);
void __stdcall bfmeVecDtor936B(void *p, unsigned int size, int count, void (__stdcall *dtor)(void *));

class BfmeThing936B
{
public:
	void bfmeGo936B();
};

void BfmeThing936B::bfmeGo936B()
{
	bfmeVecDtor936B(this, 4, 0x80, bfmeElem936B);
}

struct BfmeVt936C
{
	char m_bfmePad[0x14];
	void (__stdcall *m_bfmeFn)(void *o);
};

struct BfmeObj936C
{
	BfmeVt936C *m_bfmeVt;
};

extern BfmeObj936C *g_bfme936Ptr;
extern int g_bfme936Count;

void bfmeGo936C(void)
{
	BfmeObj936C *p = g_bfme936Ptr;
	p->m_bfmeVt->m_bfmeFn(p);
	++g_bfme936Count;
}

void bfmeCall936F(int f);

class BfmeThing936F
{
public:
	void bfmeGo936F();
	char m_bfmePad[0x60];
	unsigned int m_bfmeCount;
};

void BfmeThing936F::bfmeGo936F()
{
	--*(unsigned short *)&m_bfmeCount;
	if ((m_bfmeCount & 0xffff) == 0)
		bfmeCall936F(0);
}

extern void *g_bfme936GlobG;

class BfmeThing936G
{
public:
	BfmeThing936G *bfmeGo936G();
	void bfmeInit936G();
};

BfmeThing936G *BfmeThing936G::bfmeGo936G()
{
	if (!g_bfme936GlobG)
		bfmeInit936G();
	return this;
}
