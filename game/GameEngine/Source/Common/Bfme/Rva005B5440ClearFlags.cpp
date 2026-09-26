// cl: /DNDEBUG /MD /EHsc

class Rva005B5440
{
public:
	void clearFlags();

private:
	unsigned char m_unmodelled_000[0x38];
	unsigned char m_flag0;
	unsigned char m_flag1;
	unsigned char m_unmodelled_03A;
	unsigned char m_flag2;
	unsigned char m_flag3;
	unsigned char m_unmodelled_03D[0x117];
	unsigned char m_tail0;
	unsigned char m_tail1;
	unsigned char m_tail2;
	unsigned char m_tail3;
};

void Rva005B5440::clearFlags()
{
	m_flag0 = 0;
	m_flag1 = 0;
	m_flag2 = 0;
	m_flag3 = 0;
	m_tail0 = 0;
	m_tail1 = 0;
	m_tail2 = 0;
	m_tail3 = 0;
}
