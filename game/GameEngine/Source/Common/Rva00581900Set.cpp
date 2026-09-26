// cl: /O2 /Ob0

struct Rva00581900Obj
{
	int m_00;
	unsigned m_04;
};

class Rva00581900
{
	Rva00581900Obj *m_slot[2];

public:
	void set(Rva00581900Obj *p);
};

void Rva00581900::set(Rva00581900Obj *p)
{
	if (p->m_04 < 2)
	{
		if (m_slot[p->m_04] == 0)
			m_slot[p->m_04] = p;
	}
}
