// cl: /DNDEBUG /MD /EHsc

struct Rva0009FFC0ClearEight
{
	unsigned char m_unmodelled_000[0x20];
	unsigned int m_values[8];

	void clear();
};

void Rva0009FFC0ClearEight::clear()
{
	m_values[0] = 0;
	m_values[1] = 0;
	m_values[2] = 0;
	m_values[3] = 0;
	m_values[4] = 0;
	m_values[5] = 0;
	m_values[6] = 0;
	m_values[7] = 0;
}
