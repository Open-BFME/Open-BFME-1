// cl: /DNDEBUG /MD
// Fourteen 51-byte __cdecl three-pointer walks, one shape.  Retail:
//
//     cur = dest;
//     while (first != last) { cons(cur, first); ++first; ++cur; }
//     return cur;
//
// WHAT THE BYTES SHOW.  Both pointers advance by the SAME immediate
// (`add esi,<N>` and `add edi,<N>`), the callee takes them as two pushed dwords
// and the caller pops eight, so it is __cdecl with two pointer arguments and
// the stride is one element of the pointee.  The push order puts the walking
// DESTINATION first and the source second.  The loop is a while, not a
// do/while: the `cmp/je` runs before the first call.
//
// THE RETURNED CURSOR IS A LOCAL, NOT THE PARAMETER.  Walking `dest` itself
// costs SEVEN BYTES more (58 vs 51): the compiler then keeps `dest` on the
// stack for the empty-range path and reloads it there with its own `mov
// eax,[esp+0x14]` epilogue, instead of hoisting it into edi before the branch
// and letting the empty path fall through to `mov eax,edi`.  Retail hoists, so
// the source copied the parameter into a cursor first.  Whether the SOURCE
// pointer is also copied is invisible -- both spellings emit these 51 bytes.
//
// TWO AXES, BOTH READ DIRECTLY: the element stride (an imm32 in both `add`s,
// so every member of this family has a stride of at least 0x80) and the REL32
// callee.  Nine distinct strides over ten callees; each callee appears at
// exactly ONE stride, which is what makes the two axes a real pair rather than
// an over-fit.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The
// callees are REL32 and are pinned in targets/game/reverse/symbols.csv.

#define BFME_UCOPY_ELEM( SIZE )                                           \
	struct Elem##SIZE                                                     \
	{                                                                     \
		char m_bytes[ 0x##SIZE ];                                         \
	};

#define BFME_UCOPY_CONS( ADDR, ELEM )                                     \
	void __cdecl Cons##ADDR( ELEM *dest, const ELEM *src );

#define BFME_UCOPY_WALK( NAME, ELEM, CONS )                               \
	ELEM * __cdecl NAME( ELEM *first, ELEM *last, ELEM *dest )            \
	{                                                                     \
		ELEM *cur = dest;                                                 \
		while ( first != last )                                           \
		{                                                                 \
			CONS( cur, first );                                           \
			++first;                                                      \
			++cur;                                                        \
		}                                                                 \
		return cur;                                                       \
	}

BFME_UCOPY_ELEM( 00000088 )
BFME_UCOPY_ELEM( 0000008C )
BFME_UCOPY_ELEM( 000000B4 )
BFME_UCOPY_ELEM( 000000B8 )
BFME_UCOPY_ELEM( 000000BC )
BFME_UCOPY_ELEM( 000000DC )
BFME_UCOPY_ELEM( 00000128 )
BFME_UCOPY_ELEM( 000001F0 )
BFME_UCOPY_ELEM( 00000210 )

BFME_UCOPY_CONS( 0013A700, Elem00000128 )
BFME_UCOPY_CONS( 0013A760, Elem000000BC )
BFME_UCOPY_CONS( 00195060, Elem0000008C )
BFME_UCOPY_CONS( 00363A60, Elem000000B4 )
BFME_UCOPY_CONS( 0039E0A0, Elem00000088 )
BFME_UCOPY_CONS( 003A2460, Elem000000B8 )
BFME_UCOPY_CONS( 003ABF20, Elem000000DC )
BFME_UCOPY_CONS( 00607280, Elem000001F0 )
BFME_UCOPY_CONS( 00608AF0, Elem00000210 )

BFME_UCOPY_WALK( Rva00195280, Elem0000008C, Cons00195060 )
BFME_UCOPY_WALK( Rva00363AC0, Elem000000B4, Cons00363A60 )
BFME_UCOPY_WALK( Rva00363B40, Elem000000B4, Cons00363A60 )
BFME_UCOPY_WALK( Rva0039E100, Elem00000088, Cons0039E0A0 )
BFME_UCOPY_WALK( Rva003A24F0, Elem000000B8, Cons003A2460 )
BFME_UCOPY_WALK( Rva003ABF80, Elem000000DC, Cons003ABF20 )
BFME_UCOPY_WALK( Rva003B6860, Elem000000DC, Cons003ABF20 )
BFME_UCOPY_WALK( Rva006072E0, Elem000001F0, Cons00607280 )
BFME_UCOPY_WALK( Rva00608B50, Elem00000210, Cons00608AF0 )
BFME_UCOPY_WALK( Rva00774760, Elem00000128, Cons0013A700 )
BFME_UCOPY_WALK( Rva007747E0, Elem000000BC, Cons0013A760 )
BFME_UCOPY_WALK( Rva0013AC80, Elem00000128, Cons0013A700 )
BFME_UCOPY_WALK( Rva0013ACC0, Elem000000BC, Cons0013A760 )
BFME_UCOPY_WALK( Rva00195460, Elem0000008C, Cons00195060 )
