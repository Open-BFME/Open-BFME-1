struct BfmeHdrVKI
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPoolVKI
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

// The pool pointer at VA 0x01337A30 has one canonical global; this TU keeps its
// own view type of the {void *unused; void (*free)(void *);} table and casts at
// the use.
struct BfmeStringPool3AF0;

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

static __forceinline BfmeStringPoolVKI *localPool()
{
	return (BfmeStringPoolVKI *)g_rva01337A30AllocPair;
}

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
			localPool()->free(data);
	}

	BfmeHdrVKI *m_data;
};

struct BfmeResultEVB
{
	~BfmeResultEVB();

	void *m_bfmeAEVB;
	void *m_bfmeBEVB;
	void *m_bfmeCEVB;
	void *m_bfmeDEVB;
};

class Rva00893030Manager
{
public:
	BfmeResultEVB bfmeBuildEVB(BfmeStrVKI *name);
};

extern Rva00893030Manager *g_rva00893030Manager;

BfmeResultEVB bfmeMakeEVB(const char *name)
{
	BfmeStrVKI value(name);

	return g_rva00893030Manager->bfmeBuildEVB(&value);
}
