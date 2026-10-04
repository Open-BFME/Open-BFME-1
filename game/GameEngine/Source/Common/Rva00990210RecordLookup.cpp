// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00990210Record
{
	unsigned m_type;
	unsigned m_4;
	unsigned m_value;
	unsigned m_C;
};

struct lua_State
{
	Rva00990210Record *top;
	unsigned char m_pad10[0x10 - 4];
	Rva00990210Record *Cbase;
};

unsigned Rva00990210Lookup(lua_State *range, int index)
{
	Rva00990210Record *record;
	if (index >= 0) {
		record = range->Cbase + index - 1;
		if (record >= range->top)
			return 0;
	} else {
		record = range->top + index;
	}
	if (!record || record->m_type == 1)
		return 0;
	if (record->m_type == 6)
		return record->m_value;
	return 1;
}
