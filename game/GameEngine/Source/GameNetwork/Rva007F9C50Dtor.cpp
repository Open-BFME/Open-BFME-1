// cl: /O2
// 0x007F9C50: destructor. Three most-derived vptrs, drop the +0x6A8 heap
// object, clear the chain at +0x6AC, then walk 32 0x1C slots backward.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *acquire(int size, int flags);
	virtual void release(void *block, int flags);
};

extern GenAlloc *Gen007EFFC0();

void bfmeDeleteVMP(void *block, unsigned size);

class Rva00800550Chain
{
public:
	void clear();
};

class Rva007F9C50Base0
{
public:
	virtual void v0();
	~Rva007F9C50Base0() throw() {}
};

class Rva007F9C50Base4
{
public:
	virtual void v4();
};

class Rva007F9C50Base8
{
public:
	virtual void v8();
};

struct Rva007F9C50Node
{
	void *a;
	void *b;
	void *c;
};

class Rva007F9C50Heap
{
public:
	virtual void wipe(unsigned flag);
};

class Rva007F9C50 : public Rva007F9C50Base0, public Rva007F9C50Base4, public Rva007F9C50Base8
{
public:
	~Rva007F9C50() throw();
	virtual void v0();
	virtual void v4();
	virtual void v8();

private:
	char m_pad[0x1C];
	char m_slots[0x380];
	char m_pad3A8[0x300];
	Rva007F9C50Heap *m_6A8;
	Rva00800550Chain m_chain;
};

Rva007F9C50::~Rva007F9C50() throw()
{
	Rva007F9C50Heap *p = m_6A8;
	if (p)
		p->wipe(1);
	m_6A8 = 0;
	m_chain.clear();

	char *edi = (char *)this + 0x3A8;
	int n = 0x20;
	do
	{
		Rva007F9C50Node *esi = *(Rva007F9C50Node **)(edi - 4);
		edi -= 0x1C;
		if (esi)
		{
			Gen007EFFC0()->release(esi->c, 1);
			esi->b = 0;
			esi->a = 0;
			esi->c = 0;
			bfmeDeleteVMP(esi, 0xC);
		}
		*(void **)(edi + 4) = 0;
		*(void **)edi = 0;
		*(void **)(edi + 8) = 0;
		*(void **)(edi + 0xC) = 0;
		*(void **)(edi + 0x10) = 0;
		*(void **)(edi + 0x14) = 0;
		*(void **)(edi + 0x18) = 0;
	} while (--n);
}
