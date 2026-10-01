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

namespace _STL
{
template <class First, class Second> struct pair;
template <class Destination, class Source>
void __cdecl _Construct(Destination *dest, const Source &src);
}

#define BFME_UCOPY_CONS( ADDR, LOWER ) \
	struct Gen_t_##LOWER##_k4; \
	struct Gen_t_##LOWER##_p12cd; \
	typedef _STL::pair<const Gen_t_##LOWER##_k4, Gen_t_##LOWER##_p12cd> CopyElement##ADDR;

#define BFME_UCOPY_WALK( NAME, ELEM, ROW_ELEM )                               \
	ELEM * __cdecl NAME( ELEM *first, ELEM *last, ELEM *dest )            \
	{                                                                     \
		ELEM *cur = dest;                                                 \
		while ( first != last )                                           \
		{                                                                 \
			_STL::_Construct( (ROW_ELEM *)cur, *(const ROW_ELEM *)first ); \
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

BFME_UCOPY_CONS( 0013A700, 0013a700 )
BFME_UCOPY_CONS( 0013A760, 0013a760 )
BFME_UCOPY_CONS( 00195060, 00195060 )
BFME_UCOPY_CONS( 00363A60, 00363a60 )
BFME_UCOPY_CONS( 0039E0A0, 0039e0a0 )
BFME_UCOPY_CONS( 003A2460, 003a2460 )
BFME_UCOPY_CONS( 003ABF20, 003abf20 )
BFME_UCOPY_CONS( 00607280, 00607280 )
BFME_UCOPY_CONS( 00608AF0, 00608af0 )

BFME_UCOPY_WALK( Rva00195280, Elem0000008C, CopyElement00195060 )
BFME_UCOPY_WALK( Rva00363AC0, Elem000000B4, CopyElement00363A60 )
BFME_UCOPY_WALK( Rva00363B40, Elem000000B4, CopyElement00363A60 )
BFME_UCOPY_WALK( Rva0039E100, Elem00000088, CopyElement0039E0A0 )
BFME_UCOPY_WALK( Rva003A24F0, Elem000000B8, CopyElement003A2460 )
BFME_UCOPY_WALK( Rva003ABF80, Elem000000DC, CopyElement003ABF20 )
BFME_UCOPY_WALK( Rva003B6860, Elem000000DC, CopyElement003ABF20 )
BFME_UCOPY_WALK( Rva006072E0, Elem000001F0, CopyElement00607280 )
BFME_UCOPY_WALK( Rva00608B50, Elem00000210, CopyElement00608AF0 )
BFME_UCOPY_WALK( Rva00774760, Elem00000128, CopyElement0013A700 )
BFME_UCOPY_WALK( Rva007747E0, Elem000000BC, CopyElement0013A760 )
BFME_UCOPY_WALK( Rva0013AC80, Elem00000128, CopyElement0013A700 )
BFME_UCOPY_WALK( Rva0013ACC0, Elem000000BC, CopyElement0013A760 )
BFME_UCOPY_WALK( Rva00195460, Elem0000008C, CopyElement00195060 )
