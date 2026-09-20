// cl: /O2

class Rva002BC840
{
	char m_lead[0x3F0];
	unsigned int m_bits;

public:
	void setBit(bool value);
};

void Rva002BC840::setBit(bool value)
{
	if (value)
		m_bits |= 0x40;
	else
		m_bits &= ~0x40u;
}
