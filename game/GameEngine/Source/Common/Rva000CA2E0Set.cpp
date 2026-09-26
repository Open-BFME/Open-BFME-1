// cl: /O2 /Ob0

class Rva000CA2E0
{
	int m_00, m_04, m_08, m_0C, m_10, m_14;

public:
	Rva000CA2E0 &set(const Rva000CA2E0 *o);
};

Rva000CA2E0 &Rva000CA2E0::set(const Rva000CA2E0 *o)
{
	m_00 &= o->m_00;
	m_04 &= o->m_04;
	m_08 &= o->m_08;
	m_0C &= o->m_0C;
	m_10 &= o->m_10;
	m_14 &= o->m_14;
	return *this;
}
