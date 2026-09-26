// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001C0410 (35 bytes).

struct Rva001C0410
{
	unsigned m_word0;
	unsigned m_word1;
	unsigned m_word2;

	void merge(const Rva001C0410 &source);
};

void Rva001C0410::merge(const Rva001C0410 &source)
{
	m_word0 &= source.m_word0;
	m_word1 &= source.m_word1;
	m_word2 &= source.m_word2;
}
