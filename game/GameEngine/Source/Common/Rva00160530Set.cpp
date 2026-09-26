// cl: /O2 /Ob0

class Rva00160530
{
	Rva00160530 *m_00;
	Rva00160530 *m_04;
	Rva00160530 *m_08;

public:
	void set(Rva00160530 **p);
};

void Rva00160530::set(Rva00160530 **p)
{
	m_08 = *p;
	if (*p)
		(*p)->m_04 = this;
	*p = this;
}
