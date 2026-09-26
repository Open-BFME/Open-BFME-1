// cl: /O2 /Ob0

struct Rva004B0440Obj
{
	int m_00;
	int m_04;
};

class Rva004B0440
{
	int m_00;
	Rva004B0440Obj *m_04;

public:
	Rva004B0440 *set(const int *a, Rva004B0440Obj *const *b);
};

Rva004B0440 *Rva004B0440::set(const int *a, Rva004B0440Obj *const *b)
{
	m_00 = *a;
	m_04 = *b;
	if (m_04)
		m_04->m_04++;
	return this;
}
