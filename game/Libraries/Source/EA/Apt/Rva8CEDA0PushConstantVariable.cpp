// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME Apt opcode 0xAE, retail 0x008CEDA0 (93 bytes), slot 0x00ED5D20 of the
// opcode table based at 0x00ED5A68 (see AptActionInterpreterStoreRegister.cpp).
// No ledger row covered it.  A one-byte operand indexes the constant pool
// (+0x60); the entry's name string (the entry itself when it is a string
// value, type 1, else its +0x20 string object) is resolved to a value through
// the interpreter's createString (0x008CC940, the call EnsureName008CDAD0.cpp
// makes), which is pushed with a reference added.

class BfmeStrVKI;
class Rva00899770;

class Rva008CEDA0Value
{
public:
	virtual void addRef();
	virtual void release();

	unsigned int m_valueBits;
	char m_pad08[0x18];
	Rva008CEDA0Value *m_stringObject;
};

class Rva008AE770Stack
{
};

// Retail calls 0x008CC940 as a thiscall with six arguments; the body is linked
// as the cdecl void() row ?d_008cc940@@YAXXZ (see aptExportString.cpp).
extern void d_008cc940();
typedef Rva00899770 *(Rva008AE770Stack::*Rva008CEDA0CreateString)(void *, int,
	BfmeStrVKI *, int, int, int);

struct Rva008CEDA0State
{
	int m_count;
	int m_capacity;
	Rva008CEDA0Value **m_stack;
	char m_pad0C[0x54];
	Rva008CEDA0Value **m_constants;
};

struct Rva008CEDA0Context
{
	const unsigned char *m_pc;
	void *m_owner;
	int m_scope;
};

void rva8CEDA0PushConstantVariable(Rva008CEDA0State *state, Rva008CEDA0Context *context)
{
	unsigned char index = *context->m_pc++;
	Rva008CEDA0Value *constant = state->m_constants[index];
	if ((constant->m_valueBits & 0x3f) != 1)
		constant = constant->m_stringObject;
	union { void (*fn)(); Rva008CEDA0CreateString call; } u = { d_008cc940 };
	Rva008CEDA0Value *value = (Rva008CEDA0Value *)(((Rva008AE770Stack *)state)->*u.call)(
		context->m_owner, context->m_scope, (BfmeStrVKI *)((char *)constant + 8), 1, 1, 0);
	state->m_stack[state->m_count++] = value;
	if (!((unsigned char)(value->m_valueBits >> 30) & 1))
		value->addRef();
}
