struct BfmeStringData3AF0
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

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPoolVKI *g_bfmeStringPool1284;

class BfmeStrEAW
{
public:
	BfmeStrEAW()
	{
		g_bfmeDefaultString1284.m_refCount++;

		m_data = &g_bfmeDefaultString1284;
	}
	~BfmeStrEAW()
	{
		BfmeStringData3AF0 *data = m_data;

		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}
	const char *strEAW() const
	{
		return (const char *)m_data + 8;
	}

	BfmeStringData3AF0 *m_data;
};

class BfmeHostEAW
{
public:
	void bfmeFillEAW(BfmeStrEAW *out);
};

extern void (__cdecl *g_bfmeCompareEAW)(const char *a, const char *b);

char __stdcall bfmeReportEAW(void *unused, BfmeStrEAW *other, BfmeHostEAW *host)
{
	BfmeStrEAW text;

	host->bfmeFillEAW(&text);

	g_bfmeCompareEAW(other->strEAW(), text.strEAW());

	return 1;
}
