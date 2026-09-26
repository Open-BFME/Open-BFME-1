// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x000FA140 (78 bytes).
// Retail OR-merges six source dwords into destination offsets +0x224..+0x238.

struct Rva000FA140Source
{
	unsigned m_word0;
	unsigned m_word1;
	unsigned m_word2;
	unsigned m_word3;
	unsigned m_word4;
	unsigned m_word5;
};

class Rva000FA140
{
public:
	void merge(const Rva000FA140Source &source);

private:
	unsigned char m_unmodelled_000[0x224];
	unsigned m_word0;
	unsigned m_word1;
	unsigned m_word2;
	unsigned m_word3;
	unsigned m_word4;
	unsigned m_word5;
};

void Rva000FA140::merge(const Rva000FA140Source &source)
{
	m_word0 |= source.m_word0;
	m_word1 |= source.m_word1;
	m_word2 |= source.m_word2;
	m_word3 |= source.m_word3;
	m_word4 |= source.m_word4;
	m_word5 |= source.m_word5;
}
