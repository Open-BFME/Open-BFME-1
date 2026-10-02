// Unclaimed tiny bodies with one shape:
//
//     xor eax,eax / ret
//
// A member returns zero in all of eax without reading `this` or any
// argument.  int is spelled for the four-byte width; a null pointer would
// compile the same.
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

#define BFME_ZERO_RETURNER( NAME ) \
	class NAME \
	{ \
	public: \
		int value() const; \
	}; \
	int NAME::value() const \
	{ \
		return 0; \
	}

BFME_ZERO_RETURNER( Rva007EFFA0Zero )
BFME_ZERO_RETURNER( Rva007EFFB0Zero )
BFME_ZERO_RETURNER( Rva007F0320Zero )
BFME_ZERO_RETURNER( Rva00891840Zero )
BFME_ZERO_RETURNER( Rva00891850Zero )
BFME_ZERO_RETURNER( Rva00899650Zero )
BFME_ZERO_RETURNER( Rva0089A0F0Zero )
BFME_ZERO_RETURNER( Rva0089A1D0Zero )
BFME_ZERO_RETURNER( Rva008A1180Zero )
BFME_ZERO_RETURNER( Rva008A4C70Zero )
BFME_ZERO_RETURNER( Rva008A9890Zero )
BFME_ZERO_RETURNER( Rva008CB5A0Zero )
BFME_ZERO_RETURNER( Rva008CB670Zero )
BFME_ZERO_RETURNER( Rva008FD470Zero )
BFME_ZERO_RETURNER( Rva0092C700Zero )
BFME_ZERO_RETURNER( Rva00955900Zero )
BFME_ZERO_RETURNER( Rva00955910Zero )
BFME_ZERO_RETURNER( Rva00959A70Zero )
BFME_ZERO_RETURNER( Rva009747C0Zero )
BFME_ZERO_RETURNER( Rva0097EB00Zero )
BFME_ZERO_RETURNER( Rva0097EB10Zero )
BFME_ZERO_RETURNER( Rva009D2120Zero )
BFME_ZERO_RETURNER( Rva00B021C0Zero )
