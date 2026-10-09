// Five 78-byte __cdecl functions with the shape of STLport's
// `__final_insertion_sort`: over a threshold, sort the first sixteen elements
// and hand the remainder to an unguarded pass; under it, sort the whole range.
//
//     ecx = last - first ; ecx &= ~(SIZE-1) ; if ( ecx <= 16*SIZE ) goto small
//     mid = first + 16*SIZE
//     sort( first, mid, comp )
//     tail( mid, last, 0, comp )      <- FOUR arguments; the third is a zero
//     return
//   small: sort( first, last, comp )
//
// WHAT THE `and` MEANS, because it is the whole puzzle.  Masking a pointer
// DIFFERENCE with ~(SIZE-1) looks like source-level rounding and is not: MSVC
// rewrites `(last - first) > 16` on a T* of size SIZE into
// `((last-first) & ~(SIZE-1)) > 16*SIZE`, trading the arithmetic shift the
// signed division would need for a mask.  Read that way the two constants stop
// being independent -- 0xFFFFFFF0 with 0x100 and 0xFFFFFFF8 with 0x80 are the
// SAME source constant 16 at two element sizes, and `jle` being signed is the
// signed ptrdiff_t comparison, not an unsigned one.  Probing the plain
// `last - first > 16` spelling reproduces the mask, the limit and the `lea`.
//
// The fourth argument of the tail call is a hard zero pushed between `last` and
// the comparator.  A dead pointer argument in that position is STLport's
// value-type dummy -- `__unguarded_insertion_sort(first, last, __VALUE_TYPE, comp)`
// -- and the position is the only evidence for it, so it is declared as an
// unnamed pointer of the element type and passed as 0.
//
// TWO AXES: the element size (16 bytes in two rows, 8 in three) and the callee
// pair.  Five distinct pairs; within each row the SMALL branch calls the same
// address as the big branch's first call, which is what makes the two branches
// one function rather than two.
//
// IDENTITY IS NOT RECOVERED.  The real thing is a template instantiation whose
// mangled name encodes the element type and comparator; nothing in these bytes
// names either, so the callees are declared as ordinary functions with
// address-derived names and the comparator is typed only by its WIDTH (one
// dword, passed by value).

// The retail calls below reach the existing matched instantiations. Keep
// declarations only; each cast preserves the caller's address-derived ABI.
struct Q3SortElem16;
struct Q3SortCompare { void *m_state; };
struct BfmeElemQR;
void __insertion_sort(Q3SortElem16 *, Q3SortElem16 *, Q3SortCompare);
void bfmeEachQR(BfmeElemQR *, BfmeElemQR *, int, void *);

struct BfmeScoreEntry;
struct BfmeScoreEntryLess {};
void Rva005742C0(BfmeScoreEntry *, BfmeScoreEntry *, BfmeScoreEntryLess);
void Rva00571AB0(BfmeScoreEntry *, BfmeScoreEntry *, BfmeScoreEntry *, BfmeScoreEntryLess);

struct S4SortElem8;
struct S4Cmp00575AA0 { void *m_bfmeState; };
void S4InsertionSort005759E0(S4SortElem8 *, S4SortElem8 *, S4Cmp00575AA0);

struct BfmeSortPair;
struct BfmeSortCompare {};
struct BfmeSortCompareDescending {};
struct S3Elem009F3050;
struct S3Less009F3050 {};
struct S3Elem009F30B0;
struct S3Greater009F30B0 {};
void Gen009F3050(S3Elem009F3050 *, S3Elem009F3050 *, S3Elem009F3050 *, S3Less009F3050);
void Gen009F30B0(S3Elem009F30B0 *, S3Elem009F30B0 *, S3Elem009F30B0 *, S3Greater009F30B0);

namespace _STL
{
template <class Iter, class T, class Comp>
void __unguarded_insertion_sort_aux(Iter, Iter, T *, Comp);
template <class Iter, class Comp>
void __insertion_sort(Iter, Iter, Comp);
}

class Rva00476880Elem { public: char m_pad[ 16 ]; };

