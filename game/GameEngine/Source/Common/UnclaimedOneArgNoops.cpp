// Unclaimed tiny bodies with one shape:
//
//     ret 4
//
// A body that returns at once and pops one stack dword it never reads.
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

#define BFME_ONE_ARG_NOOP( NAME ) \
	class NAME \
	{ \
	public: \
		void body( int unused ); \
	}; \
	void NAME::body( int ) \
	{ \
	}

BFME_ONE_ARG_NOOP( Rva007F0310Body )
BFME_ONE_ARG_NOOP( Rva00800450Body )
BFME_ONE_ARG_NOOP( Rva00800870Body )
BFME_ONE_ARG_NOOP( Rva00808E50Body )
BFME_ONE_ARG_NOOP( Rva0081C580Body )
BFME_ONE_ARG_NOOP( Rva00883CA0Body )
BFME_ONE_ARG_NOOP( Rva00891860Body )
BFME_ONE_ARG_NOOP( Rva008FE910Body )
BFME_ONE_ARG_NOOP( Rva008FE930Body )
BFME_ONE_ARG_NOOP( Rva00910DA0Body )
BFME_ONE_ARG_NOOP( Rva0091F9B0Body )
BFME_ONE_ARG_NOOP( Rva00931650Body )
BFME_ONE_ARG_NOOP( Rva00942F80Body )
BFME_ONE_ARG_NOOP( Rva00944BA0Body )
BFME_ONE_ARG_NOOP( Rva00955890Body )
BFME_ONE_ARG_NOOP( Rva009558F0Body )
BFME_ONE_ARG_NOOP( Rva0097E9B0Body )
BFME_ONE_ARG_NOOP( Rva009A16F0Body )
BFME_ONE_ARG_NOOP( Rva009D90C0Body )
