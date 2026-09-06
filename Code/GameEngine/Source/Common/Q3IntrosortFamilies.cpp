// Twenty-one bodies at the two OUTERMOST layers of an introsort: thirteen
// drivers and eight of the final-insertion passes they hand off to.  Seven of
// the eight are called directly by a driver in this same file, which is why
// they share a translation unit.
//
// WHAT THE BYTES SHOW -- the driver (74 bytes, thirteen copies).
//
//   if ( first != last )
//   {
//       // k = floor(log2(last - first)), spelled as the SGI __lg loop:
//       // for ( k = 0; n != 1; n >>= 1 ) ++k;
//       introsortLoop( first, last, (T *)0, k * 2, comp );
//       finalInsertionSort( first, last, comp );
//   }
//
// Both calls are cdecl and the frame is cleaned ONCE for both (add esp,0x20 =
// 5 + 3 dwords), so neither callee pops.  The third argument to the first
// callee is a literal zero pushed between `last` and the depth -- a null type
// tag, exactly where SGI's `__introsort_loop` takes its `_Tp*`.  `comp` is the
// driver's THIRD parameter, read once into ebx and pushed to both callees.
//
// WHAT THE BYTES SHOW -- the final-insertion pass (72 bytes, eight copies).
//
//   if ( last - first > 16 )
//   {
//       insertionSort( first, first + 16, comp );
//       unguardedInsertionSort( first + 16, last, (T *)0, comp );
//   }
//   else
//       insertionSort( first, last, comp );
//
// The SAME callee is reached from both arms (identical REL32 target at two call
// sites), so the two arms are one function called twice, not two functions --
// that is SGI's `__insertion_sort`, and 16 is its `__stl_threshold`.  The
// second callee again takes a null type tag in third position.  `and ecx,-4`
// before `cmp ecx,0x40` is the compiler's rounding for a signed
// element-difference compared against 16; it is not a byte count in the source.
//
// AXES.  The driver has THREE: the introsort callee, the final-insertion
// callee, and one displacement byte that is the element width -- `sar eax,2`,
// `sar eax,3`, `sar eax,4` for four-, eight- and sixteen-byte elements.
// Thirteen rows, thirteen distinct introsort targets, thirteen distinct
// final-insertion targets: no callee is reused at a second width, so the width
// axis is not absorbing a callee that would otherwise repeat.  The
// final-insertion pass has TWO axes, both callees, and no width axis at all --
// all eight are four-byte, `lea esi,[eax+0x40]` in every copy.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  Callee
// pins are address-derived and additive; each target was read from the REL32 at
// its call site and followed through its ILT thunk where one was in the way.
//
// A NOTE ON THE SEVEN OVERLAPS.  Seven of the eight final-insertion passes are
// the exact target a driver in this file calls.  They are still reached through
// a separate address-derived DECLARATION rather than by naming the definition
// next to them: pointed at the local definition, MSVC inlines the callee and
// the driver grows from 74 bytes to 111.  Retail's `call` says it did not.
//
// WHAT THE BYTES CANNOT DECIDE.  The element TYPE, beyond its width -- the
// drivers never dereference it.  The comparator, beyond being one dword passed
// by value and never invoked here; a single stand-in struct is used for all
// twenty-one, since nothing distinguishes them.  What the null type-tag
// arguments actually are is unobservable past their position and count.

struct Q3SortItem003CDC60
{
	char m_pad30[ 0x30 ];
	int m_key;
	char m_pad34[ 5 ];
	char m_tie;
};

struct Q3SortElem4
{
	Q3SortItem003CDC60 *m_item;
};

struct Q3SortElem8;

