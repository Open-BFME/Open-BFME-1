// Unclaimed tiny bodies with one shape:
//
//     mov eax,[ecx] / add eax,<imm> / ret
//
// A __thiscall member returns the pointer stored in the first dword of
// `this` advanced by a constant byte count.  char * is the spelling that
// makes the constant a byte count; the pointee type is not witnessed.
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

#define BFME_POINTER_OFFSET( NAME, DELTA ) \
	class NAME \
	{ \
	public: \
		char *offset() const; \
\
		char *m_pointer; \
	}; \
	char *NAME::offset() const \
	{ \
		return m_pointer + DELTA; \
	}

BFME_POINTER_OFFSET( Rva00850CA0PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva00891AC0PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva00891B20PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva00894D60PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva008FE8D0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva008FE970PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva008FE990PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva008FE9A0PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva008FE9B0PointerOffset, 0xC )
BFME_POINTER_OFFSET( Rva00923BD0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva00923C10PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva00923C40PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva00923C50PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva00923C60PointerOffset, 0xC )
BFME_POINTER_OFFSET( Rva009263A0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009263B0PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva0093C990PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva0093C9C0PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva0093C9D0PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva0093C9E0PointerOffset, 0xC )
BFME_POINTER_OFFSET( Rva0093D420PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva0094BCB0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva0094BCE0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva0094BDC0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva0094BFE0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009A2C90PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009A2CA0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009A2D70PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009A2D80PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva009A2D90PointerOffset, 0xC )
BFME_POINTER_OFFSET( Rva009C8EE0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009C8EF0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009C8F00PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009C9040PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009C9050PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva009C9070PointerOffset, 0xC )
BFME_POINTER_OFFSET( Rva009C9200PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009C9230PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009C9240PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009CE660PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009CE670PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009CE680PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009CE6A0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009CE830PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009CE840PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva009CE850PointerOffset, 0xC )
BFME_POINTER_OFFSET( Rva009CE860PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009CE870PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva009CE880PointerOffset, 0xC )
BFME_POINTER_OFFSET( Rva009CEB40PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009CEB50PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009D6FB0PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009D6FC0PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009D7270PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009D7280PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009ECB50PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009ECBB0PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009ECBE0PointerOffset, 0x10 )
BFME_POINTER_OFFSET( Rva009ECC50PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009ECC60PointerOffset, 0x8 )
BFME_POINTER_OFFSET( Rva009ECC70PointerOffset, 0xC )
BFME_POINTER_OFFSET( Rva009ED270PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009ED2A0PointerOffset, 0x4 )
BFME_POINTER_OFFSET( Rva009ED2C0PointerOffset, 0x10 )
