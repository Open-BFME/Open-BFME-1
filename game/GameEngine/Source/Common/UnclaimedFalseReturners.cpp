// Unclaimed tiny bodies with one shape:
//
//     xor al,al / ret
//
// A member returns false without reading `this` or any argument.  Only al is
// cleared, so the result is one byte wide.
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

#define BFME_FALSE_RETURNER( NAME ) \
	class NAME \
	{ \
	public: \
		bool value() const; \
	}; \
	bool NAME::value() const \
	{ \
		return false; \
	}

BFME_FALSE_RETURNER( Rva00845680False )
BFME_FALSE_RETURNER( Rva00845690False )
BFME_FALSE_RETURNER( Rva00846010False )
BFME_FALSE_RETURNER( Rva00846020False )
BFME_FALSE_RETURNER( Rva00846080False )
BFME_FALSE_RETURNER( Rva00846090False )
BFME_FALSE_RETURNER( Rva0088F920False )
BFME_FALSE_RETURNER( Rva00891780False )
BFME_FALSE_RETURNER( Rva00891830False )
BFME_FALSE_RETURNER( Rva00891870False )
BFME_FALSE_RETURNER( Rva008F9130False )
BFME_FALSE_RETURNER( Rva008F9140False )
BFME_FALSE_RETURNER( Rva008F91F0False )
BFME_FALSE_RETURNER( Rva008F9200False )
BFME_FALSE_RETURNER( Rva008F9210False )
BFME_FALSE_RETURNER( Rva008F9280False )
BFME_FALSE_RETURNER( Rva009213B0False )
BFME_FALSE_RETURNER( Rva00921420False )
BFME_FALSE_RETURNER( Rva009CC3D0False )
BFME_FALSE_RETURNER( Rva009CC410False )
BFME_FALSE_RETURNER( Rva009CC420False )
BFME_FALSE_RETURNER( Rva009CC430False )
BFME_FALSE_RETURNER( Rva009ED1D0False )
BFME_FALSE_RETURNER( Rva009ED1E0False )
BFME_FALSE_RETURNER( Rva009ED1F0False )
