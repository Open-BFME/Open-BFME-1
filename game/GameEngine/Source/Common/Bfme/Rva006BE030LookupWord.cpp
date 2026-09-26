// cl: /DNDEBUG /MD /EHsc

struct Rva006BE030LookupWord
{
	unsigned char m_unmodelled_000[8];
	int m_stride;
	unsigned char m_unmodelled_00C[0x14];
	int m_limit;
	unsigned short *m_values;

	unsigned short lookup(int offset, int row);
};

unsigned short Rva006BE030LookupWord::lookup(int offset, int row)
{
	int index = m_stride * row + offset;
	if (index < 0 || index >= m_limit || m_values == 0)
		return 0;
	return m_values[index];
}
