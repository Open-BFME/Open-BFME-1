// cl: /DNDEBUG /MD /EHsc

class Rva003D5C40
{
public:
	void resetFlags();

private:
	unsigned char m_padding[0x1A];
	unsigned char m_first;
	unsigned char m_second;
};

void Rva003D5C40::resetFlags()
{
	m_first = 1;
	m_second = 0;
}
