// cl: /DNDEBUG /MD /EHsc

class Rva007E4790
{
public:
	unsigned char isAtOrAfterPrevious() const;

private:
	unsigned char m_padding[0x3C];
	int m_current;
	unsigned char m_gap40[0x08];
	int m_previous;
};

unsigned char Rva007E4790::isAtOrAfterPrevious() const
{
	return m_previous >= m_current - 1;
}
