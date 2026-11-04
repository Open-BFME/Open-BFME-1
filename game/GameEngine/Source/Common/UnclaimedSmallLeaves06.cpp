// Unclaimed tiny bodies, three shapes:
//
//     mov eax,ecx / ret        returns this
//     mov eax,[ecx] / ret      returns the dword at +0 of this
//     mov eax,[ecx+d] / ret    returns the dword at +4, +8 or +0x10 of this
//
// Each sat in a .text gap no ledger row covered.  The start is 16-byte aligned
// directly after the ret of a matched row (so no int3 pad precedes it), and the
// terminal ret is followed by int3 padding.  No rel32 call or jmp, ILT stub,
// vtable slot or absolute code immediate in the image reaches any of them.
// Retail was linked without identical-COMDAT folding, so each address is its
// own function even where the bytes repeat.  The bytes cannot tell int from a
// pointer; the lead array only spells the witnessed offset.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#pragma pack( push, 1 )

#define BFME_THIS_RETURNER( NAME )                                            \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME *self();                                                         \
	};                                                                        \
	NAME *NAME::self()                                                        \
	{                                                                         \
		return this;                                                          \
	}

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

#define BFME_FIRST_DWORD_GETTER( NAME ) \
	class NAME \
	{ \
	public: \
		int get() const; \
\
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

BFME_THIS_RETURNER( Rva0088D420Self )
BFME_FIRST_DWORD_GETTER( Rva00894E20DwordField )
BFME_DWORD_GETTER( Rva0092EFA0DwordField, 0x4 )
BFME_FIRST_DWORD_GETTER( Rva00937300DwordField )
BFME_DWORD_GETTER( Rva0093C920DwordField, 0x10 )
BFME_DWORD_GETTER( Rva009790B0DwordField, 0x8 )

#pragma pack( pop )
