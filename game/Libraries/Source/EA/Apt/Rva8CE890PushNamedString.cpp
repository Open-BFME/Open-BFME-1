// cl: /DNDEBUG /MD /EHsc
// Apt handler, retail 0x008CE890 (64 bytes), address-derived identity: build a
// string value through Rva008AE770Stack::createString (0x008CC940) from the
// context's two operand words and the fixed string object at 0x01338710,
// push it on the state's count/array pair, and tail-dispatch the value's
// first virtual unless bit 30 of its flag word is set.

class BfmeStrVKI;
class Rva00899770;

class Rva8CE890Value
{
public:
	virtual void invoke();
	unsigned int m_flags;
};

class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int);
	int m_count;
	int m_unknown04;
	Rva8CE890Value **m_entries;
};

struct Rva8CE890Context
{
	int m_unknown00;
	void *m_unknown04;
	int m_unknown08;
};

extern BfmeStrVKI g_Va01338710String;

// ?rva8CE890PushNamedString@@YAXPAVRva008AE770Stack@@PAURva8CE890Context@@@Z
void rva8CE890PushNamedString(Rva008AE770Stack *state, Rva8CE890Context *context)
{
	Rva8CE890Value *value = reinterpret_cast<Rva8CE890Value *>(state->createString(
		context->m_unknown04, context->m_unknown08, &g_Va01338710String, 1, 1, 0));
	state->m_entries[state->m_count] = value;
	state->m_count++;

	unsigned char flags = (unsigned char)(value->m_flags >> 30);
	if (flags & 1)
		return;

	value->invoke();
}
