// ??1Rva008BE450SizedDeleting@@UAE@XZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeStringData1286
{
	unsigned short m_refCount;
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeStringPool1286
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringPool1286 *g_bfmeStringPool1284;
extern char g_bfmeDerived1286Vtable;
extern char g_bfmeSpecialBlock1286;
extern void (__cdecl *g_bfmeFreePair1286)(void *storage, int count);
extern void (__cdecl *g_bfmeFreeSingle1286)(void *storage);
extern char g_bfmeBase1285Vtable;
extern void (__cdecl *TheBfmeFree)(void *storage, unsigned int size);

class BfmeString1286
{
public:
	~BfmeString1286()
	{
		BfmeStringData1286 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

private:
	BfmeStringData1286 *m_data;
};

class Gen_uwm_008ad330
{
public:
	~Gen_uwm_008ad330();

private:
	BfmeStringData1286 *m_data;
};

class BfmeChildB
{
public:
	~BfmeChildB();

	void operator delete(void *storage, unsigned int size)
	{
		TheBfmeFree(storage, size);
	}

private:
	char m_padding00[0x10];
};

struct BfmeNestedBlock1286
{
	char m_padding00[0x34];
	void *m_owned34;
	void *m_owned38;
};

class BfmeBase1286
{
public:
	virtual ~BfmeBase1286()
	{
		delete m_child;
	}

protected:
	char m_padding04[0x0c - 0x04];
	BfmeNestedBlock1286 *m_nested;
	BfmeChildB *m_child;
	char m_padding14[0x18 - 0x14];
};

class Rva008BE450SizedDeleting : public BfmeBase1286
{
public:
	virtual ~Rva008BE450SizedDeleting();

private:
	BfmeString1286 m_string18;
	BfmeString1286 m_string1c;
	void *m_special20;
	int m_value24;
	char m_padding28[0x60 - 0x28];
	int m_value60;
	int m_value64;
	Gen_uwm_008ad330 *volatile m_heapString68;
	char m_padding6c[0x74 - 0x6c];
	unsigned char m_flags74;
};

Rva008BE450SizedDeleting::~Rva008BE450SizedDeleting()
{
	Gen_uwm_008ad330 *heapString = m_heapString68;
	m_value24 = 0;
	m_value64 = 0;
	m_value60 = 0;
	if (heapString != 0) {
		delete heapString;
		m_heapString68 = 0;
	}
	if (m_special20 != 0 && m_special20 != &g_bfmeSpecialBlock1286) {
		g_bfmeFreePair1286(m_special20, 2);
		m_special20 = 0;
	}
	if ((m_flags74 & 1) != 0) {
		if (m_nested->m_owned34 != 0)
			g_bfmeFreeSingle1286(m_nested->m_owned34);
		if (m_nested->m_owned38 != 0)
			g_bfmeFreeSingle1286(m_nested->m_owned38);
		if (m_nested != 0)
			g_bfmeFreeSingle1286(m_nested);
	}
}
