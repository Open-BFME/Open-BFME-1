// cl: /O2 /Ob0

class Rva00918A00
{
	unsigned char m_earlier[0x40];
	unsigned int m_packed;

public:
	void setTopByte(unsigned int value);
};

void Rva00918A00::setTopByte(unsigned int value)
{
	reinterpret_cast<unsigned char *>(&m_packed)[3] = 0;
	m_packed |= value << 24;
}
