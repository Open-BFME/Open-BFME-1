// cl: /DNDEBUG /MD /EHsc

struct Rva001B1210
{
	unsigned int m_values[16];
	unsigned int m_other[16];
	unsigned int m_tail0;
	unsigned int m_tail1;

	void clear();
};

void Rva001B1210::clear()
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		m_other[i] = 0;
		m_values[i] = 0;
	}
	m_tail1 = 0;
	m_tail0 = 0;
}
