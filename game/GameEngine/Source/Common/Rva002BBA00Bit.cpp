// cl: /O2 /Ob0

class Rva002BBA00
{
	char pad[0x3F0];
	unsigned m_3F0;

public:
	void set(unsigned bit, unsigned char on);
};

void Rva002BBA00::set(unsigned bit, unsigned char on)
{
	if (on)
		m_3F0 |= (1u << bit);
	else
		m_3F0 &= ~(1u << bit);
}
