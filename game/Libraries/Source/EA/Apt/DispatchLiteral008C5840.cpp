// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008C5840: aligned literal pair dispatch. A prefix uses the callback;
// a .swf suffix is removed before the tracker call; empty names are forwarded.
// By-value string layout and ABI are shared with the verified 008ACDC0 callback.

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
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

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
			g_rva01337A30AllocPair->free(data);
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

extern Rva00896AF0Tracker *g_bfmeTracker4310;

extern "C" unsigned strlen(const char *);
extern "C" int strncmp(const char *, const char *, unsigned);
#pragma intrinsic(strlen)
extern const char *rva012D5A08Prefix;
extern void (__cdecl *Callback01337858)(const char *, const char *);
__forceinline bool prefix(const char *text) { return strncmp(text, rva012D5A08Prefix, strlen(rva012D5A08Prefix)) == 0; }
void DispatchLiteral008C5840(void *, const char **cursor)
{
    const char **args = (const char **)(((unsigned)*cursor + 3) & ~3);
    *cursor = (const char *)(args + 2);
    if (prefix(args[0])) {
        unsigned prefixLength = strlen(rva012D5A08Prefix);
        Callback01337858(args[0] + prefixLength, args[1]);
        return;
    }
    char buffer[260];
    const char *src = args[0];
    unsigned delta = (unsigned)buffer - (unsigned)src;
    char c;
    do { c = *src; *(char *)(delta + (unsigned)src) = c; ++src; } while(c);
    unsigned length = strlen(buffer);
    char *end = buffer + length;
    if ((end[-1] == 'f' || end[-1] == 'F') &&
        (end[-2] == 'w' || end[-2] == 'W') &&
        (end[-3] == 's' || end[-3] == 'S') && end[-4] == '.') {
        const char *arg = args[1];
        end[-4] = 0;
        g_bfmeTracker4310->rva00896AF0(&Rva8CD130String(buffer), Rva8CD130String(arg));
    } else if (length == 0) {
        g_bfmeTracker4310->rva00896AF0(&Rva8CD130String(""), Rva8CD130String(args[1]));
    }
}
