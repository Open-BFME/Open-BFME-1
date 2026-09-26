// cl: /O2 /Ob0

class HoldRva002BC020
{
public:
	char m_lead[0x3C];
	int m_value;
};

HoldRva002BC020 *g_rva002BC020;

class Rva002BC020
{
	char m_lead[0x24];
	int m_field;

public:
	int apply();
};

int Rva002BC020::apply()
{
	m_field = g_rva002BC020->m_value + 2;
	return 0;
}
