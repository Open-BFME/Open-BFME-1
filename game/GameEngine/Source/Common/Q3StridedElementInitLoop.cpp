// stlport
//
// Nine copies of one loop that walks an array of fixed-stride elements,
// copy-constructs one value into each, and returns the cursor PAST the last.
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
// THE HELPERS ARE STLPORT _Construct INSTANCES.  Each REL32 lands on an
// ordinary ILT entry that jumps to a matched _STL::_Construct<T,T>(T*, const T&)
// row (tools/callees.py: 0x000E3B70 for PlayerTemplate, the rest map-node pair
// rows), so the loop copy-constructs `*extra` into each slot.  The helpers are
// declared as explicit specializations so this TU calls the matched bodies
// instead of inlining a second copy.
//
// IDENTITY IS NOT RECOVERED.  The loop names are address-derived, and the
// pair payload names are the address-derived ones of the matched helper rows,
// sized as those rows' generated payloads; only their names reach the bytes.
//
// WHAT THE BYTES CANNOT DECIDE.  The third parameter's declared type: it is one
// dword, never dereferenced here.  And whether the count is `unsigned` or a
// pointer difference the compiler proved non-negative; only the UNSIGNED test
// is visible.

#include <utility>
#include <memory>

class PlayerTemplate;

namespace _STL
{
template<> void _Construct<PlayerTemplate, PlayerTemplate>(
	PlayerTemplate *p, const PlayerTemplate &value );
}

#define BFME_PAIR_PAYLOAD( ADDR )                                             \
	struct Gen_t_##ADDR##_k4 { int a[1]; };                                   \
	struct Gen_t_##ADDR##_p12cd { int a[3]; };                                \
	typedef _STL::pair<const Gen_t_##ADDR##_k4, Gen_t_##ADDR##_p12cd>         \
		Pair##ADDR;                                                           \
	namespace _STL                                                            \
	{                                                                         \
	template<> void _Construct<Pair##ADDR, Pair##ADDR>(                       \
		Pair##ADDR *p, const Pair##ADDR &value );                             \
	}

BFME_PAIR_PAYLOAD( 00195060 )
BFME_PAIR_PAYLOAD( 00363a60 )
BFME_PAIR_PAYLOAD( 0039e0a0 )
BFME_PAIR_PAYLOAD( 003a2460 )
BFME_PAIR_PAYLOAD( 003abf20 )
BFME_PAIR_PAYLOAD( 00607280 )
BFME_PAIR_PAYLOAD( 00608af0 )
BFME_PAIR_PAYLOAD( 0013a700 )

#define BFME_STRIDED_INIT_LOOP( NAME, VALUE, STRIDE )                         \
	struct NAME##Elem { char m_bytes[ STRIDE ]; };                            \
	NAME##Elem *NAME( NAME##Elem *base, unsigned int count, void *extra );    \
	NAME##Elem *NAME( NAME##Elem *base, unsigned int count, void *extra )     \
	{                                                                         \
		NAME##Elem *cursor = base;                                            \
		for ( unsigned int i = 0; i < count; ++i )                            \
		{                                                                     \
			_STL::_Construct( reinterpret_cast<VALUE *>( cursor ),            \
				*static_cast<const VALUE *>( extra ) );                       \
			++cursor;                                                         \
		}                                                                     \
		return cursor;                                                        \
	}

BFME_STRIDED_INIT_LOOP( Rva000E3C10, PlayerTemplate, 0x124 )
BFME_STRIDED_INIT_LOOP( Rva001952C0, Pair00195060, 0x8C )
BFME_STRIDED_INIT_LOOP( Rva00363B00, Pair00363a60, 0xB4 )
BFME_STRIDED_INIT_LOOP( Rva0039E140, Pair0039e0a0, 0x88 )
BFME_STRIDED_INIT_LOOP( Rva003A2530, Pair003a2460, 0xB8 )
BFME_STRIDED_INIT_LOOP( Rva003ABFC0, Pair003abf20, 0xDC )
BFME_STRIDED_INIT_LOOP( Rva00607320, Pair00607280, 0x1F0 )
BFME_STRIDED_INIT_LOOP( Rva00608B90, Pair00608af0, 0x210 )
BFME_STRIDED_INIT_LOOP( Rva007747A0, Pair0013a700, 0x128 )
