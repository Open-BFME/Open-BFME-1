// ?rva00895A00@Rva00893030Manager@@QAE?AVRefHandle008958D0@@PAVBfmeStrVKI@@@Z
// partial score=0.2044 date=2026-10-03
// cl: /O2 /DNDEBUG /MD /EHsc

struct BfmeHdrVKI
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_data[1];
};

struct BfmeStringPoolVKI
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPoolVKI *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}
	void __declspec(nothrow) bfmeSetVKI(const char *text);
	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeHdrVKI *m_data;
};

class BfmeDropObjectA;

class RefHandle008958D0
{
public:
	RefHandle008958D0();
 RefHandle008958D0(BfmeDropObjectA *p);
	RefHandle008958D0(const RefHandle008958D0 &other);
	~RefHandle008958D0();

	BfmeDropObjectA *m_bfmeAEVB;
};

struct BfmeStringDataEVB
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_data[1];
};

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
extern void (*TheBfmeFree)(void *value, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA();
 void *operator new(unsigned int n) { return Rva008C5D70Alloc(n); }
 BfmeDropObjectA(BfmeStrVKI *name) { m_refCount=0; m_string=reinterpret_cast<BfmeStringDataEVB *>(name->m_data); ++m_string->m_refCount; m_kind=1; m_argument=0; m_object=0; m_buffer=0; }

	void operator delete(void *value, unsigned int bytes)
	{
		TheBfmeFree(value, bytes);
	}

	int m_refCount;
	BfmeStringDataEVB *m_string;
	int m_kind;
	void *m_argument;
	void *m_object;
	void *m_buffer;
};


__forceinline RefHandle008958D0::~RefHandle008958D0()
{
	BfmeDropObjectA *p=m_bfmeAEVB;
 if(p && --p->m_refCount == 0) delete p;
}

__forceinline RefHandle008958D0::RefHandle008958D0()
	: m_bfmeAEVB(0)
{
}

__forceinline RefHandle008958D0::RefHandle008958D0(const RefHandle008958D0 &other)
	: m_bfmeAEVB(other.m_bfmeAEVB)
{
	if (m_bfmeAEVB != 0)
		++m_bfmeAEVB->m_refCount;
}

struct BfmeDropNodeEVB
{
	BfmeDropObjectA *m_object;
	BfmeDropNodeEVB *m_next;
};

class Rva00893030Manager
{
public:
	RefHandle008958D0 find008958D0(BfmeStrVKI *name);
	RefHandle008958D0 rva00895A00(BfmeStrVKI *name);

	BfmeDropNodeEVB *m_head;
};


inline RefHandle008958D0::RefHandle008958D0(BfmeDropObjectA *p) : m_bfmeAEVB(p) { if(p) ++p->m_refCount; }
RefHandle008958D0 Rva00893030Manager::rva00895A00(BfmeStrVKI *name)
{
 RefHandle008958D0 found = find008958D0(name);
 if(found.m_bfmeAEVB) return found;
 BfmeDropObjectA *value = new BfmeDropObjectA(name);
 RefHandle008958D0 made(value);
 BfmeDropNodeEVB *node=static_cast<BfmeDropNodeEVB *>(Rva008C5D70Alloc(8));
 if(node) { node->m_object=value; node->m_next=0; } else node=0;
 node->m_next=m_head; m_head=node;
 return made;
}
