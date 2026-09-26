// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00990210Record
{
	unsigned m_type;
	unsigned m_4;
	unsigned m_value;
	unsigned m_C;
};

struct Rva00990210Range
{
	Rva00990210Record *m_begin;
	unsigned char m_pad10[0x10 - 4];
	Rva00990210Record *m_end;
};

unsigned Rva00990210Lookup(Rva00990210Range *range, int index)
{
	Rva00990210Record *record;
	if (index >= 0) {
		record = range->m_end + index - 1;
		if (record >= range->m_begin)
			return 0;
	} else {
		record = range->m_begin + index;
	}
	if (!record || record->m_type == 1)
		return 0;
	if (record->m_type == 6)
		return record->m_value;
	return 1;
}
