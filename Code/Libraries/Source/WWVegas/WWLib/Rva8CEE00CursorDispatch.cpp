// ?rva8CEE00Dispatch@@YAXPAVRva8CEE00State@@PAURva8CEE00Cursor@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of a cursor-byte dispatch, retail 0x008CEE00 (64 bytes).

class Rva8CEE00Handler
{
public:
	virtual void invoke();

	unsigned m_flags;
};

class Rva8CEE00State
{
public:
	int m_count;
	int m_unused;
	Rva8CEE00Handler **m_slots;
	char m_gap[0x60 - 0x0c];
	Rva8CEE00Handler **m_table;
};

struct Rva8CEE00Cursor
{
	unsigned char *m_ptr;
};

void rva8CDE50Continue(Rva8CEE00State *state, Rva8CEE00Cursor *cursor);

void rva8CEE00Dispatch(Rva8CEE00State *state, Rva8CEE00Cursor *cursor)
{
	unsigned char code = *cursor->m_ptr++;
	int index = state->m_count;
	Rva8CEE00Handler *handler = state->m_table[code];
	state->m_slots[index] = handler;
	++state->m_count;
	unsigned char flags = (unsigned char)(handler->m_flags >> 30);
	if (!(flags & 1))
		handler->invoke();
	rva8CDE50Continue(state, cursor);
}
