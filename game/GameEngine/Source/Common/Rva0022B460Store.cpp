// cl: /O2 /Ob0

struct Rva0022B460Dest
{
	char m_lead[0x234];
	float m_value;
};

struct Rva0022B460Owner
{
	Rva0022B460Dest *m_dest;
	char m_pad[0x18];
};

class Rva0022B460Inner
{
	char m_lead[0xC8];
	int m_value;

public:
	float mul();
};

float Rva0022B460Inner::mul()
{
	Rva0022B460Owner *owner = (Rva0022B460Owner *)((char *)this - 0x1C);
	return (float)m_value * owner->m_dest->m_value;
}
