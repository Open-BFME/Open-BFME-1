// cl: -GX-
// stlport

#include <algorithm>

// Retail calls the comparator value itself, so this specialization takes a
// function pointer rather than the stateful functors used by the other Q4 sorts.
typedef bool (__cdecl *Q4Compare00483F70)(int, int);

template const int &_STL::__median<int, Q4Compare00483F70>(
	const int &, const int &, const int &, Q4Compare00483F70);

template int *_STL::__unguarded_partition<int *, int, Q4Compare00483F70>(
	int *, int *, int, Q4Compare00483F70);
