// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00477DF0 (33 bytes).

struct Rva00477DF0
{
	unsigned char m_unmodelled_000[0x14];
	int m_first;
	int m_third;
	int m_second;
	int m_fourth;

	void orderPairs();
};

void Rva00477DF0::orderPairs()
{
	if (m_first > m_second)
	{
		int value = m_first;
		m_first = m_second;
		m_second = value;
	}
	if (m_third > m_fourth)
	{
		int value = m_third;
		m_third = m_fourth;
		m_fourth = value;
	}
}
