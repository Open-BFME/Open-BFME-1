class Rva003C4BA0Object
{
public:
	void clearTriple();

private:
	unsigned char m_prefix[0x1c];
	unsigned int m_first;
	unsigned int m_second;
	unsigned int m_third;
};

void Rva003C4BA0Object::clearTriple()
{
	m_first = 0;
	m_second = 0;
	m_third = 0;
}
