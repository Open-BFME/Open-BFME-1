// Dispatch two value references from an Apt instruction payload.
class Rva8CCD60State
{
public:
	void expandPrototypeValues(void *first, void *second);
};

struct BfmePrototypeCall8CDE30
{
	int m_opcode;
	void *m_first;
	void *m_second;
};

void __cdecl bfmeExpandPrototype8CDE30(Rva8CCD60State *state, const BfmePrototypeCall8CDE30 *call)
{
	state->expandPrototypeValues(call->m_first, call->m_second);
}

void __cdecl bfmeExpandPrototype8CE410(Rva8CCD60State *state, const BfmePrototypeCall8CDE30 *call)
{
	state->expandPrototypeValues(call->m_first, call->m_second);
}
