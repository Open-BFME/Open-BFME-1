// Unclaimed tiny bodies with one shape:
//
//     mov al,1 / ret
//
// A member returns true without reading `this` or any argument.  Only al is
// written, so the result is one byte wide.
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

#define BFME_TRUE_RETURNER( NAME ) \
	class NAME \
	{ \
	public: \
		bool value() const; \
	}; \
	bool NAME::value() const \
	{ \
		return true; \
	}

BFME_TRUE_RETURNER( Rva00802F40True )
BFME_TRUE_RETURNER( Rva00891E60True )
BFME_TRUE_RETURNER( Rva00892EC0True )
BFME_TRUE_RETURNER( Rva00899480True )
BFME_TRUE_RETURNER( Rva008994A0True )
BFME_TRUE_RETURNER( Rva00899D50True )
BFME_TRUE_RETURNER( Rva0089A3A0True )
BFME_TRUE_RETURNER( Rva0089A3B0True )
BFME_TRUE_RETURNER( Rva0089A620True )
BFME_TRUE_RETURNER( Rva0089A630True )
BFME_TRUE_RETURNER( Rva0089A7C0True )
BFME_TRUE_RETURNER( Rva0089A7D0True )
BFME_TRUE_RETURNER( Rva0089A960True )
BFME_TRUE_RETURNER( Rva0089A970True )
BFME_TRUE_RETURNER( Rva0089AB00True )
BFME_TRUE_RETURNER( Rva0089AB10True )
BFME_TRUE_RETURNER( Rva008BB3E0True )
BFME_TRUE_RETURNER( Rva008CBD20True )
BFME_TRUE_RETURNER( Rva008CBD40True )
BFME_TRUE_RETURNER( Rva0090E8D0True )
BFME_TRUE_RETURNER( Rva00921450True )
BFME_TRUE_RETURNER( Rva00921510True )
BFME_TRUE_RETURNER( Rva009215F0True )
BFME_TRUE_RETURNER( Rva00921610True )
BFME_TRUE_RETURNER( Rva009220B0True )
BFME_TRUE_RETURNER( Rva009226B0True )
BFME_TRUE_RETURNER( Rva00964AF0True )
BFME_TRUE_RETURNER( Rva00964DD0True )
BFME_TRUE_RETURNER( Rva00965090True )
BFME_TRUE_RETURNER( Rva00965410True )
BFME_TRUE_RETURNER( Rva00965760True )
BFME_TRUE_RETURNER( Rva00965770True )
BFME_TRUE_RETURNER( Rva00965CD0True )
BFME_TRUE_RETURNER( Rva009696E0True )
BFME_TRUE_RETURNER( Rva009D8CE0True )
BFME_TRUE_RETURNER( Rva009D9BF0True )
