// cl: /O2 /Ob0

struct Rva00249D50Dest
{
	char m_lead[0x234];
	float m_value;
};

struct Rva00249D50Owner
{
	Rva00249D50Dest *m_dest;
	char m_pad[0x18];
};

class Rva00249D50Inner
{
	char m_lead[0xD0];
	int m_value;

public:
	float mul();
};

float Rva00249D50Inner::mul()
{
	Rva00249D50Owner *owner = (Rva00249D50Owner *)((char *)this - 0x1C);
	return (float)m_value * owner->m_dest->m_value;
}
