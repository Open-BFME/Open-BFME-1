// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived accumulator siblings at 0x000C89D0/0x000C89F0.

struct Rva000C89D0Object
{
	unsigned char m_prefix[0x10];
	unsigned int m_first;
	unsigned int m_second;

	void addFirst(unsigned int value);
	void addSecond(unsigned int value);
};

void Rva000C89D0Object::addFirst(unsigned int value)
{
	unsigned int result = m_first;
	result += value;
	m_first = result;
}

void Rva000C89D0Object::addSecond(unsigned int value)
{
	unsigned int result = m_second;
	result += value;
	m_second = result;
}
