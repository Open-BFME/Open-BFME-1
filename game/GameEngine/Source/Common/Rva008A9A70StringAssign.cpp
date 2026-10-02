// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

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
		g_rva01337A30AllocPair->m_free(old);
	m_block = src.m_block;
}
