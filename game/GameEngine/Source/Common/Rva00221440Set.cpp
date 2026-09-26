// cl: /O2 /Ob0

struct Rva00221440Ten
{
	int x[10];
};

class Rva00221440
{
	int m_00;
	Rva00221440Ten m_04;

public:
	Rva00221440 &set(const Rva00221440 *p);
};

Rva00221440 &Rva00221440::set(const Rva00221440 *p)
{
	m_00 = p->m_00;
	m_04 = p->m_04;
	return *this;
}
