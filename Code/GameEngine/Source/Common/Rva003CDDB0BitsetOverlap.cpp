// cl: /O2 /DNDEBUG /MD
// Retail 0x003CDDB0 compares two integer ranges for a shared bit.

struct Rva003CDDB0Range
{
	const int *m_begin;
	const int *m_end;

	bool method(const Rva003CDDB0Range *other);
};

bool Rva003CDDB0Range::method(const Rva003CDDB0Range *other)
{
	const Rva003CDDB0Range *otherRange = other;
	unsigned int thisCount;
	unsigned int otherCount;
	otherCount = otherRange->m_end - otherRange->m_begin;
	thisCount = m_end - m_begin;
	const int *count = otherCount < thisCount ? (const int *)&otherCount : (const int *)&thisCount;

	for (int i = 0; i < *count; ++i)
	{
		if ((m_begin[i] & otherRange->m_begin[i]) != 0)
			return true;
	}

	return false;
}
