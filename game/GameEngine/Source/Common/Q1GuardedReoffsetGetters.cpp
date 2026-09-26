// Fifteen __thiscall members with one shape, in two encodings that differ only
// in whether the second `lea` needs a disp8 or a disp32:
//
//     lea eax,[ecx-<BACK>] / test eax,eax / je zero
//     lea eax,[ecx+<FORWARD>] / ret
//   zero:
//     xor eax,eax / ret
//
// WHAT THE BYTES SHOW.  Every byte is concrete -- no relocation site in any of
// the fifteen -- so both displacements are read directly off the instruction
// stream.  The load-bearing detail is WHICH value gets tested: `test eax,eax`
// follows the FIRST lea, so the guard is on `this - BACK`, not on `this`.  A
// null test on `this` itself would have been `test ecx,ecx`, and MSVC 7.1
// elides that test entirely because `this` is known non-null -- which is why
// these bodies can only come from an expression whose subject is a POINTER
// DERIVED FROM `this` BY SUBTRACTION and guarded before use.  That is what is
// spelled here, and it is the whole of what the bytes support.
//
// TWO AXES: the backward displacement (0x0C in thirteen members, 0x20 in one
// pair) and the forward displacement (0x08..0x2C in the disp8 encoding,
// 0xC4..0x334 in the disp32 encoding).
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing here says WHY `this` is adjusted
// backwards.  A container-of computation, a sub-object `this` pointing into the
// middle of a larger object, and a hand-written pointer cast all produce these
// bytes; the explicit `char *` arithmetic below claims no inheritance
// relationship and no containing type, which is the least it can claim.  The
// return is spelled `void *` because the result is only ever an address.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q1_GUARDED_REOFFSET( NAME, BACK, FORWARD )                        \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void *get();                                                      \
	};                                                                    \
	void *NAME::get()                                                     \
	{                                                                     \
		return ( (char *)this - ( BACK ) ) ? (char *)this + ( FORWARD )   \
		                                   : 0;                           \
	}

Q1_GUARDED_REOFFSET( Rva001F60B0, 0xC, 0xC )
Q1_GUARDED_REOFFSET( Rva001F60D0, 0xC, 0x8 )
Q1_GUARDED_REOFFSET( Rva001F8A50, 0xC, 0xC )
Q1_GUARDED_REOFFSET( Rva001F8C20, 0xC, 0x10 )
Q1_GUARDED_REOFFSET( Rva0020B0A0, 0xC, 0x20 )
Q1_GUARDED_REOFFSET( Rva00219380, 0xC, 0x20 )
Q1_GUARDED_REOFFSET( Rva0025A300, 0xC, 0x2C )
Q1_GUARDED_REOFFSET( Rva002D45E0, 0xC, 0x10 )

Q1_GUARDED_REOFFSET( Rva00212D70, 0xC, 0xD4 )
Q1_GUARDED_REOFFSET( Rva002C41E0, 0xC, 0x334 )
Q1_GUARDED_REOFFSET( Rva00219770, 0xC, 0xC8 )
Q1_GUARDED_REOFFSET( Rva00230730, 0x20, 0xC4 )
Q1_GUARDED_REOFFSET( Rva00230750, 0x20, 0xC4 )
Q1_GUARDED_REOFFSET( Rva00267640, 0xC, 0xDC )
Q1_GUARDED_REOFFSET( Rva0026C5A0, 0xC, 0xDC )
