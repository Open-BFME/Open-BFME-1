// Open-BFME5 conversions.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>

extern char g_bfme928Handler[];

struct BfmeObj928A
{
	int m_bfmePad;
	unsigned int m_bfmeBits;
	char m_bfmePad2[0x10];
	char *m_bfmeFn;
};

void __stdcall bfmeTail928A(BfmeObj928A *a);

void __stdcall bfmeGo928A(BfmeObj928A *a)
{
	a->m_bfmeBits |= 0x80;
	a->m_bfmeFn = g_bfme928Handler;
	*(BfmeObj928A *volatile *)&a = a;
	bfmeTail928A(a);
}

class BfmeSub928B
{
public:
	virtual void bfmeSlot928B00();
	virtual void bfmeSlot928B01();
	virtual void bfmeSlot928B02();
	virtual void bfmeVirt928B(void *a);
};

class BfmeThing928B
{
public:
	void bfmeGo928B(void *a);
	char m_bfmePad[0x74];
	BfmeSub928B *m_bfmeSub;
};

void BfmeThing928B::bfmeGo928B(void *a)
{
	if (!m_bfmeSub)
		return;
	if (!a)
		return;
	m_bfmeSub->bfmeVirt928B(a);
}

struct BfmeArg928C
{
	void *m_bfmeP;
};

class BfmeSub928C
{
public:
	void bfmeTail928C(void *p);
};

class BfmeThing928C
{
public:
	void bfmeGo928C(BfmeArg928C *a);
	char m_bfmePad[0x1c0];
	BfmeSub928C *m_bfmeSub;
};

void BfmeThing928C::bfmeGo928C(BfmeArg928C *a)
{
	void *p = a->m_bfmeP;
	if (!p)
		return;
	BfmeSub928C *s = m_bfmeSub;
	if (!s)
		return;
	s->bfmeTail928C(p);
}

void bfmeCall928D(void *p);

class BfmeThing928D
{
public:
	BfmeThing928D *bfmeGo928D(void **src);
	void *m_bfmeP;
};

BfmeThing928D *BfmeThing928D::bfmeGo928D(void **src)
{
	void *p = *src;
	m_bfmeP = p;
	if (p)
		bfmeCall928D(p);
	return this;
}

class BfmeThing928E;
void bfmeCall928E(BfmeThing928E *t, void *a, void *b, void *c);

class BfmeThing928E
{
public:
	void bfmeGo928E(void *a, void *b, void *c);
};

void BfmeThing928E::bfmeGo928E(void *a, void *b, void *c)
{
	bfmeCall928E(this, a, b, c);
}

class BfmeSub928F
{
public:
	void bfmeTail928F();
};

struct Rva007B4CD0Entry
{
	char m_pad00[0x34];
	int m_type;
	char m_pad38[0x9c];
	Rva007B4CD0Entry *m_next;
};

class Shadow
{
public:
	virtual void slot00(int);
	virtual void slot04(int);
	virtual void release();
	void rva00459960(int, int, int, int, int, int, int, int);
};

class BfmeThing928F
{
public:
	void bfmeGo928F();
	void bfmeOne928F();
	void bfmeTwo928F();

	void *m_pad00;
	Rva007B4CD0Entry *m_list04;
	Rva007B4CD0Entry *m_list08;
	char m_bfmePad[0x240];
	BfmeSub928F *m_bfmeSub;
};

void BfmeThing928F::bfmeGo928F()
{
	bfmeOne928F();
	bfmeTwo928F();
	m_bfmeSub->bfmeTail928F();
}

void BfmeThing928F::bfmeOne928F()
{
	_STL::list<Shadow *> pending;

	for (int list = 0; list <= 1; ++list)
	{
		Rva007B4CD0Entry *entry = list ? m_list04 : m_list08;
		while (entry)
		{
			if (entry->m_type == 0x400 || entry->m_type == 0x800)
				pending.push_back((Shadow *)entry);
			entry = entry->m_next;
		}
	}

	for (_STL::list<Shadow *>::iterator it = pending.begin();
		it != pending.end(); ++it)
	{
		(*it)->rva00459960(0, 0, 0, 0, 0, 0, 0, 0);
		(*it)->release();
	}
	pending.clear();
}

__declspec(dllimport) void __stdcall bfmeImport928G(void *h);
extern char g_bfme928Vft[];

class BfmeThing928G
{
public:
	void bfmeGo928G();
	void bfmeTail928G();
	char *m_bfmeVft;
	char m_bfmePad[0x58];
	void *m_bfmeH;
};

void BfmeThing928G::bfmeGo928G()
{
	void *h = m_bfmeH;
	m_bfmeVft = g_bfme928Vft;
	bfmeImport928G(h);
	bfmeTail928G();
}
