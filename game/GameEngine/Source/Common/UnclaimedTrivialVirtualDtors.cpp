// Unclaimed tiny bodies with one shape:
//
//     mov dword ptr [ecx],vftable / ret
//
// An empty destructor of a polymorphic class: it re-seats the vftable at +0
// and returns nothing (a constructor would also return `this` in eax).
// Precedent: TrivialVirtualDestructors.cpp.  Destructors whose vftable
// already carries a real class name in dir32_addresses.csv are left out.
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

#define BFME_TRIVIAL_VIRTUAL_DTOR( NAME ) \
	class NAME \
	{ \
	public: \
		virtual ~NAME(); \
	}; \
	NAME::~NAME() \
	{ \
	}

BFME_TRIVIAL_VIRTUAL_DTOR( Rva007EA6C0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007F48B0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007F48C0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007F8720Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007F8DA0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007F95D0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007FA670Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007FA970Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007FBB50Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva007FCFB0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00801420Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00802200Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00802280Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00802870Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00802E30Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva008062F0Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva008DCC90Poly )
BFME_TRIVIAL_VIRTUAL_DTOR( Rva00938BC0Poly )
