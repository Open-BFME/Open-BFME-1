// cl: /O2 /Ob0

class Rva001C28F0
{
	int m_00;
	int m_04;
	int m_08;

public:
	Rva001C28F0 &set(const Rva001C28F0 *o);
};

Rva001C28F0 &Rva001C28F0::set(const Rva001C28F0 *o)
{
	m_00 |= o->m_00;
	m_04 |= o->m_04;
	m_08 |= o->m_08;
	return *this;
}