void Rva00476880( Rva00476880Elem *first, Rva00476880Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		__insertion_sort( reinterpret_cast<Q3SortElem16 *>(first), reinterpret_cast<Q3SortElem16 *>(first + 16), *reinterpret_cast<Q3SortCompare *>(&comp) );
		bfmeEachQR( reinterpret_cast<BfmeElemQR *>(first + 16), reinterpret_cast<BfmeElemQR *>(last), 0, comp );
	}
	else
		__insertion_sort( reinterpret_cast<Q3SortElem16 *>(first), reinterpret_cast<Q3SortElem16 *>(last), *reinterpret_cast<Q3SortCompare *>(&comp) );
}

class Rva00574E70Elem { public: char m_pad[ 16 ]; };

void Rva00574E70( Rva00574E70Elem *first, Rva00574E70Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		Rva005742C0( reinterpret_cast<BfmeScoreEntry *>(first), reinterpret_cast<BfmeScoreEntry *>(first + 16), *reinterpret_cast<BfmeScoreEntryLess *>(&comp) );
		Rva00571AB0( reinterpret_cast<BfmeScoreEntry *>(first + 16), reinterpret_cast<BfmeScoreEntry *>(last), 0, *reinterpret_cast<BfmeScoreEntryLess *>(&comp) );
	}
	else
		Rva005742C0( reinterpret_cast<BfmeScoreEntry *>(first), reinterpret_cast<BfmeScoreEntry *>(last), *reinterpret_cast<BfmeScoreEntryLess *>(&comp) );
}

class Rva00576FF0Elem { public: char m_pad[ 8 ]; };

void Rva00576FF0( Rva00576FF0Elem *first, Rva00576FF0Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		S4InsertionSort005759E0( reinterpret_cast<S4SortElem8 *>(first), reinterpret_cast<S4SortElem8 *>(first + 16), *reinterpret_cast<S4Cmp00575AA0 *>(&comp) );
		_STL::__unguarded_insertion_sort_aux<S4SortElem8 *, S4SortElem8, S4Cmp00575AA0>( reinterpret_cast<S4SortElem8 *>(first + 16), reinterpret_cast<S4SortElem8 *>(last), 0, *reinterpret_cast<S4Cmp00575AA0 *>(&comp) );
	}
	else
		S4InsertionSort005759E0( reinterpret_cast<S4SortElem8 *>(first), reinterpret_cast<S4SortElem8 *>(last), *reinterpret_cast<S4Cmp00575AA0 *>(&comp) );
}

class Rva009F3CE0Elem { public: char m_pad[ 8 ]; };

void Rva009F3CE0( Rva009F3CE0Elem *first, Rva009F3CE0Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		_STL::__insertion_sort<BfmeSortPair *, BfmeSortCompare>( reinterpret_cast<BfmeSortPair *>(first), reinterpret_cast<BfmeSortPair *>(first + 16), *reinterpret_cast<BfmeSortCompare *>(&comp) );
		Gen009F3050( reinterpret_cast<S3Elem009F3050 *>(first + 16), reinterpret_cast<S3Elem009F3050 *>(last), 0, *reinterpret_cast<S3Less009F3050 *>(&comp) );
	}
	else
		_STL::__insertion_sort<BfmeSortPair *, BfmeSortCompare>( reinterpret_cast<BfmeSortPair *>(first), reinterpret_cast<BfmeSortPair *>(last), *reinterpret_cast<BfmeSortCompare *>(&comp) );
}

class Rva009F3D30Elem { public: char m_pad[ 8 ]; };

void Rva009F3D30( Rva009F3D30Elem *first, Rva009F3D30Elem *last, void *comp )
{
	if( last - first > 16 )
	{
		_STL::__insertion_sort<BfmeSortPair *, BfmeSortCompareDescending>( reinterpret_cast<BfmeSortPair *>(first), reinterpret_cast<BfmeSortPair *>(first + 16), *reinterpret_cast<BfmeSortCompareDescending *>(&comp) );
		Gen009F30B0( reinterpret_cast<S3Elem009F30B0 *>(first + 16), reinterpret_cast<S3Elem009F30B0 *>(last), 0, *reinterpret_cast<S3Greater009F30B0 *>(&comp) );
	}
	else
		_STL::__insertion_sort<BfmeSortPair *, BfmeSortCompareDescending>( reinterpret_cast<BfmeSortPair *>(first), reinterpret_cast<BfmeSortPair *>(last), *reinterpret_cast<BfmeSortCompareDescending *>(&comp) );
}

