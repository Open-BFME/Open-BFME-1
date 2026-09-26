// cl: -GX-
// stlport
//
// Fourteen bodies from three layers of STLport's `sort` over element widths the
// earlier introsort lanes did not reach.  All three are instantiated from the
// VENDORED header, not replicated: the shapes below say what the retail bytes
// show, and the header supplies the code.
//
// WHAT THE BYTES SHOW -- __final_insertion_sort (91/92 bytes, five copies).
//
//     if ( last - first > 16 ) { insertion( first, first + 16, comp );
//                                unguarded( first + 16, last, (T *)0, comp ); }
//     else                       insertion( first, last, comp );
//
// The same shape Q3IntrosortFamilies.cpp landed at a four-byte element, where
// the element-difference is a `sar`.  Here it is a MAGIC MULTIPLY: 0x2AAAAAAB
// with `sar edx,1` divides the byte span by twelve, 0x66666667 with `sar edx,3`
// divides it by twenty, and the matching `lea edi,[esi+0xC0]` / `[esi+0x140]`
// is sixteen elements at those widths.  That fixes the element WIDTH and
// nothing else about the element; `S4SortElem12`/`S4SortElem20` are stand-ins.
// One `add esp,0x1C` retires seven dwords for both callees, so both are __cdecl
// and neither pops -- and the SAME callee address appears at both insertion
// call sites, so the two arms are one function called twice.
//
// WHAT THE BYTES SHOW -- __make_heap (103 bytes, five copies).
//
//     len = last - first; if ( len < 2 ) return;
//     for ( parent = (len - 2) / 2; ; --parent ) {
//         adjust( first, parent, len, *(first + parent), comp );
//         if ( parent == 0 ) return; }
//
// `sar ebx,3` on the byte span is an eight-byte element, and the callee is
// handed the element as TWO pushed dwords read from `[ebp+esi*8]` and
// `[ebp+esi*8+4]` -- six dwords per call, `add esp,0x18` -- which is
// __adjust_heap's by-value `_Tp __value`.  The loop is the compiler's rewrite
// of STLport's `while (true) { ...; if (__parent == 0) return; __parent--; }`:
// the zero test sits AFTER the call, not before it.
//
// WHAT THE BYTES SHOW -- __push_heap (98 bytes, four copies).
//
//     parent = (hole - 1) / 2;
//     while ( hole > top && comp( first[parent], value ) ) {
//         first[hole] = first[parent]; hole = parent; parent = (hole - 1) / 2; }
//     first[hole] = value;
//
// Five arguments, and the fifth is the comparator: `lea ecx,[esp+0x2C]` with
// six dwords pushed is the address of argument five, so the predicate is a
// __thiscall member called on the by-value functor IN PLACE -- no copy is made,
// which is what tells this apart from a body that passes the functor onward.
// `lea eax,[edi-1] / cdq / sub eax,edx / sar eax,1` is the signed divide by two
// the source spells as `(__holeIndex - 1) / 2`.
//
// THE COMPARATOR IS FOUR BYTES in the two bodies that pass it on -- one pushed
// dword in __final_insertion_sort and in __make_heap.  __push_heap never passes
// it, so its width is unobservable there and four is assumed for consistency.
//
// A CROSS-CHECK BETWEEN LANES.  The four __push_heap predicates are the same
// four retail addresses that S4UnguardedInsertionSort.cpp's four bodies call:
// 0x0033D5E0, 0x00451F60, 0x00451E90, 0x00752B80.  Each address therefore
// belongs to ONE sort instantiation seen twice, which is why one comparator
// type per address carries the whole axis.
//
// IDENTITY IS NOT RECOVERED.  Every comparator is named after the retail body
// that uses it and is DECLARED, never defined; every element stand-in asserts
// only the width the bytes fix.  The callee pins are address-derived: each was
// read from the REL32 at its call site and followed through its ILT thunk.
//
// WHAT THE BYTES CANNOT DECIDE.  The element TYPE beyond its width -- these
// three layers move elements with dword copies and never touch a member.  What
// the comparators actually compare, beyond taking two elements by value and
// returning a byte-wide result tested with `test al,al`.

#include <algorithm>

struct S4SortElem12 { int m_a, m_b, m_c; };
struct S4SortElem20 { int m_a, m_b, m_c, m_d, m_e; };
struct S4SortElem8  { int m_a, m_b; };

#define S4_FINAL_INSERTION( NAME, ELEM )                                       \
	struct S4Cmp##NAME                                                         \
	{                                                                          \
		void *m_state;                                                         \
		bool operator()( ELEM, ELEM ) const;                                   \
	};                                                                         \
	void s4fis##NAME( ELEM *first, ELEM *last, S4Cmp##NAME comp )              \
	{                                                                          \
		_STL::__final_insertion_sort( first, last, comp );                     \
	}

S4_FINAL_INSERTION( 002E1690, S4SortElem12 )
S4_FINAL_INSERTION( 002EB8E0, S4SortElem20 )
S4_FINAL_INSERTION( 00531FA0, S4SortElem12 )
S4_FINAL_INSERTION( 00532740, S4SortElem12 )
S4_FINAL_INSERTION( 00574DF0, S4SortElem12 )

#define S4_MAKE_HEAP( NAME )                                                   \
	struct S4Cmp##NAME                                                         \
	{                                                                          \
		void *m_state;                                                         \
		bool operator()( S4SortElem8, S4SortElem8 ) const;                      \
	};                                                                         \
	void s4mh##NAME( S4SortElem8 *first, S4SortElem8 *last, S4Cmp##NAME comp ) \
	{                                                                          \
		_STL::make_heap( first, last, comp );                                  \
	}

S4_MAKE_HEAP( 00261140 )
S4_MAKE_HEAP( 00437D80 )
S4_MAKE_HEAP( 00575AA0 )
S4_MAKE_HEAP( 009F3400 )
S4_MAKE_HEAP( 009F34B0 )

#define S4_PUSH_HEAP( NAME )                                                   \
	struct S4Cmp##NAME                                                         \
	{                                                                          \
		void *m_state;                                                         \
		bool operator()( int, int ) const;                                     \
	};                                                                         \
	void s4ph##NAME( int *first, int hole, int top, int value,                 \
		S4Cmp##NAME comp )                                                     \
	{                                                                          \
		_STL::__push_heap( first, hole, top, value, comp );                    \
	}

S4_PUSH_HEAP( 003408C0 )
S4_PUSH_HEAP( 004529D0 )
S4_PUSH_HEAP( 00452A50 )
S4_PUSH_HEAP( 007534F0 )
