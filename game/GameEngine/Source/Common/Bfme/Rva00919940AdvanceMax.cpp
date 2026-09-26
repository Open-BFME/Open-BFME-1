// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00919940 (31 bytes).

class Rva00919940
{
public:
	void advanceMax();

private:
	unsigned char m_unmodelled_000[0xC8];
	unsigned m_limit;
	unsigned char m_unmodelled_CC[0x58];
	unsigned m_value;
};

void Rva00919940::advanceMax()
{
	unsigned value = m_value + 1;
	if (value < m_limit)
		m_value = value;
	else
		m_value = m_limit;
}
