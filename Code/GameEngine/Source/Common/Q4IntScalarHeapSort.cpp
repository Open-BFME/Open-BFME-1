// cl: -GX-
// stlport
//
// The comparator-LESS twins of the Q4 grid: STLport's `sort`, `push_heap`,
// `pop_heap` and `make_heap` over a four-byte signed scalar with the default
// `operator<`.  The comparisons inline to signed jge/jl, so unlike the
// Q4IntrosortLoop.cpp members there is no functor argument anywhere in the
// family -- __push_heap carries (first, holeIndex, topIndex, value) and
// __unguarded_insertion_sort_aux only (first, last, tag).  `int` stands in
// for the element because the bytes fix its size, signedness and category
// and nothing more.

#include <algorithm>

void q4IntSort( int *first, int *last )
{
	_STL::sort( first, last );
}

void q4IntPushHeap( int *first, int *last )
{
	_STL::push_heap( first, last );
}

void q4IntPopHeap( int *first, int *last )
{
	_STL::pop_heap( first, last );
}

void q4IntMakeHeap( int *first, int *last )
{
	_STL::make_heap( first, last );
}

void q4IntPartialSort( int *first, int *middle, int *last )
{
	_STL::partial_sort( first, middle, last );
}
