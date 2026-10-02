// batch51 ASCII-family audit: no S4 object is instantiated in this forwarder TU.
// Sixty-two __cdecl free functions that forward every one of their arguments to
// one direct call and insert a constant zero at a fixed position.  Three
// families, distinguished only by how many arguments they carry and where the
// zero lands; they share no callee with each other.
//
//     26 bytes:  f(a,b,c)   -> callee(a, b, 0, c)
//     28 bytes:  f(a,b,c)   -> callee(a, b, c, 0, 0)
//     31 bytes:  f(a,b,c,d) -> callee(a, b, c, 0, d)
//
// WHAT THE BYTES SHOW.  Each body reads its arguments at [esp+4] upward, never
// touches ecx, ends in a plain `ret`, and pops the call's arguments itself with
// `add esp,N`: __cdecl on both sides, at the arities the pushes and the `add`
// count out.  The zeros are `push 0` immediates at a fixed slot, so they are
// literal constants in the source rather than anything read from memory; a null
// pointer and an integer zero are the same two bytes here and the bytes cannot
// tell them apart, so the argument is spelled as the plain 0 that asserts less.
// Nothing is done with eax after the call, so the result -- if there is one --
// is not used by these bodies, and they are spelled `void`.
//
// THE ONLY AXIS WITHIN EACH FAMILY IS THE REL32 TARGET, and here it is almost
// one callee per member: twenty-two, twenty and twenty distinct callees for
// twenty-two, twenty and twenty members.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; callee pins are
// additive and address-derived.

#define BFME_ZERO_THIRD_CALLEE( ADDR )                                       \
	void gen##ADDR( void *a, void *b, int zero, void *c );

#define BFME_ZERO_THIRD_FORWARDER( NAME, CALLEE )                            \
	void NAME( void *a, void *b, void *c )                                   \
	{                                                                        \
		CALLEE( a, b, 0, c );                                                \
	}

// 0x00342CE0 IS DEFINED UNDER ITS OWN NAME in
// game/GameEngine/Source/Common/S4UnguardedInsertionSort.cpp, whose two
// parameters are `int *first` and a one-dword by-value range.  The forwarder
// here must therefore name `s4uis00342CE0`, and it calls it through a cast to
// the four-dword shape this file's own argument pushes produce -- the cast is
// what keeps the caller's `add esp,0x10` while the emitted symbol is the
// defining one.  Only the struct is forward-declared: its layout lives in the
// defining TU.
#define BFME_ZERO_THIRD_S4UIS_DECL( ADDR )                                      \
	struct S4Range##ADDR;                                                       \
	void s4uis##ADDR( int *first, S4Range##ADDR range );

#define BFME_ZERO_THIRD_S4UIS_FORWARDER( NAME, ADDR )                           \
	void NAME( void *a, void *b, void *c )                                      \
	{                                                                           \
		reinterpret_cast<void ( __cdecl * )( void *, void *, void *, void * )>( \
			&s4uis##ADDR )( a, b, 0, c );                                       \
	}

#define BFME_ZERO_TAIL_CALLEE( ADDR )                                        \
	void gen##ADDR( void *a, void *b, void *c, int zero, int alsoZero );

#define BFME_ZERO_TAIL_FORWARDER( NAME, CALLEE )                             \
	void NAME( void *a, void *b, void *c )                                   \
	{                                                                        \
		CALLEE( a, b, c, 0, 0 );                                             \
	}

#define BFME_ZERO_FOURTH_CALLEE( ADDR )                                      \
	void gen##ADDR( void *a, void *b, void *c, int zero, void *d );

#define BFME_ZERO_FOURTH_FORWARDER( NAME, CALLEE )                           \
	void NAME( void *a, void *b, void *c, void *d )                          \
	{                                                                        \
		CALLEE( a, b, c, 0, d );                                             \
	}


// batch50 scratch declarations for the two STLport S4 callees.  The other
// forwarder families retain their existing address-derived declarations.
struct S4SortElem20;
struct S4Cmp002EB8E0 { int m_bfmeSlot; };
namespace _STL
{
template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator, RandomAccessIterator, Compare, Tp *, Distance *);
template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator, RandomAccessIterator,
    RandomAccessIterator, Tp *, Compare);
}
#define BFME_CANONICAL_MAKE_HEAP(a,b,c,z0,z1) \
    _STL::__make_heap((S4SortElem20 *)(a), (S4SortElem20 *)(b), \
        *(S4Cmp002EB8E0 *)&(c), (S4SortElem20 *)0, (int *)0)
