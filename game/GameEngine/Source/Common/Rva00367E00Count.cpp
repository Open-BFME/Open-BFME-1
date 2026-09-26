// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00367E00Pair
{
	unsigned key;
	unsigned pad;
};

class Rva00367E00
{
	Rva00367E00Pair *m_begin;
	Rva00367E00Pair *m_end;

public:
	int count(unsigned key) const;
};

int Rva00367E00::count(unsigned key) const
{
	int n = 0;
	for (Rva00367E00Pair *p = m_begin; p != m_end; ++p)
	{
		if (p->key == key)
			n++;
	}
	return n;
}
