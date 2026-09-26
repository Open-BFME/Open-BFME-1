// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x006DF250 (41 bytes).

class Rva006DF250
{
public:
	void initialize();

private:
	unsigned char m_unmodelled_000[4];
	unsigned m_word0;
	unsigned m_word1;
	unsigned m_word2;
	unsigned m_word3;
	unsigned m_word4;
	unsigned char m_byte;
	unsigned char m_unmodelled_019[3];
	unsigned m_word5;
	unsigned m_word6;
	unsigned m_word7;
	unsigned m_word8;
};

void Rva006DF250::initialize()
{
	m_word0 = 0;
	m_word1 = 0;
	m_word2 = 0x42160000u;
	m_word3 = 0;
	m_word4 = 0x3F800000u;
	m_byte = 0;
	m_word6 = 0;
	m_word7 = 0;
	m_word8 = 0;
	m_word5 = 0;
}
