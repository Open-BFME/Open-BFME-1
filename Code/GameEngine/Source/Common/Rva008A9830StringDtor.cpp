// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00891B80Pool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva00891B80Pool *g_pool01337A30;

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
			g_pool01337A30->free(block);
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
