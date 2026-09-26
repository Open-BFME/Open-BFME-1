// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00402700Half
{
	unsigned short m_count;
	int m_value;
	int m_pad0;
	int m_pad1;
};

struct Rva00402700Pair
{
	Rva00402700Half m_first;
	Rva00402700Half m_second;
};

bool Rva00402700(const Rva00402700Pair *p)
{
	int second = p->m_second.m_count == 2;
	int first = p->m_first.m_count == 2;
	return first == second;
}