struct Q3SortCompare
{
	void *m_state;
	bool operator()( Q3SortElem4 a, Q3SortElem4 b ) const
	{
		int a_key = a.m_item->m_key;
		int b_key = b.m_item->m_key;
		if( b_key > a_key )
			return true;
		if( b_key < a_key )
			return false;
		char a_tie = a.m_item->m_tie;
		char b_tie = b.m_item->m_tie;
		return b_tie < a_tie;
	}
	bool operator()( const Q3SortElem8 &left, const Q3SortElem8 &right ) const;
};
struct Q3SortElem8  { int m_a; float m_b; };
struct Q3SortElem16 { int m_a, m_b, m_c, m_d; };

bool Q3SortCompare::operator()( const Q3SortElem8 &left, const Q3SortElem8 &right ) const
{
	return left.m_b < right.m_b;
}

#define BFME_FINAL_INSERTION( NAME, INSERT, UNGUARDED )                        \
	void INSERT( Q3SortElem4 *first, Q3SortElem4 *last, Q3SortCompare comp );  \
	void UNGUARDED( Q3SortElem4 *first, Q3SortElem4 *last, Q3SortElem4 *,      \
		Q3SortCompare comp );                                                  \
	void NAME( Q3SortElem4 *first, Q3SortElem4 *last, Q3SortCompare comp )     \
	{                                                                          \
		if ( last - first > 16 )                                               \
		{                                                                      \
			INSERT( first, first + 16, comp );                                 \
			UNGUARDED( first + 16, last, (Q3SortElem4 *)0, comp );             \
		}                                                                      \
		else                                                                   \
		{                                                                      \
			INSERT( first, last, comp );                                       \
		}                                                                      \
	}

BFME_FINAL_INSERTION( Rva00453EF0, Gen004539D0, Gen00453090 )
BFME_FINAL_INSERTION( Rva00453F50, Gen00453A80, Gen00453180 )
BFME_FINAL_INSERTION( Rva00754740, Gen00754430, Gen007537C0 )
BFME_FINAL_INSERTION( Rva009CD6F0, Gen009CD4F0, Gen009CD1A0 )
BFME_FINAL_INSERTION( Rva00347CD0, Gen00344970, Gen00342CE0 )
BFME_FINAL_INSERTION( Rva003CFA00, Gen003CEC30, Gen003CDC60 )
BFME_FINAL_INSERTION( Rva00483DA0, Gen00483B90, Gen0047E480 )
BFME_FINAL_INSERTION( Rva00513980, Gen00513410, Gen00511B90 )

void Gen003CDC60( Q3SortElem4 *first, Q3SortElem4 *last, Q3SortCompare comp )
{
	if( first != last )
	{
		Q3SortElem4 *i = first;
		for( ;; )
		{
			Q3SortElem4 value = *i;
			Q3SortElem4 *cur = i;
			Q3SortElem4 *next = i - 1;
			while( comp( *next, value ) )
			{
				*cur = *next;
				cur = next;
				--next;
			}
			++i;
			*cur = value;
			if( i == last )
				break;
		}
	}
}

#define BFME_SORT_DRIVER( NAME, ELEM, INTRO, FINAL )                           \
	void INTRO( ELEM *first, ELEM *last, ELEM *, int depth,                    \
		Q3SortCompare comp );                                                  \
	void NAME( ELEM *first, ELEM *last, Q3SortCompare comp )                   \
	{                                                                          \
		if ( first != last )                                                   \
		{                                                                      \
			int n = last - first;                                              \
			int k;                                                             \
			for ( k = 0; n != 1; n >>= 1 )                                     \
				++k;                                                           \
			INTRO( first, last, (ELEM *)0, k * 2, comp );                      \
			FINAL( first, last, comp );                                        \
		}                                                                      \
	}

#define BFME_SORT_FINAL_DECL( NAME, ELEM )                                     \
	void NAME( ELEM *first, ELEM *last, Q3SortCompare comp );

