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

struct lua_State
{
	Rva00990030Record *top;
	unsigned char m_pad10[0x10 - 4];
	Rva00990030Record *base;
};

unsigned Rva00990030Lookup(lua_State *range, int index)
{
	Rva00990030Record *record;
	if (index >= 0) {
		record = range->base + index - 1;
		if (record >= range->top)
			return 0;
	} else {
		record = range->top + index;
	}
	if (!record || record->m_type != 4)
		return 0;
	return record->m_value->m_value;
}
