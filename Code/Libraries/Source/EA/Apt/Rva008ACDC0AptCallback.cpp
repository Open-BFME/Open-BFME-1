// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived Apt callback for retail RVA 0x008ACDC0. Its address is
// pushed to a constructor call at 0x008B22CE, as other native Apt callbacks
// are; no caller names it. The raw ABI is one cdecl context pointer in and
// g_bfmeFallbackDB out.

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI() : m_data(&g_bfmeDefaultString1284) { ++m_data->m_refCount; }
	BfmeStrVKI(const BfmeStrVKI &other) : m_data(other.m_data) { ++m_data->m_refCount; }
	BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	void bfmeSetVKI(const char *text);

	BfmeStringData3AF0 *m_data;
};

class Rva8CD130String : public BfmeStrVKI
{
public:
	Rva8CD130String() {}
	Rva8CD130String(const Rva8CD130String &other) : BfmeStrVKI(other) {}
	Rva8CD130String(const char *text) : BfmeStrVKI(text) {}
};

class Rva00896AF0Tracker
{
public:
	void rva00896AF0(Rva8CD130String *input, Rva8CD130String text);
};

class AptValue;

extern Rva00896AF0Tracker *g_bfmeTracker4310;
extern AptValue *g_bfmeFallbackDB;
extern void bfmeResetEVF(void *context, BfmeStrVKI *text);

AptValue *rva008ACDC0(void *context)
{
	// Reading the argument once into a local frees its incoming slot; retail
	// builds the "" temporary there instead of in a frame slot.
	void *resetContext = context;
	Rva8CD130String input;
	bfmeResetEVF(resetContext, &input);
	g_bfmeTracker4310->rva00896AF0(&Rva8CD130String(""), input);
	return g_bfmeFallbackDB;
}
