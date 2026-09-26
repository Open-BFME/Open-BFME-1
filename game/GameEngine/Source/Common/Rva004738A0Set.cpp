// cl: /O2 /Ob0

struct Rva004738A0Obj
{
	int m_00;
	int m_04;
};

class Rva004738A0
{
	int m_00;
	Rva004738A0Obj *m_04;

public:
	Rva004738A0 *set(const int *a, Rva004738A0Obj *const *b);
};

Rva004738A0 *Rva004738A0::set(const int *a, Rva004738A0Obj *const *b)
{
	m_00 = *a;
	m_04 = *b;
	if (m_04)
		m_04->m_04++;
	return this;
}