#define BFME_CANONICAL_PARTIAL_SORT(a,b,c,z0,d) \
    _STL::__partial_sort((S4SortElem20 *)(a), (S4SortElem20 *)(b), \
        (S4SortElem20 *)(c), (S4SortElem20 *)0, *(S4Cmp002EB8E0 *)&(d))

BFME_ZERO_THIRD_CALLEE( 002E0730 )
BFME_ZERO_THIRD_CALLEE( 002E0D70 )
BFME_ZERO_THIRD_CALLEE( 002EA750 )
BFME_ZERO_THIRD_CALLEE( 002EADF0 )
BFME_ZERO_THIRD_S4UIS_DECL( 00342CE0 )
BFME_ZERO_THIRD_CALLEE( 00363B80 )
BFME_ZERO_THIRD_CALLEE( 00364980 )
BFME_ZERO_THIRD_CALLEE( 003CDC60 )
BFME_ZERO_THIRD_CALLEE( 00453090 )
BFME_ZERO_THIRD_CALLEE( 00453180 )
BFME_ZERO_THIRD_CALLEE( 004742C0 )
BFME_ZERO_THIRD_CALLEE( 00474A90 )
BFME_ZERO_THIRD_CALLEE( 00511B90 )
BFME_ZERO_THIRD_CALLEE( 0052FF20 )
BFME_ZERO_THIRD_CALLEE( 00530050 )
BFME_ZERO_THIRD_CALLEE( 00531D80 )
BFME_ZERO_THIRD_CALLEE( 005719B0 )
BFME_ZERO_THIRD_CALLEE( 00571AB0 )
BFME_ZERO_THIRD_CALLEE( 00575750 )
BFME_ZERO_THIRD_CALLEE( 007537C0 )
BFME_ZERO_THIRD_CALLEE( 008CBDF0 )

BFME_ZERO_THIRD_FORWARDER( rva002E0B70ZeroThirdForwarder, gen002E0730 )
BFME_ZERO_THIRD_FORWARDER( rva002E10F0ZeroThirdForwarder, gen002E0D70 )
BFME_ZERO_THIRD_FORWARDER( rva002EABA0ZeroThirdForwarder, gen002EA750 )
BFME_ZERO_THIRD_FORWARDER( rva002EAEC0ZeroThirdForwarder, gen002EADF0 )
BFME_ZERO_THIRD_S4UIS_FORWARDER( rva00344A00ZeroThirdForwarder, 00342CE0 )
BFME_ZERO_THIRD_FORWARDER( rva003647B0ZeroThirdForwarder, gen00363B80 )
BFME_ZERO_THIRD_FORWARDER( rva00365500ZeroThirdForwarder, gen00364980 )
BFME_ZERO_THIRD_FORWARDER( rva003CE400ZeroThirdForwarder, gen003CDC60 )
BFME_ZERO_THIRD_FORWARDER( rva00453A60ZeroThirdForwarder, gen00453090 )
BFME_ZERO_THIRD_FORWARDER( rva00453B10ZeroThirdForwarder, gen00453180 )
BFME_ZERO_THIRD_FORWARDER( rva004748A0ZeroThirdForwarder, gen004742C0 )
BFME_ZERO_THIRD_FORWARDER( rva004758D0ZeroThirdForwarder, gen00474A90 )

// 0x0047E480 is not an anonymous body: the ledger's defining name is
// ?bfmeSortZV@@YAXPAH00P6ADHH@Z@Z, declared and defined by name in
// game/GameEngine/Source/Common/BfmeConv1886.cpp.  Same four arguments at the
// same widths (int*, int*, int*, comparator pointer), so the forwarder that
// calls it is unchanged.  The forwarder's own parameters are void*, so the
// casts below are compile-time only: the four pushed dwords are identical.
void bfmeSortZV( int *first, int *last, int *hint,
	char (__cdecl *comp)(int, int) );
#define BFME_ZERO_THIRD_SORT_ZV( A, B, ZERO, C )                              \
	bfmeSortZV( (int *)(A), (int *)(B), (int *)(ZERO),                         \
		(char (__cdecl *)(int, int))(C) )

BFME_ZERO_THIRD_FORWARDER( rva004833F0ZeroThirdForwarder,                        \
	BFME_ZERO_THIRD_SORT_ZV )
