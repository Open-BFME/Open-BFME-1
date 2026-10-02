struct BfmeStringBlock1226
{
	unsigned short m_refs;
};

struct BfmeStringPool1226
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringBlock1226 g_bfmeDefaultString1284;
extern BfmeStringPool1226 *g_bfmeStringPool1284;
extern "C" void (__cdecl *g_bfmeCallback1226)(const void *, const void *);

class BfmeString1226
{
public:
	BfmeString1226()
	{
		++g_bfmeDefaultString1284.m_refs;
		m_block = &g_bfmeDefaultString1284;
	}

	~BfmeString1226()
	{
		BfmeStringBlock1226 *block = m_block;
		if (--block->m_refs == 0)
			g_bfmeStringPool1284->free(block);
	}

	BfmeStringBlock1226 *m_block;
};

class Rva8CD130String;

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *out);
	virtual void slot00();
	virtual void release();
};

class BfmeR1226
{
public:
	void bfmeLine1226(char *text);

	char m_padding00[0x7c];
	Rva8CD130Value *m_pending;
};

void BfmeR1226::bfmeLine1226(char *text)
{
	Rva8CD130Value *pending = m_pending;
	if (pending != 0)
	{
		BfmeString1226 name;
		pending->getName((Rva8CD130String *)&name);
		g_bfmeCallback1226("<WARNING> Actionscript un-caught exception encountered during \"%s\"\n", text);
		g_bfmeCallback1226("<WARNING> Actionscript error message: \"%s\"\n",
			(char *)name.m_block + 8);
		m_pending->release();
		m_pending = 0;
	}
}
