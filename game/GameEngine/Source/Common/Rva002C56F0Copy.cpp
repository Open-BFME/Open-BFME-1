// cl: /O2 /Ob0

struct Rva002C56F0Vec
{
	int x;
	int y;
	int z;
};

class Rva002C56F0
{
	char m_lead[0x0C];
	Rva002C56F0Vec m_pos;
	char m_18;

public:
	char copy(Rva002C56F0Vec *dst) const;
};

char Rva002C56F0::copy(Rva002C56F0Vec *dst) const
{
	*dst = m_pos;
	return m_18;
}
