// cl: /DNDEBUG /MD /EHsc

struct Rva00695E10Difference
{
	unsigned char m_unmodelled_000[0x60c];
	int m_start;
	unsigned char m_unmodelled_610[4];
	int m_end;

	int difference();
};

int Rva00695E10Difference::difference()
{
	return m_start - m_end;
}
