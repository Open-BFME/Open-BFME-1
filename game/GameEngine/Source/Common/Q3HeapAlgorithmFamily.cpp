// Thirty-six bodies that make up four heap primitives, each instantiated nine
// times.  The shapes are the SGI/STLport heap algorithms operating on a
// four-byte element with a Compare that is itself one dword wide.
//
// WHAT THE BYTES SHOW.  All four call ONE out-of-line helper taking five cdecl
// dwords -- (first, holeIndex, len, value, comp) -- and cleaning 0x14.  Reading
// the four bodies against that helper:
//
//   * make_heap    : len = last-first; bail when len < 2; parent = (len-2)/2;
//                    call helper(first, parent, len, first[parent], comp) and
//                    walk parent down to zero.  `comp` sits at the THIRD
//                    incoming slot, so the helper-independent parameters after
//                    it are unused (SGI passes _Tp* and _Distance* there).
//   * pop_heap     : *result = *first; helper(first, 0, last-first, value,
//                    comp).  A SIXTH, unused parameter is not decoration --
//                    with five parameters MSVC rewrites the forwarding call
//                    into `jmp` and the body loses its `call`/`add esp,0x14`/
//                    `ret` tail entirely.  The retail `call` PROVES the extra
//                    trailing parameter (SGI's `_Distance*`).
//   * pop_heap_aux : value = *(last-1); *(last-1) = *first;
//                    helper(first, 0, (last-1)-first, value, comp).
//
// TWO AXES, AND THEY CROSS CLEANLY.  Axis one is the helper: nine distinct
// targets, each reached through its own low-RVA ILT thunk.  Axis two shows up
// only in pop_heap_aux, where `comp` is loaded from either the FOURTH or the
// THIRD incoming dword -- the single displacement byte 0x14 vs 0x10.  Every one
// of the nine helpers appears exactly once at each of the two positions, and
// exactly once in make_heap and once in pop_heap: a full 9x4 grid with no
// helper repeated inside a column.  An over-fitted split would have left some
// helper at two offsets in the same column; none does.
//
// IDENTITY IS NOT RECOVERED.  Every name here is derived from an address.  The
// helper pins are address-derived and additive; the target of each was read out
// of the REL32 at the call site and followed through its ILT thunk.
//
// WHAT THE BYTES CANNOT DECIDE.  The element type is only known to be four
// bytes wide and is spelled `int *` here.  The comparator is only known to be
// one dword passed by value; one struct stands in for all nine instantiations,
// because nothing in these bodies distinguishes them -- the comparator is never
// invoked, only forwarded.  Which trailing parameters the helper-independent
// slots hold (SGI's `_Tp*` / `_Distance*` tag pointers) is not observable
// beyond their COUNT, which is what the call-versus-jmp shape fixes.

typedef int *Q3HeapElem;

struct Q3HeapCompare
{
	void *m_state;
};

#define BFME_HEAP_ADJUST_DECL( ADJUST )                                       \
	void ADJUST( Q3HeapElem *first, int holeIndex, int len,                   \
		Q3HeapElem value, Q3HeapCompare comp );

#define BFME_HEAP_MAKE( NAME, ADJUST )                                        \
	void NAME( Q3HeapElem *first, Q3HeapElem *last, Q3HeapCompare comp )      \
	{                                                                         \
		int len = last - first;                                               \
		if ( len < 2 )                                                        \
			return;                                                           \
		int parent = ( len - 2 ) / 2;                                         \
		for ( ;; )                                                            \
		{                                                                     \
			ADJUST( first, parent, len, *( first + parent ), comp );          \
			if ( parent == 0 )                                                \
				return;                                                       \
			--parent;                                                         \
		}                                                                     \
	}

#define BFME_HEAP_POP( NAME, ADJUST )                                         \
	void NAME( Q3HeapElem *first, Q3HeapElem *last, Q3HeapElem *result,       \
		Q3HeapElem value, Q3HeapCompare comp, int * )                         \
	{                                                                         \
		*result = *first;                                                     \
		ADJUST( first, 0, last - first, value, comp );                        \
	}

#define BFME_HEAP_POP_AUX4( NAME, ADJUST )                                    \
	void NAME( Q3HeapElem *first, Q3HeapElem *last, Q3HeapElem *,             \
		Q3HeapCompare comp )                                                  \
	{                                                                         \
		Q3HeapElem value = *( last - 1 );                                     \
		*( last - 1 ) = *first;                                               \
		ADJUST( first, 0, ( last - 1 ) - first, value, comp );                \
	}

#define BFME_HEAP_POP_AUX3( NAME, ADJUST )                                    \
	void NAME( Q3HeapElem *first, Q3HeapElem *last, Q3HeapCompare comp )      \
	{                                                                         \
		Q3HeapElem value = *( last - 1 );                                     \
		*( last - 1 ) = *first;                                               \
		ADJUST( first, 0, ( last - 1 ) - first, value, comp );                \
	}

#define BFME_HEAP_GROUP( ADJUST, MAKE, POP, AUX4, AUX3 )                      \
	BFME_HEAP_ADJUST_DECL( ADJUST )                                           \
	BFME_HEAP_MAKE( MAKE, ADJUST )                                            \
	BFME_HEAP_POP( POP, ADJUST )                                              \
	BFME_HEAP_POP_AUX4( AUX4, ADJUST )                                        \
	BFME_HEAP_POP_AUX3( AUX3, ADJUST )

BFME_HEAP_GROUP( Gen00342D60, Rva00344A60, Rva00344A20, Rva00344AD0, Rva00347D60 )
BFME_HEAP_GROUP( Gen003CDD00, Rva003CE510, Rva003CE4D0, Rva003CE580, Rva003CED10 )
BFME_HEAP_GROUP( Gen00453200, Rva00453BB0, Rva00453B30, Rva00453C90, Rva00454010 )
BFME_HEAP_GROUP( Gen00453290, Rva00453C20, Rva00453B70, Rva00453CD0, Rva00454050 )
BFME_HEAP_GROUP( Gen0047E4F0, Rva00483480, Rva00483410, Rva004834F0, Rva00483720 )
BFME_HEAP_GROUP( Gen00511C10, Rva005125C0, Rva00512550, Rva00512630, Rva00513150 )
BFME_HEAP_GROUP( Gen005135F0, Rva00513B40, Rva00513B00, Rva00513BB0, Rva005147B0 )
BFME_HEAP_GROUP( Gen00530200, Rva00531BE0, Rva00531A00, Rva00531D40, Rva005321D0 )
BFME_HEAP_GROUP( Gen007538A0, Rva00753DD0, Rva00753D90, Rva00753E40, Rva00754550 )
