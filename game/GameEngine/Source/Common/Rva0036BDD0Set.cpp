// cl: /O2 /Ob0

struct Rva0036BDD0Vec
{
	int a;
	int b;
	int c;
};

class Rva0036BDD0
{
	Rva0036BDD0Vec m_00;
	Rva0036BDD0Vec m_0C;
	char m_18;

public:
	Rva0036BDD0 &set(const Rva0036BDD0Vec *p, const Rva0036BDD0Vec *q);
};

Rva0036BDD0 &Rva0036BDD0::set(const Rva0036BDD0Vec *p, const Rva0036BDD0Vec *q)
{
	m_00.a = p->a;
	m_00.b = p->b;
	m_00.c = p->c;
	m_0C.a = q->a;
	m_0C.b = q->b;
	m_0C.c = q->c;
	m_18 = 0;
	return *this;
}
