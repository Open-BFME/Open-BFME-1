// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00891B80Block
{
	unsigned short m_ref;
};

class Rva00891B70Copy
{
	Rva00891B80Block *m_block;

public:
	Rva00891B70Copy(const Rva00891B70Copy &other);
};

Rva00891B70Copy::Rva00891B70Copy(const Rva00891B70Copy &other)
	: m_block(other.m_block)
{
	++m_block->m_ref;
}
