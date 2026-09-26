class Rva006E1930Object
{
public:
	void clear();

private:
	unsigned char m_prefix[0x38];
	unsigned int m_low;
	unsigned int m_middle;
	unsigned int m_high;
};

void Rva006E1930Object::clear()
{
	m_high = 0;
	m_middle = 0;
	m_low = 0;
}
