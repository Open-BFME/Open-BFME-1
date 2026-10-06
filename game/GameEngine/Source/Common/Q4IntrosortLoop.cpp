// cl: -GX-
// stlport
//
// Eight 140-byte bodies of STLport's __introsort_loop over a FOUR-BYTE SCALAR
// element with a comparator -- the recursive half of `sort`:
//
//     while (last - first > 16 elements) {
//         if (depth_limit == 0) { __partial_sort(first, last, last, 0, comp); return; }
//         --depth_limit;
//         cut = __unguarded_partition(first, last,
//                   *__median(first, first + (last-first)/2, last-1, comp), comp);
//         __introsort_loop(cut, last, 0, depth_limit, comp);
//         last = cut;
//     }
//
// WHAT THE BYTES SHOW.  Argument slots are read straight off the frame: with
// two registers pushed, [esp+8] and [esp+0x10] are `first` and `last`; with
// three pushed, [esp+0x20] is `comp`; with four, [esp+0x20] is `depth_limit`.
// That places an UNTOUCHED third argument between `last` and `depth_limit`,
// which is STLport's `_Tp*` type tag -- never loaded, only passed along as a
// literal 0 in the recursive call.  So the retail body is `__introsort_loop`
// itself, not `sort`.
//
// COUNTING PUSHES AGAINST THE LATER POP RECOVERS THE ARITIES WITHOUT LOOKING
// AT ANY CALLEE.  __median takes four (first, middle, last-1, comp) and its
// result is dereferenced, so it returns a reference; __unguarded_partition
// takes four and returns the cut in eax; the recursion takes five; and the
// depth-exhausted arm looks like four pushes but pops 0x14 because the shared
// `push ebp` for `comp` was hoisted ABOVE the `je` -- __partial_sort really
// takes five (first, last, last, tag, comp).  Reading that arm as four-argument
// would have been the easy mistake.
//
// `and eax,0xfffffffc` on the byte span and `cmp eax,0x40` are the element size
// (4) and STLport's __stl_threshold (16) fused; `sar eax,2 / cdq / sub / sar 1`
// is the midpoint.  The self-call at 0x0034BFC0 resolves to this very body, so
// the recursion is direct and not through a sibling instantiation.
//
// THE ELEMENT IS A SCALAR, on the same evidence that decided the make_heap
// family: a four-byte STRUCT element changes the register the loop's element
// load lands in.
//
// THE VARYING AXIS IS FOUR REL32s THAT MOVE AS ONE.  Every member has its own
// __median, __unguarded_partition, __partial_sort and self-call, and all four
// belong to the same instantiation -- there is no combination in which one
// member borrows another's helper.  That is why a single template argument (the
// comparator type) carries the whole axis here: one distinct comparator per
// member produces one distinct set of four callees.
//
// IDENTITY IS NOT RECOVERED.  Comparators are named after the __introsort_loop
// body that uses them and are declared, never defined; `int` stands in for the
// element because the bytes fix its size and category and nothing more.

#include <algorithm>

#define Q4_SORT_COMPARATOR( T )                                           \
	struct Q4Sort##T                                                      \
	{                                                                     \
		void *m_state;                                                    \
		bool operator()( int, int ) const;                                \
	};

#define Q4_SORT( T )                                                      \
	void q4Sort##T( int *first, int *last, Q4Sort##T comp )               \
	{                                                                     \
		_STL::sort( first, last, comp );                                  \
	}

Q4_SORT_COMPARATOR( 0034BFC0 )
Q4_SORT_COMPARATOR( 003D15A0 )
Q4_SORT_COMPARATOR( 004566F0 )
Q4_SORT_COMPARATOR( 004567A0 )
Q4_SORT_COMPARATOR( 00483F70 )
Q4_SORT_COMPARATOR( 005156D0 )
Q4_SORT_COMPARATOR( 00533470 )
Q4_SORT_COMPARATOR( 00755050 )

