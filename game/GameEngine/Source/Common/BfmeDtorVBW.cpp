// cl: /EHsc

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class BfmeString3AF0
{
public:
	~BfmeString3AF0()
	{
		BfmeStringData3AF0 *data = m_data;
		--data->m_refCount;
		if (data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData3AF0 *m_data;
};

class Rva00893030Manager
{
public:
	void remove(void *key);
};

extern Rva00893030Manager *g_rva00893030Manager;

class Rva008A25C0Object
{
public:
	void run(void *value);
};

extern void (__cdecl *g_rva0133784C)(void *value);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA();

private:
	int m_refCount;
	BfmeString3AF0 m_string;
	int m_kind;
	void *m_argument;
	Rva008A25C0Object *m_object;
	void *m_buffer;
};

BfmeDropObjectA::~BfmeDropObjectA()
{
	g_rva00893030Manager->remove(this);

	if (m_kind == 3 || m_kind == 4 || m_kind == 5)
	{
		((Rva008A25C0Object *)((char *)m_object + 8))->run(m_argument);
		g_rva0133784C(m_buffer);
	}
}
