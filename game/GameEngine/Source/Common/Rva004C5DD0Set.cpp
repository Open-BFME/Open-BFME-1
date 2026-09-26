// cl: /O2 /Ob0

struct Rva004C5DD0Ref
{
	int m_00;
	int m_refs;
};

struct Rva004C5DD0Pair
{
	Rva004C5DD0Ref *a;
	Rva004C5DD0Ref *b;
};

class Rva004C5DD0
{
	Rva004C5DD0Ref *m_00;
	Rva004C5DD0Ref *m_04;

public:
	Rva004C5DD0 &set(const Rva004C5DD0Pair *p);
};

Rva004C5DD0 &Rva004C5DD0::set(const Rva004C5DD0Pair *p)
{
	Rva004C5DD0Ref *a = p->a;
	m_00 = a;
	if (a)
		a->m_refs++;
	Rva004C5DD0Ref *b = p->b;
	m_04 = b;
	if (b)
		b->m_refs++;
	return *this;
}
