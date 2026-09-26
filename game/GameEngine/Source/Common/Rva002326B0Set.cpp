// cl: /O2 /Ob0

struct Rva002326B0Vec
{
	int x;
	int y;
	int z;
};

class Rva002326B0
{
	int m_00;
	char m_04;
	char pad[0x130 - 5];
	Rva002326B0Vec m_130;
	char m_13C;

public:
	void set(const Rva002326B0Vec *v);
};

void Rva002326B0::set(const Rva002326B0Vec *v)
{
	m_130 = *v;
	m_13C = 1;
	m_04 = 1;
}
