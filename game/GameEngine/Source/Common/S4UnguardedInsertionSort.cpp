// cl: -GX-
//
// Four 93-byte bodies that walk a range of four-byte elements and, for each
// one, slide it back over its predecessors while a two-argument predicate keeps
// saying yes -- SGI's unguarded insertion pass, the callee the introsort
// final-insertion bodies in Q3IntrosortFamilies.cpp reach through their second
// call site:
//
//     for ( i = first; i != last; ++i ) {
//         val = *i; cur = i; next = i - 1;
//         while ( pred( val, *next ) ) { *cur = *next; cur = next; --next; }
//         *cur = val; }
//
// WHAT THE BYTES SHOW -- and what they FORCE about the signature.
//
// The predicate is __thiscall: two dwords pushed, no cleanup at the call site,
// and `lea ecx,[<slot>]` immediately before it.  With four saved registers and
// the predicate's two arguments on the stack, that `lea` resolves to the SECOND
// argument slot -- the SAME slot the loop bound is read from, at entry and
// again at the bottom of the loop.  So one argument slot serves twice: its
// first dword is the end pointer, and its ADDRESS is the predicate's `this`.
//
// That is not what a by-value comparator in a LAST argument position compiles
// to, and the difference is measurable rather than argued.  Spelled with the
// comparator as a trailing parameter -- three arguments or four, and with the
// functor empty, one dword, two dwords or three -- MSVC 7.1 emits the identical
// 93 bytes except for the two displacement bytes, which come out 0x24, 0x28 or
// 0x2C for a comparator in position three, four or five.  Retail's is 0x20.
// Spelled through STLport's own `__unguarded_insertion_sort_aux`, MSVC inserts
// an eight-byte copy of the by-value comparator into a dead argument slot and
// the body grows to 95 bytes with the inner loop no longer 16-byte aligned.
// Only a SECOND-POSITION by-value struct, read for the bound and addressed for
// the call, reproduces retail.
//
// The remaining shape is ordinary: element moves are single dword loads and
// stores, `add ebp,4` is the stride, and the fall-through from the guard test
// straight into the loop body is the compiler's rotation of the `for`.
//
// A CROSS-CHECK BETWEEN LANES.  The four predicate addresses here --
// 0x0033D5E0, 0x00451F60, 0x00451E90 and 0x00752B80 -- are exactly the four
// __push_heap predicates in S4StlSortHelpers.cpp.  Each belongs to one sort
// instantiation seen from two layers, which is why one predicate address
// carries the whole axis of this family.  They are declared as members of
// SEPARATE types here because nothing in these bytes shows the two layers pass
// the same object type, only that they call the same code.
//
// IDENTITY IS NOT RECOVERED.  Every type is named after the retail body that
// uses it; each `operator()` is DECLARED, never defined, and pinned to the
// address its REL32 resolves to through the ILT thunk in the way.  `int` stands
// in for the element because the bytes fix its width and its scalar category
// and nothing more.
//
// WHAT THE BYTES CANNOT DECIDE.  How WIDE the second parameter is: only its
// first dword is read, and cdecl leaves the rest invisible from inside.  The
// four-dword push at the call sites in Q3IntrosortFamilies.cpp is equally
// consistent with four separate arguments, so the narrowest spelling is used
// here.  What the predicate compares, beyond taking two elements by value and
// returning a byte tested with `test al,al`.

#define S4_UNGUARDED_INSERTION( NAME )                                         \
	struct S4Range##NAME                                                       \
	{                                                                          \
		int *m_last;                                                           \
		bool operator()( int, int ) const;                                     \
	};                                                                         \
	void s4uis##NAME( int *first, S4Range##NAME range )                        \
	{                                                                          \
		for ( int *i = first; i != range.m_last; ++i )                         \
		{                                                                      \
			int val = *i;                                                      \
			int *cur = i;                                                      \
			int *next = i - 1;                                                 \
			while ( range( val, *next ) )                                      \
			{                                                                  \
				*cur = *next;                                                  \
				cur = next;                                                    \
				--next;                                                        \
			}                                                                  \
			*cur = val;                                                        \
		}                                                                      \
	}

S4_UNGUARDED_INSERTION( 00342CE0 )
S4_UNGUARDED_INSERTION( 00453090 )
S4_UNGUARDED_INSERTION( 00453180 )
S4_UNGUARDED_INSERTION( 007537C0 )
