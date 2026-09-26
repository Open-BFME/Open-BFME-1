// cl: /O2 /Ob0

struct Rva000C8D80Vec
{
	int x;
	int y;
	int z;
};

class Rva000C8D80
{
	char m_lead[0x34];
	Rva000C8D80Vec m_pos;
	char m_40;

public:
	char copy(Rva000C8D80Vec *dst) const;
};

char Rva000C8D80::copy(Rva000C8D80Vec *dst) const
{
	*dst = m_pos;
	return m_40;
}
