// Unclaimed tiny bodies with one shape:
//
//     mov eax,[ecx+4] / ret
//
// A __thiscall member returns the dword at +4 of `this`.  The bytes cannot
// tell int from a pointer or any other four-byte value moved with a plain
// load.
//
// Every body here sat in a .text gap no ledger row covered.  The start is
// 16-byte aligned directly after the ret of the preceding matched row (a
// 16-byte DockUpdate.cpp dup body in each case, so no int3 pad separates
// them), and the terminal ret is followed by int3 padding.  Retail was linked
// without identical-COMDAT folding, so each address is its own function even
// where the bytes repeat.  None is reached by a call, jmp, ILT stub, vtable
// slot or code immediate.  The member before +4 is spelled as a lead array
// because only the total size is witnessed.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#pragma pack( push, 1 )

#define BFME_DWORD_GETTER( NAME, LEAD ) \
	class NAME \
	{ \
	public: \
		int get() const; \
\
		char m_lead[ LEAD ]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DWORD_GETTER( Rva007F6B00DwordField, 0x4 )
BFME_DWORD_GETTER( Rva007F6B70DwordField, 0x4 )
BFME_DWORD_GETTER( Rva007F6C30DwordField, 0x4 )
BFME_DWORD_GETTER( Rva00801540DwordField, 0x4 )
BFME_DWORD_GETTER( Rva008015D0DwordField, 0x4 )
BFME_DWORD_GETTER( Rva008029E0DwordField, 0x4 )
BFME_DWORD_GETTER( Rva0081D430DwordField, 0x4 )

#pragma pack( pop )
