// cl: /O2 /Ob0

struct Rva00468520Obj
{
	int m_00;
	int m_04;
};

class Rva00468520
{
	Rva00468520Obj *m_00;
	int m_04;

public:
	Rva00468520 *set(const Rva00468520 *src);
};

Rva00468520 *Rva00468520::set(const Rva00468520 *src)
{
	m_00 = src->m_00;
	if (m_00)
		m_00->m_04++;
	m_04 = src->m_04;
	return this;
}
