// cl: /O2 /Ob0

struct Rva00220780Vec
{
	int x;
	int y;
	int z;
};

class Rva00220780
{
	char pad[0x78];
	Rva00220780Vec m_78;
	char m_84;

public:
	void set(const Rva00220780Vec *v);
};

void Rva00220780::set(const Rva00220780Vec *v)
{
	m_78 = *v;
	m_84 = 1;
}
