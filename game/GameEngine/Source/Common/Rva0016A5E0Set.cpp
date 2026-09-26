// cl: /O2 /Ob0

class Rva0016A5E0
{
	char pad[0x40];
	int m_40;

public:
	Rva0016A5E0 &set(int bit, unsigned char on);
};

Rva0016A5E0 &Rva0016A5E0::set(int bit, unsigned char on)
{
	if (on)
		m_40 |= (1 << bit);
	else
		m_40 &= ~(1 << bit);
	return *this;
}