BFME_ZERO_THIRD_FORWARDER( rva00512500ZeroThirdForwarder, gen00511B90 )
BFME_ZERO_THIRD_FORWARDER( rva00531790ZeroThirdForwarder, gen0052FF20 )
BFME_ZERO_THIRD_FORWARDER( rva00531840ZeroThirdForwarder, gen00530050 )
BFME_ZERO_THIRD_FORWARDER( rva00532210ZeroThirdForwarder, gen00531D80 )
BFME_ZERO_THIRD_FORWARDER( rva005724B0ZeroThirdForwarder, gen005719B0 )
BFME_ZERO_THIRD_FORWARDER( rva005725C0ZeroThirdForwarder, gen00571AB0 )
BFME_ZERO_THIRD_FORWARDER( rva00575A30ZeroThirdForwarder, gen00575750 )
BFME_ZERO_THIRD_FORWARDER( rva00753CF0ZeroThirdForwarder, gen007537C0 )
BFME_ZERO_THIRD_FORWARDER( rva008CC540ZeroThirdForwarder, gen008CBDF0 )

BFME_ZERO_TAIL_CALLEE( 00261140 )
BFME_ZERO_TAIL_CALLEE( 002E0CD0 )
BFME_ZERO_TAIL_CALLEE( 00344A60 )
BFME_ZERO_TAIL_CALLEE( 003648E0 )
BFME_ZERO_TAIL_CALLEE( 003CE510 )
BFME_ZERO_TAIL_CALLEE( 00437D80 )
BFME_ZERO_TAIL_CALLEE( 00453BB0 )
BFME_ZERO_TAIL_CALLEE( 00453C20 )
BFME_ZERO_TAIL_CALLEE( 004749F0 )
BFME_ZERO_TAIL_CALLEE( 00483480 )
BFME_ZERO_TAIL_CALLEE( 005125C0 )
BFME_ZERO_TAIL_CALLEE( 00513B40 )
BFME_ZERO_TAIL_CALLEE( 00531B20 )
BFME_ZERO_TAIL_CALLEE( 00531BE0 )
BFME_ZERO_TAIL_CALLEE( 00531C50 )
BFME_ZERO_TAIL_CALLEE( 005726F0 )
BFME_ZERO_TAIL_CALLEE( 005727E0 )
BFME_ZERO_TAIL_CALLEE( 00575AA0 )
BFME_ZERO_TAIL_CALLEE( 00753DD0 )

BFME_ZERO_TAIL_FORWARDER( rva00261310ZeroTailForwarder, gen00261140 )
BFME_ZERO_TAIL_FORWARDER( rva002E10C0ZeroTailForwarder, gen002E0CD0 )
BFME_ZERO_TAIL_FORWARDER( rva002EAE60ZeroTailForwarder, BFME_CANONICAL_MAKE_HEAP )
BFME_ZERO_TAIL_FORWARDER( rva00347D30ZeroTailForwarder, gen00344A60 )
BFME_ZERO_TAIL_FORWARDER( rva003654D0ZeroTailForwarder, gen003648E0 )
BFME_ZERO_TAIL_FORWARDER( rva003CECE0ZeroTailForwarder, gen003CE510 )
BFME_ZERO_TAIL_FORWARDER( rva00437EE0ZeroTailForwarder, gen00437D80 )
BFME_ZERO_TAIL_FORWARDER( rva00453FB0ZeroTailForwarder, gen00453BB0 )
BFME_ZERO_TAIL_FORWARDER( rva00453FE0ZeroTailForwarder, gen00453C20 )
BFME_ZERO_TAIL_FORWARDER( rva004758A0ZeroTailForwarder, gen004749F0 )
BFME_ZERO_TAIL_FORWARDER( rva004836F0ZeroTailForwarder, gen00483480 )
BFME_ZERO_TAIL_FORWARDER( rva00513120ZeroTailForwarder, gen005125C0 )
BFME_ZERO_TAIL_FORWARDER( rva00514780ZeroTailForwarder, gen00513B40 )
BFME_ZERO_TAIL_FORWARDER( rva005320F0ZeroTailForwarder, gen00531B20 )
BFME_ZERO_TAIL_FORWARDER( rva00532120ZeroTailForwarder, gen00531BE0 )
BFME_ZERO_TAIL_FORWARDER( rva00532150ZeroTailForwarder, gen00531C50 )
BFME_ZERO_TAIL_FORWARDER( rva00572E50ZeroTailForwarder, gen005726F0 )
BFME_ZERO_TAIL_FORWARDER( rva00572EB0ZeroTailForwarder, gen005727E0 )
BFME_ZERO_TAIL_FORWARDER( rva00577060ZeroTailForwarder, gen00575AA0 )
BFME_ZERO_TAIL_FORWARDER( rva00754520ZeroTailForwarder, gen00753DD0 )

