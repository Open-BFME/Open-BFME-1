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

class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *value, int unused, BfmeStrVKI *name,
		int one, int another, int zero);
};

extern Rva008AE770Stack Rva008AE770TheStack;
class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int value);

#pragma comment(linker, "/alternatename:?createString@Rva008AE770Stack@@QAEPAVRva00899770@@PAXHPAVBfmeStrVKI@@HHH@Z=?d_008cc940@@YAXXZ")

void aptExportString(const char *name, char *out)
{
	BfmeStrVKI value(name);
	Rva00899770 *result = Rva008AE770TheStack.createString(
		Rva008930C0AptLookup(0), 0, &value, 1, 1, 0);
	result->exportString(out);
}
