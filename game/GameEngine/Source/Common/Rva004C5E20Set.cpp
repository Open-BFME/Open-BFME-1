// cl: /O2 /Ob0

struct Rva004C5E20Ref
{
	int m_00;
	int m_refs;
};

struct Rva004C5E20Pair
{
	Rva004C5E20Ref *a;
	Rva004C5E20Ref *b;
};

class Rva004C5E20
{
	Rva004C5E20Ref *m_00;
	Rva004C5E20Ref *m_04;

public:
	Rva004C5E20 &set(const Rva004C5E20Pair *p);
};

Rva004C5E20 &Rva004C5E20::set(const Rva004C5E20Pair *p)
{
	Rva004C5E20Ref *a = p->a;
	m_00 = a;
	if (a)
		a->m_refs++;
	Rva004C5E20Ref *b = p->b;
	m_04 = b;
	if (b)
		b->m_refs++;
	return *this;
}
