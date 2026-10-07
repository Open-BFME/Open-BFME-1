// ?rva8CEE00Dispatch@@YAXPAVRva8CEE00State@@PAURva8CEE00Cursor@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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

// The continuation is retail 0x008CDE50 (cdecl, two stack arguments), ledgered
// as the generated dump d_008cde50 with no typed signature.
void d_008cde50();
typedef void (*Rva8CDE50ContinueFn)(Rva8CEE00State *state, Rva8CEE00Cursor *cursor);

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
	reinterpret_cast<Rva8CDE50ContinueFn>(d_008cde50)(state, cursor);
}
