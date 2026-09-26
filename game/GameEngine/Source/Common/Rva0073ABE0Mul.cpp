// cl: /O2 /Ob0

class Rva0073ABE0
{
	char m_lead[0x3C];
	float m_b;
	char m_mid[0xA8 - 0x40];
	float m_a;

public:
	float get();
};

float Rva0073ABE0::get()
{
	return m_a * m_b;
}
