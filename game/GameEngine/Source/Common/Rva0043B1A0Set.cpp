// cl: /O2 /Ob0

struct Rva0043B1A0Pair
{
	int a;
	int b;
};

class Rva0043B1A0
{
	char pad[0x54C];
	int m_54C;
	int m_550;

public:
	void set(const Rva0043B1A0Pair *p);
};

void Rva0043B1A0::set(const Rva0043B1A0Pair *p)
{
	if (p)
	{
		m_54C = p->a;
		m_550 = p->b;
	}
}
