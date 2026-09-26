// cl: /DNDEBUG /MD /EHsc

class Rva00783790
{
public:
	void copy(unsigned *target) const;

private:
	unsigned char m_unmodelled_000[0x1c];
	unsigned m_word0;
	unsigned m_word1;
};

void Rva00783790::copy(unsigned *target) const
{
	target[16] = m_word0;
	target[17] = m_word1;
	target[8] = m_word0;
	target[7] = 1;
}
