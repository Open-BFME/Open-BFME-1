// cl: /O2 /Ob0

struct Rva0016A6D0Vec
{
	int x;
	int y;
	int z;
};

class Rva0016A6D0
{
	char pad[0x180];
	Rva0016A6D0Vec m_180;
	char pad2[0x31D - 0x18C];
	char m_31D;

public:
	void set(const Rva0016A6D0Vec *v);
};

void Rva0016A6D0::set(const Rva0016A6D0Vec *v)
{
	m_180 = *v;
	m_31D = 0;
}
