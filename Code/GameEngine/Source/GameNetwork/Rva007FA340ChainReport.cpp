// cl: /O2 /DNDEBUG /MD
// Retail 0x007FA340: notify the handler, advance the live-slot watermark,
// and report the first queued chain item through the FESL diagnostic object.

class Rva007FA340Handler
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2(void *);
};

class Rva007FA2C0
{
public:
	void walk(unsigned int);
};

class Rva00800550Chain
{
public:
	void *first();
	void popFront();
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4(void *, void *, void *, void *);
};

extern Rva007EB810Diag *Rva007EB810Get();

extern void Rva007F93E0(void *, void *, void *);
typedef void *(__cdecl *Rva007F93E0Ret)(void *, void *, void *);

class Rva007FA340
{
public:
	void process(void *);

private:
	char m_pad00[0x10];
	unsigned int m_watermark;
	Rva007FA340Handler *m_handler;
	char m_pad18[0x68c];
	Rva00800550Chain m_chain;
};

void Rva007FA340::process(void *item)
{
	m_handler->v2(item);
	unsigned int value = (unsigned int)item;
	if (m_watermark != 0 && value >= m_watermark)
		((Rva007FA2C0 *)((char *)this - 8))->walk(value);

	if (*(int *)((char *)this + 0x6a4) == 0)
		return;
	Rva00800550Chain *chain = &m_chain;
	void *first = chain->first();

	Rva007EB810Diag *diag = Rva007EB810Get();
	diag->v4(((Rva007F93E0Ret)Rva007F93E0)(
		first, (void *)0x0112bb94, m_handler),
		(void *)0x0112bb98, (void *)0x0112ba50, (void *)0x2d6);
	chain->popFront();
}