BFME_ZERO_FOURTH_CALLEE( 00261920 )
BFME_ZERO_FOURTH_CALLEE( 002E1710 )
BFME_ZERO_FOURTH_CALLEE( 0034B8D0 )
BFME_ZERO_FOURTH_CALLEE( 003667E0 )
BFME_ZERO_FOURTH_CALLEE( 003D00E0 )
BFME_ZERO_FOURTH_CALLEE( 004384D0 )
BFME_ZERO_FOURTH_CALLEE( 00455E20 )
BFME_ZERO_FOURTH_CALLEE( 00455EC0 )
BFME_ZERO_FOURTH_CALLEE( 004768F0 )
BFME_ZERO_FOURTH_CALLEE( 00483E00 )
BFME_ZERO_FOURTH_CALLEE( 00513A70 )
BFME_ZERO_FOURTH_CALLEE( 00515550 )
BFME_ZERO_FOURTH_CALLEE( 00532CC0 )
BFME_ZERO_FOURTH_CALLEE( 00532DF0 )
BFME_ZERO_FOURTH_CALLEE( 00532F40 )
BFME_ZERO_FOURTH_CALLEE( 00574330 )
BFME_ZERO_FOURTH_CALLEE( 00574410 )
BFME_ZERO_FOURTH_CALLEE( 00577690 )
BFME_ZERO_FOURTH_CALLEE( 00754C60 )

BFME_ZERO_FOURTH_FORWARDER( rva00261A80ZeroFourthForwarder, gen00261920 )
BFME_ZERO_FOURTH_FORWARDER( rva002E1990ZeroFourthForwarder, gen002E1710 )
BFME_ZERO_FOURTH_FORWARDER( rva002EB960ZeroFourthForwarder, BFME_CANONICAL_PARTIAL_SORT )
BFME_ZERO_FOURTH_FORWARDER( rva0034BF90ZeroFourthForwarder, gen0034B8D0 )
BFME_ZERO_FOURTH_FORWARDER( rva00366940ZeroFourthForwarder, gen003667E0 )
BFME_ZERO_FOURTH_FORWARDER( rva003D1320ZeroFourthForwarder, gen003D00E0 )
BFME_ZERO_FOURTH_FORWARDER( rva00438640ZeroFourthForwarder, gen004384D0 )
BFME_ZERO_FOURTH_FORWARDER( rva00456630ZeroFourthForwarder, gen00455E20 )
BFME_ZERO_FOURTH_FORWARDER( rva00456660ZeroFourthForwarder, gen00455EC0 )
BFME_ZERO_FOURTH_FORWARDER( rva004771B0ZeroFourthForwarder, gen004768F0 )
BFME_ZERO_FOURTH_FORWARDER( rva00483F40ZeroFourthForwarder, gen00483E00 )
BFME_ZERO_FOURTH_FORWARDER( rva00514750ZeroFourthForwarder, gen00513A70 )
BFME_ZERO_FOURTH_FORWARDER( rva005156A0ZeroFourthForwarder, gen00515550 )
BFME_ZERO_FOURTH_FORWARDER( rva00533150ZeroFourthForwarder, gen00532CC0 )
BFME_ZERO_FOURTH_FORWARDER( rva00533180ZeroFourthForwarder, gen00532DF0 )
BFME_ZERO_FOURTH_FORWARDER( rva005331B0ZeroFourthForwarder, gen00532F40 )
BFME_ZERO_FOURTH_FORWARDER( rva00574EE0ZeroFourthForwarder, gen00574330 )
BFME_ZERO_FOURTH_FORWARDER( rva00574F10ZeroFourthForwarder, gen00574410 )
BFME_ZERO_FOURTH_FORWARDER( rva00577730ZeroFourthForwarder, gen00577690 )
BFME_ZERO_FOURTH_FORWARDER( rva00754F40ZeroFourthForwarder, gen00754C60 )

