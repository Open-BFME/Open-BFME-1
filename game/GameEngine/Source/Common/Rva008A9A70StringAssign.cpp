// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

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

struct Rva008A9A70Str
{
	Rva00891B80Block *m_block;
};

class Rva008A9A70
{
public:
	void set(const Rva008A9A70Str &src);

private:
	int m_pad0;
	int m_pad4;
	Rva00891B80Block *m_block;
};

void Rva008A9A70::set(const Rva008A9A70Str &src)
{
	++src.m_block->m_ref;
	Rva00891B80Block *old = m_block;
	if (--old->m_ref == 0)
		g_pool01337A30->free(old);
	m_block = src.m_block;
}
