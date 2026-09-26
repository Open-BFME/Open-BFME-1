// cl: /O2 /Ob0

struct Rva002AC0B0Global
{
	char m_lead[0x3C];
	unsigned m_frame;
};

Rva002AC0B0Global *g_rva002ac0b0;

class Rva002AC0B0
{
	char m_lead[0x28];
	unsigned m_value;

public:
	unsigned char cmp();
};

unsigned char Rva002AC0B0::cmp()
{
	return g_rva002ac0b0->m_frame >= m_value;
}
