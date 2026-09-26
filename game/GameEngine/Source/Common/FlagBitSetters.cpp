// 6 bodies that set or clear one bit of a member according to a byte
// argument:
//
//     mov al,[esp+4] / test al,al / mov eax,[ecx+<D>] / je +N /
//     or eax,<MASK> / mov [ecx+<D>],eax / ret 4 /
//     and eax,~<MASK> / mov [ecx+<D>],eax / ret 4
//
// WHAT THE BYTES SHOW.  One byte argument, one dword member, and two exits that
// differ only in `or <MASK>` versus `and` its exact complement -- which is what
// `if ( on ) m_flags |= MASK; else m_flags &= ~MASK;` compiles to.  The member
// is loaded ONCE, before the branch, and both arms write it back; that hoist is
// the compiler's and needs nothing from the source.  The masks are single bits.
//
// The argument is spelled `unsigned char` because only al is read; the bytes
// cannot distinguish it from `bool` or `signed char`.  Members ahead of the
// flag word are a lead array: their total size is all the displacement
// witnesses.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_FLAG_BIT_SETTER( NAME, LEAD, MASK )                              \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void setFlag( unsigned char on );                                     \
                                                                              \
		char         m_lead[ LEAD ];                                          \
		unsigned int m_flags;                                                 \
	};                                                                        \
	void NAME::setFlag( unsigned char on )                                    \
	{                                                                         \
		if ( on )                                                             \
			m_flags |= ( MASK );                                              \
		else                                                                  \
			m_flags &= ~( MASK );                                             \
	}

BFME_FLAG_BIT_SETTER( Rva0016E450FlagBit, 0x40, 0x2u )
BFME_FLAG_BIT_SETTER( Rva0016E480FlagBit, 0x40, 0x8u )
BFME_FLAG_BIT_SETTER( Rva001B5190FlagBit, 0x40, 0x10u )
BFME_FLAG_BIT_SETTER( Rva002700E0FlagBit, 0x40, 0x40u )
BFME_FLAG_BIT_SETTER( Rva004784A0FlagBit, 0x38, 0x2u )
BFME_FLAG_BIT_SETTER( Rva009120F0FlagBit, 0x30, 0x2u )
