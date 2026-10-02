// Unclaimed tiny bodies with one shape:
//
//     mov eax,ecx / mov dword ptr [eax],vftable / ret
//
// A constructor of a polymorphic class with no base ctor call, no member
// initialisation and no argument: it copies `this` to eax, stores one relocated
// .rdata address (the vftable) at +0 and returns.  MSVC 7.1 emits exactly
// these nine bytes for `C::C() {}` (precedent: TinyVfptrCtors.cpp).  The
// gate takes the DIR32 site from retail, so the vftable address is not
// reconstructed here.  Only constructors whose vftable has no owner class
// anywhere in the ledger (no matched slot-0 deleting destructor and no
// dir32_addresses.csv name) are kept here; a vftable with an owner gives its
// constructor to that class.
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

#define BFME_VFPTR_CTOR( NAME ) \
	class NAME \
	{ \
	public: \
		NAME(); \
		virtual void slot(); \
	}; \
	NAME::NAME() \
	{ \
	}

BFME_VFPTR_CTOR( Rva007EB730VfptrCtor )
BFME_VFPTR_CTOR( Rva007EFF30VfptrCtor )
BFME_VFPTR_CTOR( Rva007F5540VfptrCtor )
BFME_VFPTR_CTOR( Rva007F8F60VfptrCtor )
BFME_VFPTR_CTOR( Rva007F9130VfptrCtor )
BFME_VFPTR_CTOR( Rva008011C0VfptrCtor )
