// cl: /O2 /Ob0

class Rva000E9200
{
	int m_00, m_04, m_08, m_0C, m_10, m_14;

public:
	Rva000E9200 &set(const Rva000E9200 *o);
};

Rva000E9200 &Rva000E9200::set(const Rva000E9200 *o)
{
	m_00 &= o->m_00;
	m_04 &= o->m_04;
	m_08 &= o->m_08;
	m_0C &= o->m_0C;
	m_10 &= o->m_10;
	m_14 &= o->m_14;
	return *this;
}
