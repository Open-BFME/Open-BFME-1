// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00990030Value
{
	unsigned char m_padC[0xC];
	unsigned m_value;
};

struct Rva00990030Record
{
	unsigned m_type;
	unsigned m_4;
	Rva00990030Value *m_value;
	unsigned m_C;
};

struct Rva00990030Range
{
	Rva00990030Record *m_begin;
	unsigned char m_pad10[0x10 - 4];
	Rva00990030Record *m_end;
};

unsigned Rva00990030Lookup(Rva00990030Range *range, int index)
{
	Rva00990030Record *record;
	if (index >= 0) {
		record = range->m_end + index - 1;
		if (record >= range->m_begin)
			return 0;
	} else {
		record = range->m_begin + index;
	}
	if (!record || record->m_type != 4)
		return 0;
	return record->m_value->m_value;
}
