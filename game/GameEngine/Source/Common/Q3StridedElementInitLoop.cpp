// Nine copies of one loop that walks an array of fixed-stride elements, calls a
// two-argument cdecl helper on each, and returns the cursor PAST the last one.
//
// WHAT THE BYTES SHOW.  Three cdecl parameters: a base pointer, a COUNT tested
// with `test edi,edi` / `jbe` -- an UNSIGNED "greater than zero" test, not a
// signed not-equal, which would have emitted `je` -- and a third dword handed
// through untouched to the helper.  The helper is called as (cursor, extra) and
// the frame is cleaned by the caller.  After it returns, the cursor advances by
// a constant stride and the count counts down.
//
// The single return path returning esi is the load-bearing detail.  Written as a
// walk over the PARAMETER, the early-exit arm has to reload that parameter and
// the body costs six bytes more (50 rather than 44).  Retail returns the WALKED
// value from both arms, which is what a source that copies the base into a LOCAL
// CURSOR first compiles to.  The countdown `dec`/`jne` is not in the source: it
// is the compiler's induction rewrite of a forward count-up loop -- writing the
// countdown explicitly costs a different compare.
//
// TWO AXES.  The stride -- 0x28, 0x88, 0x8C, 0xB4, 0xB8, 0xDC, 0x124, 0x128,
// 0x1F0, 0x210 -- and the helper.  Nine rows, nine distinct strides, nine
// distinct helpers, so neither axis is standing in for the other.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; helper pins are
// address-derived and additive, read from the REL32 at the call site.
//
// WHAT THE BYTES CANNOT DECIDE.  What the helper does -- it is not necessarily a
// constructor, only a per-element call.  The third parameter's type: it is one
// dword, never dereferenced here.  And whether the count is `unsigned` or a
// pointer difference the compiler proved non-negative; only the UNSIGNED test is
// visible.

#define BFME_STRIDED_INIT_LOOP( NAME, HELPER, STRIDE )                        \
	struct NAME##Elem { char m_bytes[ STRIDE ]; };                            \
	void HELPER( NAME##Elem *p, void *extra );                                \
	NAME##Elem *NAME( NAME##Elem *base, unsigned int count, void *extra );    \
	NAME##Elem *NAME( NAME##Elem *base, unsigned int count, void *extra )     \
	{                                                                         \
		NAME##Elem *cursor = base;                                            \
		for ( unsigned int i = 0; i < count; ++i )                            \
		{                                                                     \
			HELPER( cursor, extra );                                          \
			++cursor;                                                         \
		}                                                                     \
		return cursor;                                                        \
	}

BFME_STRIDED_INIT_LOOP( Rva000E3C10, Gen000E3B70, 0x124 )
BFME_STRIDED_INIT_LOOP( Rva001952C0, Gen00195060, 0x8C )
BFME_STRIDED_INIT_LOOP( Rva00363B00, Gen00363A60, 0xB4 )
BFME_STRIDED_INIT_LOOP( Rva0039E140, Gen0039E0A0, 0x88 )
BFME_STRIDED_INIT_LOOP( Rva003A2530, Gen003A2460, 0xB8 )
BFME_STRIDED_INIT_LOOP( Rva003ABFC0, Gen003ABF20, 0xDC )
BFME_STRIDED_INIT_LOOP( Rva00607320, Gen00607280, 0x1F0 )
BFME_STRIDED_INIT_LOOP( Rva00608B90, Gen00608AF0, 0x210 )
BFME_STRIDED_INIT_LOOP( Rva007747A0, Gen0013A700, 0x128 )
