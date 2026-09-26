// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived Apt callback for retail RVA 0x008AE600.  No named direct
// caller or vtable identifies this body; the raw ABI is one cdecl context
// pointer in and an Apt value pointer out.

struct Rva008AE600StringData
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct Rva008AE600StringPool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva008AE600StringData g_bfmeDefaultString1284;
extern Rva008AE600StringPool *g_bfmeStringPool1284;

class BfmeStrVKI;

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		++g_bfmeDefaultString1284.m_refCount;
		m_data = &g_bfmeDefaultString1284;
	}

	Rva8CD130String(const Rva8CD130String &other)
	{
		m_data = other.m_data;
		++m_data->m_refCount;
	}

	~Rva8CD130String()
	{
		Rva008AE600StringData *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	Rva8CD130String &operator=(const Rva8CD130String &other)
	{
		++other.m_data->m_refCount;
		Rva008AE600StringData *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = other.m_data;
		return *this;
	}

	// Neutral name: retail calls the two-int member at 0x0089EEF0.
	void rva0089EEF0(unsigned start, unsigned length);

	Rva008AE600StringData *m_data;
};

struct Rva8CD130Value
{
public:
	// This exact decorated helper is already pinned to retail 0x008985C0.
	void getName(Rva8CD130String *name);
};

class Rva00896AF0Tracker
{
public:
	// Neutral name: retail calls this thiscall helper at 0x00896AF0 and it
	// returns with eight bytes of stack arguments removed.
	void rva00896AF0(Rva8CD130String *input, Rva8CD130String text);
};

extern Rva8CD130Value **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern Rva00896AF0Tracker *g_bfmeTracker4310;
extern Rva8CD130Value *g_bfmeFallbackDB;
extern void bfmeResetEVF(void *context, BfmeStrVKI *text);

Rva8CD130Value *rva008AE600(void *context)
{
	Rva8CD130Value *value = g_bfmeArr1233[g_bfmeCount1233 - 1];
	Rva8CD130String name;
	value->getName(&name);
	int length = name.m_data->m_length;
	if (length != 0)
	{
		char last = *(const char *)(length + (unsigned int)name.m_data + 7);
		if (last != 'f' && last != 'F')
			goto cleanup;
		if (*(const char *)(length + (unsigned int)name.m_data + 6) != 'w' &&
			last != 'W')
			goto cleanup;
		if (*(const char *)(length + (unsigned int)name.m_data + 5) != 's' &&
			last != 'S')
			goto cleanup;
		if (*(const char *)(length + (unsigned int)name.m_data + 4) != '.')
			goto cleanup;
	}

	{
		Rva8CD130String stem;
		stem = name;
		if (length >= 4)
			stem.rva0089EEF0(length - 4, 4);
		bfmeResetEVF(context, reinterpret_cast<BfmeStrVKI *>(&name));
		g_bfmeTracker4310->rva00896AF0(&stem, name);
	}

cleanup:
	return g_bfmeFallbackDB;
}
