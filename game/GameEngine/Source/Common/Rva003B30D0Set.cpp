// cl: /O2 /Ob0

class Rva003B30D0
{
	int m_00;
	int m_04;
	char m_08;
	int m_0C;

public:
	Rva003B30D0 &set(const Rva003B30D0 *p);
};

Rva003B30D0 &Rva003B30D0::set(const Rva003B30D0 *p)
{
	m_04 = p->m_04;
	m_08 = p->m_08;
	m_0C = p->m_0C;
	return *this;
}
