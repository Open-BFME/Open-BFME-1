// cl: /O2 /Ob0

struct Rva004B0280Obj
{
	int m_00;
	int m_04;
};

class Rva004B0280
{
	int m_00;
	Rva004B0280Obj *m_04;

public:
	Rva004B0280 *set(const Rva004B0280 *src);
};

Rva004B0280 *Rva004B0280::set(const Rva004B0280 *src)
{
	m_00 = src->m_00;
	m_04 = src->m_04;
	if (m_04)
		m_04->m_04++;
	return this;
}
