// cl: /O2 /Ob0

class Rva005A6560
{
	int m_00;
	char m_pad[8];
	int m_0c;
	int m_10;
	unsigned char m_14;

public:
	Rva005A6560 *reset();
};

Rva005A6560 *Rva005A6560::reset()
{
	m_00 = 0;
	m_0c = 0;
	m_10 = 0;
	m_14 &= 0xFE;
	return this;
}
