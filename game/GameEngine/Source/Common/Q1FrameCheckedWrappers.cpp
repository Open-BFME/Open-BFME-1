// cl: /Od /GZ
// Seven seventeen-byte __cdecl functions that are BYTE-IDENTICAL apart from the
// position-dependent encoding of their two calls:
//
//     push ebp / mov ebp,esp / call <REL32>
//     cmp ebp,esp / call <REL32> / pop ebp / ret
//
// WHAT THE BYTES SHOW, AND WHY THIS FILE CARRIES ITS OWN FLAGS.  A frame
// pointer is set up for a body with no locals, no arguments and one void call,
// and the frame is then CHECKED: `cmp ebp,esp` followed by a call whose target
// (RVA 0x009F7502) is the two-byte `jne / ret` head of a stack-check helper.
// That pair is MSVC 7.1`s /GZ run-time check, and /GZ is rejected on the same
// command line as /O2, so these seven bodies cannot have been compiled with the
// settings the rest of the binary was.  The `// cl:` line above is not a
// convenience -- it is the claim these bytes force, and it is why this family
// gets a translation unit to itself instead of joining the others.
//
// NO PAYLOAD AXIS AT ALL.  All seven call the same inner function (RVA
// 0x007FEA00) and the same check helper; every difference between them is the
// REL32 arithmetic of where they sit.  Retail carries seven copies of one
// wrapper.
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing says why seven copies exist, whether
// the inner call was written directly or reached through something the
// compiler inlined away, or what any of them are called.  The check helper is
// referenced under its compiler-generated name because that is the symbol MSVC
// emits for it; the pin points that name at the address the call sites encode.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; both pins
// are address-derived and additive.

void Q1Wrapped007FEA00( void );

#define Q1_FRAME_CHECKED_WRAPPER( NAME )                                  \
	void NAME( void );                                                    \
	void NAME( void )                                                     \
	{                                                                     \
		Q1Wrapped007FEA00();                                                  \
	}

Q1_FRAME_CHECKED_WRAPPER( Rva007F8B40 )
Q1_FRAME_CHECKED_WRAPPER( Rva00807900 )
Q1_FRAME_CHECKED_WRAPPER( Rva00814020 )
Q1_FRAME_CHECKED_WRAPPER( Rva00814520 )
Q1_FRAME_CHECKED_WRAPPER( Rva00815890 )
Q1_FRAME_CHECKED_WRAPPER( Rva008173A0 )
Q1_FRAME_CHECKED_WRAPPER( Rva0081BA40 )
