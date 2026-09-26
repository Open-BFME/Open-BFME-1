// Eight 9-byte __thiscall bodies of the single shape
//
//     mov eax,[ecx+<DISP8>] / add eax,<IMM32> / ret
//
// WHAT THE BYTES SHOW.  A pointer held in the object is loaded and a constant
// is added to it before it is returned: an interior-pointer getter,
// `return (char *)m_ptr + K;` -- the address of a sub-object K bytes into
// whatever the stored pointer points at.  Nothing is dereferenced, so K is a
// layout offset in the POINTEE, not in this object.
//
// TWO AXES, BOTH READ DIRECTLY: the load offset in this object and the added
// constant.  The constant uses the eax-accumulator form (opcode 05), which is
// simply what MSVC 7.1 emits for `eax + imm32`.
//
// SEVEN SIBLINGS OF THIS SHAPE ARE NOT HERE.  0x001F7200, 0x00268790, 0x002687A0,
// 0x002687B0, 0x0026A960, 0x0026A970 and 0x00287340 load at NEGATIVE
// displacements (-0x4C, -0x0C, -0x20, -0x1C).  A C++ member never sits at a
// negative offset from `this`, so those bodies are not this shape written a
// different way; they are compiled against an already-adjusted `this` and
// cannot be spelled in source.  They are left unclaimed deliberately.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_INTERIOR_POINTER_GETTER( NAME, OFFSET, DELTA )               \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		char *interior();                                                   \
		char m_lead[ OFFSET ];                                              \
		char *m_ptr;                                                        \
	};                                                                     \
	char *NAME::interior()                                                 \
	{                                                                      \
		return m_ptr + DELTA;                                               \
	}

BFME_INTERIOR_POINTER_GETTER( Rva001B2C00, 0x4, 0xB4 )
BFME_INTERIOR_POINTER_GETTER( Rva003CC6D0, 0x8, 0x110 )
BFME_INTERIOR_POINTER_GETTER( Rva003CC6E0, 0x8, 0x90 )
BFME_INTERIOR_POINTER_GETTER( Rva005A7410, 0x4, 0xE0 )
BFME_INTERIOR_POINTER_GETTER( Rva005A7420, 0x4, 0x150 )
BFME_INTERIOR_POINTER_GETTER( Rva005A7430, 0x4, 0x1C0 )
BFME_INTERIOR_POINTER_GETTER( Rva005A7440, 0x4, 0x230 )
BFME_INTERIOR_POINTER_GETTER( Rva005A7450, 0x4, 0x2A0 )
