// Unclaimed tiny bodies with one shape:
//
//     mov eax,imm32 / ret
//
// A member returns a 32-bit constant without reading `this`.  Every
// immediate in this file lies outside the loaded image, so none is an
// address; each is returned as the plain constant it is.
//
// Every body here sat in a .text gap no ledger row covered.  Both ends are
// proven by the retail layout: the start is 16-byte aligned directly after an
// int3 pad run, and the terminal instruction is followed by int3 padding or by
// the next matched row.  Retail was linked without identical-COMDAT folding,
// so each address is its own function even where the bytes repeat.  Most are
// unreferenced (no call, ILT stub or table slot reaches them); the notes column
// of each ledger row lists the references that do exist.  Members before an
// accessed field are spelled as a lead array because only their total size is
// witnessed.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_CONSTANT_RETURNER( NAME, VALUE ) \
	class NAME \
	{ \
	public: \
		unsigned int value() const; \
	}; \
	unsigned int NAME::value() const \
	{ \
		return VALUE; \
	}

BFME_CONSTANT_RETURNER( Rva0081E550Constant, 0x00000001u )
BFME_CONSTANT_RETURNER( Rva0084D850Constant, 0x00000001u )
BFME_CONSTANT_RETURNER( Rva008A0EA0Constant, 0x00000040u )
BFME_CONSTANT_RETURNER( Rva008F9090Constant, 0x00000006u )
BFME_CONSTANT_RETURNER( Rva008F90C0Constant, 0x00000010u )
BFME_CONSTANT_RETURNER( Rva009E6570Constant, 0xFFFFFFEFu )
BFME_CONSTANT_RETURNER( Rva009ECF20Constant, 0x00000020u )
BFME_CONSTANT_RETURNER( Rva00AFE900Constant, 0x00000011u )
