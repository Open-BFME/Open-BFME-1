// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
class AptValue
{
public:
	virtual void release();
	unsigned flags;
};
class AptInteger : public AptValue
{
public:
	static AptInteger *Create(int value);
};
class Rva8CD130State
{
public:
	int count;
	int unused;
	AptValue **stack;
};
struct Rva8CD130Context;
void rva8CD130NamedDispatch(Rva8CD130State *, Rva8CD130Context *);

// ?Rva008CE8D0PushInteger@@YAXPAVRva8CD130State@@PAURva8CD130Context@@@Z
void Rva008CE8D0PushInteger(Rva8CD130State *state, Rva8CD130Context *context)
{
	AptValue *value = AptInteger::Create(0);
	state->stack[state->count++] = value;
	unsigned stateBits = value->flags >> 30;
	if (!(static_cast<unsigned char>(stateBits) & 1))
		value->release();
	rva8CD130NamedDispatch(state,context);
}