BFME_SORT_FINAL_DECL( Gen00453EF0, Q3SortElem4 )
BFME_SORT_FINAL_DECL( Gen00453F50, Q3SortElem4 )
BFME_SORT_FINAL_DECL( Gen00754740, Q3SortElem4 )
BFME_SORT_FINAL_DECL( Gen009CD6F0, Q3SortElem4 )
BFME_SORT_FINAL_DECL( Gen00347CD0, Q3SortElem4 )
BFME_SORT_FINAL_DECL( Gen003CFA00, Q3SortElem4 )
BFME_SORT_FINAL_DECL( Gen00483DA0, Q3SortElem4 )
BFME_SORT_FINAL_DECL( Gen00476880, Q3SortElem16 )
BFME_SORT_FINAL_DECL( Gen009F3CE0, Q3SortElem8 )
BFME_SORT_FINAL_DECL( Gen009F3D30, Q3SortElem8 )
BFME_SORT_FINAL_DECL( Gen00261A20, Q3SortElem8 )
BFME_SORT_FINAL_DECL( Gen00438270, Q3SortElem8 )
BFME_SORT_FINAL_DECL( Gen00574E70, Q3SortElem16 )

BFME_SORT_DRIVER( Rva00456860, Q3SortElem4,  Gen004566F0, Gen00453EF0 )
BFME_SORT_DRIVER( Rva004568C0, Q3SortElem4,  Gen004567A0, Gen00453F50 )
BFME_SORT_DRIVER( Rva00477960, Q3SortElem16, Gen004775D0, Gen00476880 )
BFME_SORT_DRIVER( Rva00755820, Q3SortElem4,  Gen00755050, Gen00754740 )
BFME_SORT_DRIVER( Rva009CDB40, Q3SortElem4,  Gen009CDAA0, Gen009CD6F0 )
BFME_SORT_DRIVER( Rva009F3F80, Q3SortElem8,  Gen009F3DC0, Gen009F3CE0 )
BFME_SORT_DRIVER( Rva009F3FD0, Q3SortElem8,  Gen009F3EA0, Gen009F3D30 )
BFME_SORT_DRIVER( Rva00261C30, Q3SortElem8,  Gen00261AE0, Gen00261A20 )
BFME_SORT_DRIVER( Rva0034C070, Q3SortElem4,  Gen0034BFC0, Gen00347CD0 )
BFME_SORT_DRIVER( Rva003D1880, Q3SortElem4,  Gen003D15A0, Gen003CFA00 )
BFME_SORT_DRIVER( Rva00438980, Q3SortElem8,  Gen004388C0, Gen00438270 )
BFME_SORT_DRIVER( Rva00484020, Q3SortElem4,  Gen00483F70, Gen00483DA0 )
BFME_SORT_DRIVER( Rva00575980, Q3SortElem16, Gen00575450, Gen00574E70 )

Q3SortElem8 *Gen009F3280( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 value, Q3SortCompare comp );
void Gen009F3B00( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 *middle, int zero, Q3SortCompare comp );

static __forceinline const Q3SortElem8 *Gen009F3DC0Median( const Q3SortElem8 *a,
	const Q3SortElem8 *b, const Q3SortElem8 *c, Q3SortCompare comp )
{
	if( comp( *a, *b ) )
	{
		if( comp( *b, *c ) )
			return b;
		if( comp( *a, *c ) )
			return c;
		return a;
	}
	if( comp( *a, *c ) )
		return a;
	if( comp( *b, *c ) )
		return c;
	return b;
}

void Gen009F3DC0( Q3SortElem8 *first, Q3SortElem8 *last,
	Q3SortElem8 *, int depthLimit, Q3SortCompare comp )
{
	while( last - first > 16 )
	{
		if( depthLimit == 0 )
		{
			Gen009F3B00( first, last, last, 0, comp );
			return;
		}
		--depthLimit;
		Q3SortElem8 *cut = Gen009F3280( first, last,
			*Gen009F3DC0Median( first, first + ( last - first ) / 2,
				last - 1, comp ), comp );
		Gen009F3DC0( cut, last, (Q3SortElem8 *)0, depthLimit, comp );
		last = cut;
	}
}
