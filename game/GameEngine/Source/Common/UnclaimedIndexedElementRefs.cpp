// Unclaimed tiny bodies with one shape:
//
//     mov eax,[ecx+4] / mov ecx,[esp+4] / lea eax,[eax+ecx*4] / ret 4
//
// A __thiscall member returns a reference to element i of the dword array
// whose pointer sits at this+4.  The element type is not witnessed beyond
// its four-byte stride.
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

#define BFME_INDEXED_ELEMENT( NAME ) \
	class NAME \
	{ \
	public: \
		int &at( int index ); \
\
		int m_lead; \
		int *m_elements; \
	}; \
	int &NAME::at( int index ) \
	{ \
		return m_elements[ index ]; \
	}

BFME_INDEXED_ELEMENT( Rva00903220Indexed )
BFME_INDEXED_ELEMENT( Rva00912560Indexed )
BFME_INDEXED_ELEMENT( Rva00918370Indexed )
BFME_INDEXED_ELEMENT( Rva0092EE20Indexed )
BFME_INDEXED_ELEMENT( Rva0092EE40Indexed )
BFME_INDEXED_ELEMENT( Rva0092EF00Indexed )
BFME_INDEXED_ELEMENT( Rva0093C8D0Indexed )
BFME_INDEXED_ELEMENT( Rva0093C8F0Indexed )
BFME_INDEXED_ELEMENT( Rva0093CC40Indexed )
BFME_INDEXED_ELEMENT( Rva00944DB0Indexed )
BFME_INDEXED_ELEMENT( Rva0096CB20Indexed )
BFME_INDEXED_ELEMENT( Rva0096CB40Indexed )
BFME_INDEXED_ELEMENT( Rva00973540Indexed )
BFME_INDEXED_ELEMENT( Rva009806D0Indexed )
BFME_INDEXED_ELEMENT( Rva009806E0Indexed )
BFME_INDEXED_ELEMENT( Rva00980700Indexed )
BFME_INDEXED_ELEMENT( Rva00AFE970Indexed )
BFME_INDEXED_ELEMENT( Rva00AFECB0Indexed )
