// Three 19-byte __thiscall members that dereference the object's leading
// pointer, read one dword out of the pointee, shift it right and keep one bit
// -- returning zero when the pointer is null:
//
//     mov eax,[ecx] / test eax,eax / je zero / mov eax,[eax+0x24]
//     shr eax,<SHIFT> / and eax,1 / ret / zero: xor eax,eax / ret
//
//     0x003D4C50  shift 2
//     0x003D49E0  shift 3
//     0x003D4A00  shift 4
//
// WHAT THE BYTES SHOW.  All nineteen bytes are concrete -- there is no
// relocation site in any of the three -- so the member offset (0), the pointee
// offset (0x24), the shift and the mask are all read straight off the
// instruction stream.  `shr` rather than `sar` says the shifted dword is
// treated as unsigned, and a single-bit mask on three different shifts of the
// same field is what a packed bit field looks like.
//
// These are the null-guarded relatives of the tree's
// Q1ShiftedBitfieldGetters.cpp family, which reads the bits out of `this`
// directly.  Here the bits live one indirection away and the accessor answers
// zero rather than faulting.
//
// THE `else` IS LOAD-BEARING.  Written as an early `if ( !p ) return 0;` the
// compiler notices eax already holds the null it just tested and folds the two
// returns into `jne $+1 / ret` -- seventeen bytes with no `xor eax,eax`, which
// is NOT what retail has.  Retail keeps a separate zeroing tail, so the source
// spelled both arms of one conditional rather than a guard followed by the
// body.  (`return p ? ... : 0;` compiles to the same nineteen bytes; the bytes
// do not choose between those two spellings.)
//
// WHAT THE BYTES CANNOT DECIDE.  The result is left in the full eax and spelled
// `int`; a C++ bit field declaration, or an unsigned return, would compile to
// the same shape.  The explicit shift-and-mask written here asserts less -- it
// claims only the bit actually kept, not a field width.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

struct Y1GuardedBits
{
	char m_lead[ 0x24 ];
	unsigned int m_bits;
};

#define Y1_GUARDED_BITFIELD_GET( NAME, SHIFT )                            \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		Y1GuardedBits *m_payload;                                         \
		int get();                                                        \
	};                                                                    \
	int NAME::get()                                                       \
	{                                                                     \
		if ( m_payload )                                                  \
			return ( m_payload->m_bits >> SHIFT ) & 1;                    \
		else                                                              \
			return 0;                                                     \
	}

Y1_GUARDED_BITFIELD_GET( Rva003D49E0, 3 )
Y1_GUARDED_BITFIELD_GET( Rva003D4A00, 4 )
Y1_GUARDED_BITFIELD_GET( Rva003D4C50, 2 )
