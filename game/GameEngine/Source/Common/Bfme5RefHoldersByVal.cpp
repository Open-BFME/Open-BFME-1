// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: by-value ref-holder constructors at 0x004C6370 / 0x004C6430 /
// 0x004C64E0. Same 16-byte and 12-byte nodes as Bfme5RefNodes.cpp and
// Bfme5TrackPoints.cpp, but the inner pointers arrive as a by-value pair
// (or a single refcounted pointer) whose destructor is the EH frame.

void *__cdecl operator new(unsigned int n);

extern void *g_bfmeRva010FE034Vt;
extern void *g_bfmeRva010FE04CVt;
extern void *g_bfmeRva010FE040Vt;

struct Bfme5RefY
{
	void *m_bfmeVptr;
	int m_bfmeRefCount;
	Bfme5RefY *m_bfmeInner0;
	Bfme5RefY *m_bfmeInner1;
};

struct Bfme5RefX
{
	void *m_bfmeVptr;
	int m_bfmeRefCount;
	Bfme5RefX *m_bfmeInner;
};

class Bfme5RefCounted
{
public:
	void Release_Ref()
	{
		if ((m_refs = m_refs - 1) <= 0)
			Delete_This(1);
	}

protected:
	virtual void Delete_This(unsigned int);
	int m_refs;
};

class Bfme5RefPtr
{
public:
	~Bfme5RefPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Bfme5RefCounted *m_ptr;
};

struct Bfme5RefPairVal
{
	Bfme5RefPtr m_a;
	Bfme5RefPtr m_b;
	~Bfme5RefPairVal();
};

Bfme5RefPairVal::~Bfme5RefPairVal() {}

struct Bfme5RefPairValE
{
	Bfme5RefPtr m_a;
	Bfme5RefPtr m_b;
	~Bfme5RefPairValE();
};

Bfme5RefPairValE::~Bfme5RefPairValE() {}

class Rva004C6370
{
public:
	Rva004C6370(Bfme5RefPairVal s);
	Bfme5RefY *m_bfmeNode;
};

Rva004C6370::Rva004C6370(Bfme5RefPairVal s)
{
	Bfme5RefY *q = (Bfme5RefY *)operator new(16);
	Bfme5RefY *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfmeRva010FE034Vt;

		q->m_bfmeInner0 = (Bfme5RefY *)s.m_a.m_ptr;
		if (s.m_a.m_ptr)
			++((Bfme5RefY *)s.m_a.m_ptr)->m_bfmeRefCount;

		q->m_bfmeInner1 = (Bfme5RefY *)s.m_b.m_ptr;
		if (s.m_b.m_ptr)
			++((Bfme5RefY *)s.m_b.m_ptr)->m_bfmeRefCount;

		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;
	if (p)
		++p->m_bfmeRefCount;
}

class Rva004C64E0
{
public:
	Rva004C64E0(Bfme5RefPairValE s);
	Bfme5RefY *m_bfmeNode;
};

Rva004C64E0::Rva004C64E0(Bfme5RefPairValE s)
{
	Bfme5RefY *q = (Bfme5RefY *)operator new(16);
	Bfme5RefY *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfmeRva010FE04CVt;

		q->m_bfmeInner0 = (Bfme5RefY *)s.m_a.m_ptr;
		if (s.m_a.m_ptr)
			++((Bfme5RefY *)s.m_a.m_ptr)->m_bfmeRefCount;

		q->m_bfmeInner1 = (Bfme5RefY *)s.m_b.m_ptr;
		if (s.m_b.m_ptr)
			++((Bfme5RefY *)s.m_b.m_ptr)->m_bfmeRefCount;

		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;
	if (p)
		++p->m_bfmeRefCount;
}

class Rva004C6430
{
public:
	Rva004C6430(Bfme5RefPtr s);
	Bfme5RefX *m_bfmeNode;
};

Rva004C6430::Rva004C6430(Bfme5RefPtr s)
{
	Bfme5RefX *q = (Bfme5RefX *)operator new(12);
	Bfme5RefX *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfmeRva010FE040Vt;

		q->m_bfmeInner = (Bfme5RefX *)s.m_ptr;
		if (s.m_ptr)
			++((Bfme5RefX *)s.m_ptr)->m_bfmeRefCount;

		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;
	if (p)
		++p->m_bfmeRefCount;
}
