// cl: /O2 /Ob0

struct Rva005B4230Pair
{
	int a;
	int b;
};

class Rva005B4230
{
	char m_pad[0x1C];
	char m_1C;
	int m_20;
	int m_24;

public:
	void set(const Rva005B4230Pair *p);
};

void Rva005B4230::set(const Rva005B4230Pair *p)
{
	m_20 = p->a;
	m_24 = p->b;
	m_1C = 1;
}
