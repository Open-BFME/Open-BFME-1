// Eleven ten-byte __thiscall members that read one dword out of the object,
// shift it right, mask it, and return the result:
//
//     mov eax,[ecx+<OFFSET>] / shr eax,<SHIFT> / and eax,<MASK> / ret
//
// WHAT THE BYTES SHOW.  All ten bytes are concrete -- no relocation site -- so
// the field offset, the shift count and the mask are read directly off the
// instruction stream.  `shr` (not `sar`) says the shifted value is treated as
// unsigned; the mask is a low-bit run in every member (1, 3, 7, 0x3F), which is
// what a packed bit field looks like.
//
// THREE AXES, ALL READ DIRECTLY: offset, shift, mask.  Members read the same
// field with the same shift and different masks, and with the same mask and
// different shifts, so no axis is a function of another.
//
// WHAT THE BYTES CANNOT DECIDE.  The result is left in the full eax and spelled
// `int`.  A C++ bit field declaration would compile to the same shape, and the
// bytes cannot choose between that and the explicit shift-and-mask written
// here.  The explicit form asserts less: it does not claim a field WIDTH, only
// the bits actually kept.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q1_BITFIELD_GET( NAME, OFFSET, SHIFT, MASK )                      \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		char m_lead[ OFFSET ];                                            \
		unsigned int m_bits;                                              \
		int get();                                                        \
	};                                                                    \
	int NAME::get()                                                       \
	{                                                                     \
		return ( m_bits >> SHIFT ) & MASK;                                \
	}

Q1_BITFIELD_GET( Rva0016E4B0, 0x40, 7, 0x1 )
Q1_BITFIELD_GET( Rva001ED560, 0x18, 5, 0x1 )
Q1_BITFIELD_GET( Rva002700D0, 0x40, 10, 0x1 )
Q1_BITFIELD_GET( Rva00270110, 0x40, 6, 0x1 )
Q1_BITFIELD_GET( Rva003D4AC0, 0xC, 20, 0x1 )
Q1_BITFIELD_GET( Rva003D4AD0, 0xC, 21, 0x1 )
Q1_BITFIELD_GET( Rva003D4AF0, 0xC, 22, 0x3 )
Q1_BITFIELD_GET( Rva003D4BA0, 0xC, 3, 0x7 )
Q1_BITFIELD_GET( Rva003D4BB0, 0xC, 6, 0x3F )
Q1_BITFIELD_GET( Rva003D4BC0, 0xC, 12, 0x3F )
Q1_BITFIELD_GET( Rva003D4C90, 0xC, 18, 0x1 )
