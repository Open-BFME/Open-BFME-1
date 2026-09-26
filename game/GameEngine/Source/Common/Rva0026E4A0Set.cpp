// cl: /O2 /Ob0

class Rva0026E4A0
{
	Rva0026E4A0 *m_00;
	Rva0026E4A0 *m_04;
	Rva0026E4A0 *m_08;

public:
	Rva0026E4A0 &set(Rva0026E4A0 *p);
};

Rva0026E4A0 &Rva0026E4A0::set(Rva0026E4A0 *p)
{
	m_08 = p;
	m_00 = p;
	if (p)
		p->m_04 = this;
	return *this;
}
