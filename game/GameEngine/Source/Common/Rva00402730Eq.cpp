// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00402730Half
{
	unsigned short m_count;
	int m_value;
	int m_pad0;
	int m_pad1;
};

struct Rva00402730Pair
{
	Rva00402730Half m_first;
	Rva00402730Half m_second;
};

int Rva00402730(const Rva00402730Pair *p)
{
	return p->m_first.m_count == p->m_second.m_count
		&& p->m_first.m_value == p->m_second.m_value;
}
