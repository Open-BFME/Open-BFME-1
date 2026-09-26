// cl: /DNDEBUG /MD /EHsc

struct Rva00695E00Difference
{
	unsigned char m_unmodelled_000[0x608];
	int m_start;
	unsigned char m_unmodelled_60c[4];
	int m_end;

	int difference();
};

int Rva00695E00Difference::difference()
{
	return m_start - m_end;
}
