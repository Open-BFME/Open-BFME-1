// cl: /DNDEBUG /MD /EHsc

class Rva005A4660
{
public:
	void copy(unsigned *first, unsigned *second) const;

private:
	unsigned char m_unmodelled_000[0x4d10];
	unsigned m_word0;
	unsigned m_word1;
};

void Rva005A4660::copy(unsigned *first, unsigned *second) const
{
	*first = m_word0;
	*second = m_word1;
}
