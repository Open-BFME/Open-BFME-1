// cl: /DNDEBUG /MD /EHsc

class Rva007AE300
{
public:
	void copy(unsigned *first, unsigned *second, unsigned *third,
		unsigned *fourth, unsigned *fifth, unsigned *sixth) const;

private:
	unsigned char m_unmodelled_000[0x40];
	unsigned m_word0;
	unsigned m_word1;
	unsigned m_word2;
	unsigned m_word3;
	unsigned m_word4;
	unsigned m_word5;
};

void Rva007AE300::copy(unsigned *first, unsigned *second, unsigned *third,
	unsigned *fourth, unsigned *fifth, unsigned *sixth) const
{
	*first = m_word0;
	*second = m_word1;
	*third = m_word2;
	*fourth = m_word3;
	*fifth = m_word4;
	*sixth = m_word5;
}
