// Unclaimed tiny bodies with one shape:
//
//     mov eax,[esp+4] / ret 4
//
// A __thiscall member returns its one stack argument and pops it; `this`
// is never read.  The argument type is not witnessed beyond four bytes.
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

#define BFME_ARG_RETURNER( NAME ) \
	class NAME \
	{ \
	public: \
		int pass( int value ) const; \
	}; \
	int NAME::pass( int value ) const \
	{ \
		return value; \
	}

BFME_ARG_RETURNER( Rva00850D50Pass )
BFME_ARG_RETURNER( Rva008FEA40Pass )
BFME_ARG_RETURNER( Rva008FEDF0Pass )
BFME_ARG_RETURNER( Rva00923C70Pass )
BFME_ARG_RETURNER( Rva00923D40Pass )
BFME_ARG_RETURNER( Rva009241D0Pass )
BFME_ARG_RETURNER( Rva009263D0Pass )
BFME_ARG_RETURNER( Rva0093C9F0Pass )
BFME_ARG_RETURNER( Rva0093CA80Pass )
BFME_ARG_RETURNER( Rva0093D430Pass )
BFME_ARG_RETURNER( Rva0094BE60Pass )
BFME_ARG_RETURNER( Rva0094BF50Pass )
BFME_ARG_RETURNER( Rva0094C010Pass )
BFME_ARG_RETURNER( Rva009A2DA0Pass )
BFME_ARG_RETURNER( Rva009A2E20Pass )
BFME_ARG_RETURNER( Rva009A3390Pass )
BFME_ARG_RETURNER( Rva009C8F10Pass )
BFME_ARG_RETURNER( Rva009C9060Pass )
BFME_ARG_RETURNER( Rva009C9250Pass )
BFME_ARG_RETURNER( Rva009C9370Pass )
BFME_ARG_RETURNER( Rva009CE6B0Pass )
BFME_ARG_RETURNER( Rva009CE6D0Pass )
BFME_ARG_RETURNER( Rva009CE810Pass )
BFME_ARG_RETURNER( Rva009CE820Pass )
BFME_ARG_RETURNER( Rva009CEB60Pass )
BFME_ARG_RETURNER( Rva009CEBA0Pass )
BFME_ARG_RETURNER( Rva009CED50Pass )
BFME_ARG_RETURNER( Rva009CED70Pass )
BFME_ARG_RETURNER( Rva009D70F0Pass )
BFME_ARG_RETURNER( Rva009D7140Pass )
BFME_ARG_RETURNER( Rva009ECF10Pass )
BFME_ARG_RETURNER( Rva009ED440Pass )
