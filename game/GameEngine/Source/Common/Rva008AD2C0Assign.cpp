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

class Rva008AD2C0
{
public:
	void assign(const Rva008AD2C0 &src);

private:
	Rva00891B80Block *m_block;
	int m_f4;
	int m_f8;
	int m_fC;
	int m_f10;
	int m_f14;
	int m_f18;
	int m_f1C;
};

void Rva008AD2C0::assign(const Rva008AD2C0 &src)
{
	m_fC = src.m_fC;
	m_f8 = src.m_f8;

	++src.m_block->m_ref;
	Rva00891B80Block *old = m_block;
	if (--old->m_ref == 0)
		g_rva01337A30AllocPair->m_free(old);
	m_block = src.m_block;

	m_f4 = src.m_f4;
	m_f10 = src.m_f10;
	if (src.m_f14 != -1)
		m_f14 = src.m_f14;
	if (src.m_f18 != -1)
		m_f18 = src.m_f18;
	if (src.m_f1C != -1)
		m_f1C = src.m_f1C;
}
