// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00403950Tail
{
	unsigned m_values[8];
};

class Rva00403950
{
	unsigned m_head;
	Rva00403950Tail m_tail;

public:
	Rva00403950 *copyFrom(const unsigned *head, const Rva00403950Tail *tail);
};

Rva00403950 *Rva00403950::copyFrom(const unsigned *head, const Rva00403950Tail *tail)
{
	m_head = *head;
	m_tail = *tail;
	return this;
}
