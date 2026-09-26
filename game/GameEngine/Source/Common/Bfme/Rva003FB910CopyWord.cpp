// cl: /DNDEBUG /MD /EHsc

class Rva003FB910
{
public:
	void copyWord();

private:
	unsigned char m_padding[0x08];
	unsigned short m_value;
	unsigned short m_source;
};

void Rva003FB910::copyWord()
{
	m_value = m_source;
}
