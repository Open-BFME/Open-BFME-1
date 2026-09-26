// cl: /O2 /Ob0

struct Rva003CC720Pair { int a, b; };

class Rva003CC720
{
	int m_00, m_04, m_08, m_0C;
	int z[8];
	int m_30, m_34;
	char m_38, m_39;

public:
	Rva003CC720 &set(int a, const Rva003CC720Pair *p);
};

Rva003CC720 &Rva003CC720::set(int a, const Rva003CC720Pair *p)
{
	m_00 = p->a;
	m_04 = p->b;
	m_08 = a;
	m_0C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_39 = 8;
	int *q = z;
	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
	q[3] = 0;
	q[4] = 0;
	q[5] = 0;
	q[6] = 0;
	q[7] = 0;
	return *this;
}
