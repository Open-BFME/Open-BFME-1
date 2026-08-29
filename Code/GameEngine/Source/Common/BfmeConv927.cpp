// Open-BFME5 conversions.

void __cdecl operator delete(void *p);

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

class BfmeObj927B
{
public:
	void bfmeDtor927B();
};

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
