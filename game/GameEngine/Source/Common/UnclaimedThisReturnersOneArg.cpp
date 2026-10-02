// Unclaimed tiny bodies with one shape:
//
//     mov eax,ecx / ret 4
//
// A __thiscall member returns `this` and pops one stack dword it never
// reads.  The argument type is not witnessed; int is spelled for its size.
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

#define BFME_THIS_RETURNER_ONE_ARG( NAME )                                    \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME *self( int unused );                                             \
	};                                                                        \
	NAME *NAME::self( int )                                                   \
	{                                                                         \
		return this;                                                          \
	}

BFME_THIS_RETURNER_ONE_ARG( Rva0081C4F0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva0081D490Self )
BFME_THIS_RETURNER_ONE_ARG( Rva00850CE0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva00850D30Self )
BFME_THIS_RETURNER_ONE_ARG( Rva00850D40Self )
BFME_THIS_RETURNER_ONE_ARG( Rva008919D0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva008F8F60Self )
BFME_THIS_RETURNER_ONE_ARG( Rva008F8F90Self )
BFME_THIS_RETURNER_ONE_ARG( Rva008F9070Self )
BFME_THIS_RETURNER_ONE_ARG( Rva008F9080Self )
BFME_THIS_RETURNER_ONE_ARG( Rva008FEA20Self )
BFME_THIS_RETURNER_ONE_ARG( Rva008FEA60Self )
BFME_THIS_RETURNER_ONE_ARG( Rva0090C720Self )
BFME_THIS_RETURNER_ONE_ARG( Rva00923CD0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva00923D20Self )
BFME_THIS_RETURNER_ONE_ARG( Rva00924040Self )
BFME_THIS_RETURNER_ONE_ARG( Rva00924050Self )
BFME_THIS_RETURNER_ONE_ARG( Rva00924060Self )
BFME_THIS_RETURNER_ONE_ARG( Rva0093CA60Self )
BFME_THIS_RETURNER_ONE_ARG( Rva0093CBF0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva0094BE30Self )
BFME_THIS_RETURNER_ONE_ARG( Rva0094BE40Self )
BFME_THIS_RETURNER_ONE_ARG( Rva0094BE90Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009A17F0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009A2E00Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009A2E50Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009C9010Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009C9020Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009C9080Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009C9090Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009C90A0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009CE790Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009CE7E0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009CE890Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009CE8A0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009CE8B0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009CE8C0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009D6FD0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009D6FE0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009D70B0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009D70C0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009D70D0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009D70E0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009ECCA0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009ECCB0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009ECCE0Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009ECD60Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009ECD90Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009F2C70Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009F4520Self )
BFME_THIS_RETURNER_ONE_ARG( Rva009F4530Self )
