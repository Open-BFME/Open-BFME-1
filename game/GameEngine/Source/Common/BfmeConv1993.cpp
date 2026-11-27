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

// The existing builder and its returned-object unwind action establish one
// counted pointer, not the old sixteen-byte return stand-in. Reuse the
// existing address-qualified owning-handle identity and declared API.
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

class Rva00893030Manager
{
public:
	RefHandle008958D0 rva00895A00(BfmeStrVKI *name);
};

extern Rva00893030Manager *g_rva00893030Manager;

RefHandle008958D0 bfmeMakeEVB(const char *name)
{
	BfmeStrVKI value(name);

	return g_rva00893030Manager->rva00895A00(&value);
}
