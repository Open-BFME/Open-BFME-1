// Open-BFME5 conversions: allocate-and-fill factories, and a resource reset.
//
// Retail's factories store a vtable pointer, overwrite it, and in one case
// overwrite it twice -- the redundant stores are base-class constructors that
// MSVC could not eliminate across the inline boundary. Reconstructed as plain
// assignments the compiler drops every store but the last, so the ones that
// have to survive are written through a volatile lvalue. That is a spelling
// device standing in for the constructor boundary, not a claim about the
// original declaration; the addresses themselves are masked DIR32s.

class Gen007F0130
{
public:
	static void *operator new(unsigned int n);
};

extern void *g_bfme5VtA;
extern void *g_bfme5VtB;
extern void *g_bfme5VtC;
extern void *g_bfme5VtD;
extern void *g_bfme5VtE;

struct Bfme5Obj18
{
	void *m_bfmeV0;
	void *m_bfmeV4;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

Bfme5Obj18 * __cdecl bfme5MakeObj18(void)
{
	void *q = Gen007F0130::operator new(0x18);
	Bfme5Obj18 *p;

	if (q) {
		p = (Bfme5Obj18 *)q;
		*(void *volatile *)&p->m_bfmeV4 = &g_bfme5VtA;
		*(void *volatile *)&p->m_bfmeV0 = &g_bfme5VtB;
		*(void *volatile *)&p->m_bfmeV4 = &g_bfme5VtC;
		p->m_bfme08 = 0;
		p->m_bfme0c = 0;
		p->m_bfme10 = 0;
		p->m_bfme14 = 0;
		return p;
	}

	return 0;
}

struct Bfme5Obj70
{
	void *m_bfmeV0;
	void *m_bfmeV4;
	int m_bfme08;
	void *m_bfmeVc;
	char m_bfmeRest[0x64];
};

Bfme5Obj70 * __cdecl bfme5MakeObj70(int arg)
{
	void *q = Gen007F0130::operator new(0x70);
	Bfme5Obj70 *p;

	if (q) {
		p = (Bfme5Obj70 *)q;
		*(void *volatile *)&p->m_bfmeV4 = &g_bfme5VtA;
		*(volatile int *)&p->m_bfme08 = arg;
		*(void *volatile *)&p->m_bfmeVc = &g_bfme5VtB;
		*(void *volatile *)&p->m_bfmeV0 = &g_bfme5VtC;
		*(void *volatile *)&p->m_bfmeV4 = &g_bfme5VtD;
		*(void *volatile *)&p->m_bfmeVc = &g_bfme5VtE;
		return p;
	}

	return 0;
}

class TextureClass
{
public:
	void Release_Ref(void);
};

class Bfme5Counted
{
public:
	virtual void bfmeDestroySelf();

	int m_bfmeRefCount;
};

class Bfme5ResourceSet
{
public:
	void bfmeReset(void);

	char m_bfmePad0[0x20];
	TextureClass *m_bfmeTexture;
	Bfme5Counted *m_bfmeCounted;
	int m_bfme28;
	char m_bfmePad1[0x1c];
	int m_bfme48;
	char m_bfmePad2[0x30];
	char m_bfme7c;
};

void Bfme5ResourceSet::bfmeReset(void)
{
	m_bfme7c = 0;

	Bfme5Counted *o = m_bfmeCounted;

	if (o) {
		if (--o->m_bfmeRefCount == 0)
			o->bfmeDestroySelf();

		m_bfmeCounted = 0;
	}

	TextureClass *t = m_bfmeTexture;

	if (t) {
		t->Release_Ref();
		m_bfmeTexture = 0;
	}

	m_bfme28 = 0;
	m_bfme48 = 0;
}
