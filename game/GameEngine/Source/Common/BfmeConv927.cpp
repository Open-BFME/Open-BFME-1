// Open-BFME5 conversions.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

void __cdecl operator delete(void *p);

class Rva0048EC80Manager
{
public:
	virtual void bfmeSlot00E927B();
	virtual void bfmeSlot01E927B();
	virtual void bfmeSlot02E927B();
	virtual void bfmeSlot03E927B();
	virtual void bfmeSlot04E927B();
	virtual void bfmeSlot05E927B();
	virtual void bfmeSlot06E927B();
	virtual void bfmeSlot07E927B();
	virtual void bfmeSlot08E927B();
	virtual void bfmeSlot09E927B();
	virtual void bfmeRelease927B(void *item);
};

extern Rva0048EC80Manager *Rva0048EC80TheManager;

class BfmeSub927A
{
public:
	void bfmeClear927A();
	void *m_bfmeP;
};

class BfmeThing927A
{
public:
	void bfmeGo927A();
	int m_bfmePad;
	BfmeSub927A m_bfmeSub;
};

void BfmeThing927A::bfmeGo927A()
{
	BfmeSub927A *s = &m_bfmeSub;
	s->bfmeClear927A();
	void *p = s->m_bfmeP;
	if (p)
		operator delete(p);
}

class BfmeObj927BEntry
{
public:
	unsigned char m_bfmePad[4];
	void *m_bfmeDisplayString;
};

class BfmeObj927B
{
public:
	~BfmeObj927B();
	void bfmeDtor927B();

private:
	_STL::vector<BfmeObj927BEntry *> m_bfmeEntries;
};

BfmeObj927B::~BfmeObj927B()
{
	for (unsigned int i = 0; i < m_bfmeEntries.size(); ++i)
	{
		BfmeObj927BEntry *entry = m_bfmeEntries[i];
		if (entry != 0)
		{
			if (entry->m_bfmeDisplayString != 0)
			{
				Rva0048EC80TheManager->bfmeRelease927B(entry->m_bfmeDisplayString);
				entry->m_bfmeDisplayString = 0;
			}

			operator delete(entry);
		}
	}

	m_bfmeEntries.clear();
}

void __stdcall bfmeGo927B(BfmeObj927B *p)
{
	if (p) {
		p->bfmeDtor927B();
		operator delete(p);
	}
}

class BfmeSub918P
{
public:
	void bfmeDtor918P();
};

class BfmeThing927C
{
public:
	void *bfmeGo927C(unsigned int flags);
	void bfmeOne927C();
};

void *BfmeThing927C::bfmeGo927C(unsigned int flags)
{
	char *base = (char *)this - 0x74;
	BfmeThing927C *self = (BfmeThing927C *)(base + 0x74);
	self->bfmeOne927C();
	((BfmeSub918P *)self)->bfmeDtor918P();
	if (flags & 1)
		operator delete(base);
	return base;
}

class BfmeThing927D
{
public:
	void *bfmeGo927D(unsigned int flags);
	void bfmeOne927D();
};

void *BfmeThing927D::bfmeGo927D(unsigned int flags)
{
	char *base = (char *)this - 0x70;
	BfmeThing927D *self = (BfmeThing927D *)(base + 0x70);
	self->bfmeOne927D();
	((BfmeSub918P *)self)->bfmeDtor918P();
	if (flags & 1)
		operator delete(base);
	return base;
}

struct BfmeVt927E
{
	char m_bfmePad[8];
	void (__stdcall *m_bfmeFn)(void *o);
};

struct BfmeSub927E
{
	BfmeVt927E *m_bfmeVt;
};

extern char g_bfme927Vft[];

class BfmeThing927E
{
public:
	void *bfmeGo927E(unsigned int flags);
	char *m_bfmeVft;
	int m_bfmePad;
	BfmeSub927E *m_bfmeSub;
};

void *BfmeThing927E::bfmeGo927E(unsigned int flags)
{
	BfmeSub927E *s = m_bfmeSub;
	m_bfmeVft = g_bfme927Vft;
	if (s)
		s->m_bfmeVt->m_bfmeFn(s);
	if (flags & 1)
		operator delete(this);
	return this;
}
