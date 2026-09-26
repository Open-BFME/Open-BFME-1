// cl: /O2 /Ob0

struct Rva0016A3A0Vec
{
	int x;
	int y;
	int z;
};

class Rva0016A3A0
{
	char m_lead[0x5C];
	Rva0016A3A0Vec m_pos;
	char m_68;

public:
	void set(const Rva0016A3A0Vec *src);
};

void Rva0016A3A0::set(const Rva0016A3A0Vec *src)
{
	m_pos = *src;
	m_68 = 1;
}
