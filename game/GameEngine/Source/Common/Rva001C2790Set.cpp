// cl: /O2 /Ob0

class Rva001C2790
{
	int m_00, m_04, m_08, m_0C, m_10, m_14, m_18, m_1C, m_20, m_24;

public:
	Rva001C2790 &set(const Rva001C2790 *o);
};

Rva001C2790 &Rva001C2790::set(const Rva001C2790 *o)
{
	m_00 &= o->m_00;
	m_04 &= o->m_04;
	m_08 &= o->m_08;
	m_0C &= o->m_0C;
	m_10 &= o->m_10;
	m_14 &= o->m_14;
	m_18 &= o->m_18;
	m_1C &= o->m_1C;
	m_20 &= o->m_20;
	m_24 &= o->m_24;
	return *this;
}
