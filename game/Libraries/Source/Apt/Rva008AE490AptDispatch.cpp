// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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

	Rva008AE600StringData *m_data;
};

class AptValue
{
public:
	int toInteger();
};

class Rva8CD130Value : public AptValue
{
	public:
	void getName(Rva8CD130String *name);
};

class BfmeSubmitter1283
{
	public:
	void bfmeSubmit1283(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		float *colors, int a9, int a10, int a11, int zero);
};

struct Rva008AE490SubmitContainer
{
	char m_padding00[0x24];
	BfmeSubmitter1283 m_submitter;
};

struct Rva008AE490Context
{
	char m_padding00[0x50];
	Rva008AE490SubmitContainer *m_submitContainer;
};

class BfmeNode1220
{
public:
	int bfmeTest1220(int *value, int zero);
};

class Rva008A18C0Holder
{
public:
	void rva008A18C0();
};

struct BfmeLookupString008ACCF0;
struct BfmeLookupObject008ACCF0;
// Root scratch: typed calls through existing generated ILT/body rows; no
// helper identity or new pin is claimed.
extern void d_008accf0(void);
extern void d_008a18c0(void);

extern Rva8CD130Value **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern AptValue *g_bfmeFallbackDB;
extern Rva008A18C0Holder *g_bfmeHolderBU;

int rva008AE490(void *context, int value)
{
	Rva8CD130Value *top = g_bfmeArr1233[g_bfmeCount1233 - 1];
	Rva8CD130Value *third = g_bfmeArr1233[g_bfmeCount1233 - 3];
	Rva8CD130Value *fourth;
	Rva8CD130Value *second = g_bfmeArr1233[g_bfmeCount1233 - 2];
	if (value >= 4)
		fourth = g_bfmeArr1233[g_bfmeCount1233 - 4];
	else
		fourth = 0;
	Rva8CD130String name;
	top->getName(&name);
	int lookup;
		{
			typedef int (__cdecl *LookupThunk)(void *, void *, unsigned char);
			union
			{
				void (*raw)(void);
				LookupThunk typed;
			} thunk;
			thunk.raw = d_008accf0;
			lookup = thunk.typed(context, &name, 1);
		}
	if (lookup != 0)
	{
		Rva8CD130String secondName;
		second->getName(&secondName);
		Rva008AE490SubmitContainer *submitContainer =
			reinterpret_cast<Rva008AE490Context *>(context)->m_submitContainer;
		submitContainer->m_submitter.bfmeSubmit1283(
			0, third->toInteger() + 0x4000, lookup,
			reinterpret_cast<int>(&secondName), reinterpret_cast<int>(context), 1, -1,
			0, 0, 0, 0, reinterpret_cast<int>(fourth));
		{
			typedef void (Rva008A18C0Holder::*HolderThunk)();
			union
			{
				void (*raw)(void);
				HolderThunk member;
			} thunk;
			thunk.raw = d_008a18c0;
			(g_bfmeHolderBU->*thunk.member)();
		}
		int result = reinterpret_cast<BfmeNode1220 *>(context)->bfmeTest1220(
			reinterpret_cast<int *>(&secondName), 0);
		return result;
	}
	return reinterpret_cast<int>(g_bfmeFallbackDB);
}
