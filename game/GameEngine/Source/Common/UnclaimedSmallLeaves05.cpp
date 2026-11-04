// Unclaimed tiny leaf bodies, each alone in a .text gap no ledger row covered:
//
//     ret                   0x008BD5A0  one-byte body, pops nothing
//     mov eax,ecx / ret     0x008088A0  __thiscall member returning this
//     mov eax,ecx / ret 4   0x008F8F80, 0x008F8FB0  returns this, pops one dword
//
// Each starts 16-byte aligned directly after the ret of the preceding matched
// row (so no int3 pad separates them), ends in ret followed by int3 padding or
// the next matched row, and has no call, jmp, ILT stub, vtable slot or code
// immediate pointing at it.  Retail was linked without identical-COMDAT
// folding, so each address is its own function even where the bytes repeat.
// The argument of the one-argument returners is not witnessed; int is spelled
// for its size.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

void Rva008BD5A0Noop() {}

class Rva008088A0Self
{
public:
	Rva008088A0Self *self();
};

Rva008088A0Self *Rva008088A0Self::self()
{
	return this;
}

#define BFME_THIS_RETURNER_ONE_ARG( NAME ) \
	class NAME \
	{ \
	public: \
		NAME *self( int unused ); \
	}; \
	NAME *NAME::self( int ) \
	{ \
		return this; \
	}

BFME_THIS_RETURNER_ONE_ARG( Rva008F8F80Self )
BFME_THIS_RETURNER_ONE_ARG( Rva008F8FB0Self )