// THIS TU EMITS NO HELPER COPY THAT RETAIL DISPROVES.  Instantiating `sort`
// pulls in every helper, and these came out as COMDAT copies whose bytes
// differ from retail's body at the name's address (link_census RetailTruth:
// "wrong"), copies the link can keep ahead of a retail TU's: __partial_sort for
// all eight comparators, and __median and __unguarded_partition for 003D15A0,
// 00483F70, 005156D0 and 00533470 (003D15A0's retail bodies are
// stlport_median_q4sort.cpp and stlport_unguarded_partition_q4sort.cpp, where
// the comparator is inlined, not called).  Declaring those specializations,
// never defining them, leaves each call an external reference.  __partial_sort
// was also the only path to the heap helpers, so the __make_heap and sort_heap
// copies this TU proves for 003D15A0 and 004567A0 are instantiated explicitly
// below; their __adjust_heap/__push_heap for 003D15A0 are retail 0x003CDD00
// and 0x003CC5F0 (stlport_adjust_heap_q4sort.cpp, stlport_push_heap_q4sort.cpp),
// declared here for the same reason.
#define Q4_SORT_EXTERNAL_PARTIAL_SORT( T )                                \
	template <>                                                           \
	void __partial_sort<int *, int, Q4Sort##T>( int *, int *, int *, int *, Q4Sort##T );

#define Q4_SORT_EXTERNAL_PIVOT( T )                                       \
	template <>                                                           \
	const int &__median<int, Q4Sort##T>( const int &, const int &, const int &, Q4Sort##T ); \
	template <>                                                           \
	int *__unguarded_partition<int *, int, Q4Sort##T>( int *, int *, int, Q4Sort##T );

namespace _STL
{
Q4_SORT_EXTERNAL_PARTIAL_SORT( 0034BFC0 )
Q4_SORT_EXTERNAL_PARTIAL_SORT( 003D15A0 )
Q4_SORT_EXTERNAL_PARTIAL_SORT( 004566F0 )
Q4_SORT_EXTERNAL_PARTIAL_SORT( 004567A0 )
Q4_SORT_EXTERNAL_PARTIAL_SORT( 00483F70 )
Q4_SORT_EXTERNAL_PARTIAL_SORT( 005156D0 )
Q4_SORT_EXTERNAL_PARTIAL_SORT( 00533470 )
Q4_SORT_EXTERNAL_PARTIAL_SORT( 00755050 )

Q4_SORT_EXTERNAL_PIVOT( 003D15A0 )
Q4_SORT_EXTERNAL_PIVOT( 00483F70 )
Q4_SORT_EXTERNAL_PIVOT( 005156D0 )
Q4_SORT_EXTERNAL_PIVOT( 00533470 )

template <>
void __adjust_heap<int *, int, int, Q4Sort003D15A0>( int *, int, int, int, Q4Sort003D15A0 );
template <>
void __push_heap<int *, int, int, Q4Sort003D15A0>( int *, int, int, int, Q4Sort003D15A0 );
}

Q4_SORT( 0034BFC0 )
Q4_SORT( 003D15A0 )
Q4_SORT( 004566F0 )
Q4_SORT( 004567A0 )
Q4_SORT( 00483F70 )
Q4_SORT( 005156D0 )
Q4_SORT( 00533470 )
Q4_SORT( 00755050 )

template void _STL::__make_heap<int *, Q4Sort003D15A0, int, int>( int *, int *, Q4Sort003D15A0, int *, int * );
template void _STL::__make_heap<int *, Q4Sort004567A0, int, int>( int *, int *, Q4Sort004567A0, int *, int * );
template void _STL::sort_heap<int *, Q4Sort003D15A0>( int *, int *, Q4Sort003D15A0 );
template void _STL::sort_heap<int *, Q4Sort004567A0>( int *, int *, Q4Sort004567A0 );
