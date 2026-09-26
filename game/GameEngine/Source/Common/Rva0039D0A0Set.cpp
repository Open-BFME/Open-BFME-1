// cl: /O2 /Ob0

class Rva0039D0A0
{
	int m_00, m_04, m_08, m_0C, m_10, m_14;

public:
	Rva0039D0A0 &set(const Rva0039D0A0 *o);
};

Rva0039D0A0 &Rva0039D0A0::set(const Rva0039D0A0 *o)
{
	m_00 |= o->m_00;
	m_04 |= o->m_04;
	m_08 |= o->m_08;
	m_0C |= o->m_0C;
	m_10 |= o->m_10;
	m_14 |= o->m_14;
	return *this;
}
