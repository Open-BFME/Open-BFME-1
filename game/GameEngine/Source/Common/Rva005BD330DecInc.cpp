// cl: /O2 /Ob0

struct Rva005BD330Pair
{
	int m_a;
	int m_b;
};

int rva005bd330(Rva005BD330Pair *p)
{
	--p->m_b;
	return p->m_a++;
}
