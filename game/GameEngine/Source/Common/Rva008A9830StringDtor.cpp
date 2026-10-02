// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeStringPool3AF0
{
	void *m_alloc;
	void (__cdecl *m_free)(void *);
};

extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

struct Rva00891B80Block
{
	unsigned short m_ref;
};

class Rva008A9830String
{
public:
	~Rva008A9830String()
	{
		Rva00891B80Block *block = m_block;
		if (--block->m_ref == 0)
			g_rva01337A30AllocPair->m_free(block);
	}

private:
	Rva00891B80Block *m_block;
};

class Rva008A9830Base
{
public:
	virtual ~Rva008A9830Base() {}

private:
	unsigned int m_flags;
};

class Rva008A9830 : public Rva008A9830Base
{
public:
	virtual ~Rva008A9830();

private:
	Rva008A9830String m_string;
	int m_extra;
};

Rva008A9830::~Rva008A9830()
{
}
