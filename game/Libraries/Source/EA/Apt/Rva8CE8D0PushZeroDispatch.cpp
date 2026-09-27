// cl: /DNDEBUG /MD /EHsc
// Apt handler, retail 0x008CE8D0 (61 bytes), address-derived identity: push
// AptInteger::Create(0) onto the state's count/array pair, dispatch the new
// node's first virtual unless bit 30 of its flag word is set, then hand the
// same state and context to rva8CD130NamedDispatch (0x008CD130).

class Rva8CE8D0Node
{
public:
	virtual void invoke();
	unsigned int m_flags;
};

class Rva8CD130State
{
public:
	int m_count;
	int m_unused;
	Rva8CE8D0Node **m_stack;
};

struct Rva8CD130Context;

class AptInteger { public: static AptInteger *Create(int value); };

void rva8CD130NamedDispatch(Rva8CD130State *state, Rva8CD130Context *context);

// ?rva8CE8D0PushZeroDispatch@@YAXPAVRva8CD130State@@PAURva8CD130Context@@@Z
void rva8CE8D0PushZeroDispatch(Rva8CD130State *state, Rva8CD130Context *context)
{
	Rva8CE8D0Node *node = (Rva8CE8D0Node *)AptInteger::Create(0);
	state->m_stack[state->m_count] = node;
	state->m_count = state->m_count + 1;

	unsigned char flags = (unsigned char)(node->m_flags >> 30);
	if (!(flags & 1))
		node->invoke();

	rva8CD130NamedDispatch(state, context);
}
