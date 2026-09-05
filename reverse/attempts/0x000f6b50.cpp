// ?d_000f6b50@@YAXXZ
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

// Open-BFME: see HashIntP12cdEraseThunks banked attempt (reverse/attempts/0x000d64a0.cpp) --
// same hash_int_p12cd family, const_iterator erase overload, 0x000F6B50.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;
typedef bool Bool;

// 0x000F6B50
struct Gen_t_000f73d0_p12cd { int a[3]; Gen_t_000f73d0_p12cd(); Gen_t_000f73d0_p12cd(const Gen_t_000f73d0_p12cd&); ~Gen_t_000f73d0_p12cd(); Gen_t_000f73d0_p12cd& operator=(const Gen_t_000f73d0_p12cd&); };
bool operator==(const Gen_t_000f73d0_p12cd&, const Gen_t_000f73d0_p12cd&);
bool operator<(const Gen_t_000f73d0_p12cd&, const Gen_t_000f73d0_p12cd&);

typedef _STL::pair<const int, Gen_t_000f73d0_p12cd> Pair_000f73d0;
typedef _STL::hashtable<Pair_000f73d0, int, _STL::hash<int>,
	_STL::_Select1st<Pair_000f73d0>, _STL::equal_to<int>,
	_STL::allocator<Pair_000f73d0> > Table_000f73d0;

template class _STL::hashtable<Pair_000f73d0, int, _STL::hash<int>,
	_STL::_Select1st<Pair_000f73d0>, _STL::equal_to<int>,
	_STL::allocator<Pair_000f73d0> >;
