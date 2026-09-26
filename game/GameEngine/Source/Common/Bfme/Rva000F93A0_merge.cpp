// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x000F93A0 (53 bytes).

struct Rva000F93A0
{
	unsigned m_word0;
	unsigned m_word1;
	unsigned m_word2;
	unsigned m_word3;
	unsigned m_word4;
	unsigned m_word5;

	void merge(const Rva000F93A0 &source);
};

void Rva000F93A0::merge(const Rva000F93A0 &source)
{
	m_word0 |= source.m_word0;
	m_word1 |= source.m_word1;
	m_word2 |= source.m_word2;
	m_word3 |= source.m_word3;
	m_word4 |= source.m_word4;
	m_word5 |= source.m_word5;
}
