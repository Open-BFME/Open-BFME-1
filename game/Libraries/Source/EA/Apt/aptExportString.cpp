// ?aptExportString@@YAXPBDPAD@Z
// cl: /O2 /DNDEBUG /MD /EHsc

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

class Rva00899770
{
public:
	void exportString(char *out);
};

// Defining spelling: the global is a struct-typed object (?Rva008AE770TheStack@@3U...).
// The body retail calls for createString is at 0x008cc940 and is linked as a
// cdecl void() body, so the thiscall-with-6-arguments shape is recovered through
// a member-pointer call instead of a renamed declaration.
struct Rva008AE770Stack
{
};

extern Rva008AE770Stack Rva008AE770TheStack;
class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int value);

// Body at 0x008cc940: ?d_008cc940@@YAXXZ.
extern void d_008cc940();

void aptExportString(const char *name, char *out)
{
	typedef Rva00899770 *(Rva008AE770Stack::*Fn)(void *value, int unused,
		BfmeStrVKI *strName, int one, int another, int zero);
	union { void (*fn)(); Fn call; } u = { d_008cc940 };
	BfmeStrVKI value(name);
	Rva00899770 *result = (Rva008AE770TheStack.*u.call)(
		Rva008930C0AptLookup(0), 0, &value, 1, 1, 0);
	result->exportString(out);
}
